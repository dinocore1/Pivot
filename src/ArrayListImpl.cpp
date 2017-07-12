#include <pivot/Pivot.h>

#include <cstring>

namespace pivot {

const size_t kMinArrayCapacity = 4;

#if defined(WIN32)
//windows defines min/max as a macro
#undef min
#undef max
#endif

static inline size_t min(size_t a, size_t b) {
  return a<b ? a : b;
}

static inline size_t max(size_t a, size_t b) {
  return a>b ? a : b;
}

ArrayListImpl::ArrayListImpl(size_t itemSize, uint32_t flags)
  : mStorage(0), mCount(0), mFlags(flags), mItemSize(itemSize) {}

ArrayListImpl::~ArrayListImpl() {
//  ALOGW_IF(mCount,
//      "[%p] subclasses of VectorImpl must call finish_vector()"
//      " in their destructor. Leaking %d bytes.",
//      this, (int)(mCount*mItemSize));
  // We can't call _do_destroy() here because the vtable is already gone.
}

int ArrayListImpl::removeItemsAt(size_t index, size_t count) {
//    ALOG_ASSERT((index+count)<=size(),
//        "[%p] remove: index=%d, count=%d, size=%d",
//               this, (int)index, (int)count, (int)size());

  if((index+count) > size()) {
    return BAD_VALUE;
  }
  _shrink(index, count);
  return index;
}

void ArrayListImpl::finish_vector() {
  release_storage();
  mStorage = 0;
  mCount = 0;
}

void ArrayListImpl::clear() {
  _shrink(0, mCount);
}

int ArrayListImpl::insertAt(const void* item, size_t index, size_t numItems) {
  if(index > size()) {
    return BAD_INDEX;
  }
  void* where = _grow(index, numItems);
  if(where) {
    if(item) {
      _do_splat(where, item, numItems);
    } else {
      _do_construct(where, numItems);
    }
  }
  return where ? index : (int)NO_MEMORY;
}

int ArrayListImpl::insertArrayAt(const void* array, size_t index, size_t len) {
  if(index > size()) {
    return BAD_INDEX;
  }
  void* where = _grow(index, len);
  if(where) {
    _do_copy(where, array, len);
  }
  return where ? index : (int) NO_MEMORY;
}

int ArrayListImpl::appendArray(const void* array, size_t len) {
  return insertArrayAt(array, size(), len);
}

int ArrayListImpl::insertArrayListAt(const ArrayListImpl& o, size_t index) {
  return insertArrayAt(o.arrayImpl(), index, o.size());
}

int ArrayListImpl::appendArrayList(const ArrayListImpl& o) {
  return insertArrayListAt(o, size());
}

int ArrayListImpl::add(const void* item) {
  return insertAt(item, size());
}

void* ArrayListImpl::editArrayImpl() {
  if(mStorage) {
    SharedBuffer* sb = SharedBuffer::bufferFromData(mStorage)->attemptEdit();
    if(sb == 0) {
      sb = SharedBuffer::alloc(capacity() * mItemSize);
      if(sb) {
        _do_copy(sb->data(), mStorage, mCount);
        release_storage();
        mStorage = sb->data();
      }
    }
  }
  return mStorage;
}

const void* ArrayListImpl::itemLocation(size_t index) const {
  //ALOG_ASSERT(index<capacity(),
  //    "[%p] itemLocation: index=%d, capacity=%d, count=%d",
  //    this, (int)index, (int)capacity(), (int)mCount);

  if(index < capacity()) {
    const  void* buffer = arrayImpl();
    if(buffer) {
      return reinterpret_cast<const char*>(buffer) + index*mItemSize;
    }
  }
  return 0;
}

size_t ArrayListImpl::capacity() const {
  if(mStorage) {
    return SharedBuffer::bufferFromData(mStorage)->size() / mItemSize;
  }
  return 0;
}

void ArrayListImpl::release_storage() {
  if(mStorage) {
    const SharedBuffer* sb = SharedBuffer::bufferFromData(mStorage);
    if(sb->release(SharedBuffer::eKeepStorage) == 0) {
      _do_destroy(mStorage, mCount);
      SharedBuffer::dealloc(sb);
    }
  }
}

void* ArrayListImpl::_grow(size_t where, size_t amount) {
//    ALOGV("_grow(this=%p, where=%d, amount=%d) count=%d, capacity=%d",
//        this, (int)where, (int)amount, (int)mCount, (int)capacity());

//    ALOG_ASSERT(where <= mCount,
//            "[%p] _grow: where=%d, amount=%d, count=%d",
//            this, (int)where, (int)amount, (int)mCount); // caller already checked

  const size_t new_size = mCount + amount;
  if(capacity() < new_size) {
    const size_t new_capacity = max(kMinArrayCapacity, ((new_size*3)+1)/2);
//        ALOGV("grow vector %p, new_capacity=%d", this, (int)new_capacity);
    if((mStorage) &&
        (mCount==where) &&
        (mFlags & HAS_TRIVIAL_COPY) &&
        (mFlags & HAS_TRIVIAL_DTOR)) {
      const SharedBuffer* cur_sb = SharedBuffer::bufferFromData(mStorage);
      SharedBuffer* sb = cur_sb->editResize(new_capacity * mItemSize);
      mStorage = sb->data();
    } else {
      SharedBuffer* sb = SharedBuffer::alloc(new_capacity * mItemSize);
      if(sb) {
        void* array = sb->data();
        if(where != 0) {
          _do_copy(array, mStorage, where);
        }
        if(where != mCount) {
          const void* from = reinterpret_cast<const uint8_t*>(mStorage) + where*mItemSize;
          void* dest = reinterpret_cast<uint8_t*>(array) + (where+amount)*mItemSize;
          _do_copy(dest, from, mCount-where);
        }
        release_storage();
        mStorage = const_cast<void*>(array);
      }
    }
  } else {
    void* array = editArrayImpl();
    if(where != mCount) {
      const void* from = reinterpret_cast<const uint8_t*>(array) + where*mItemSize;
      void* to = reinterpret_cast<uint8_t*>(array) + (where+amount)*mItemSize;
      _do_move_forward(to, from, mCount - where);
    }
  }
  mCount = new_size;
  void* free_space = const_cast<void*>(itemLocation(where));
  return free_space;
}

void ArrayListImpl::_shrink(size_t where, size_t amount) {
  if(!mStorage) {
    return;
  }

//    ALOGV("_shrink(this=%p, where=%d, amount=%d) count=%d, capacity=%d",
//        this, (int)where, (int)amount, (int)mCount, (int)capacity());

//    ALOG_ASSERT(where + amount <= mCount,
//            "[%p] _shrink: where=%d, amount=%d, count=%d",
//            this, (int)where, (int)amount, (int)mCount); // caller already checked

  const size_t new_size = mCount - amount;
  if(new_size*3 < capacity()) {
    const size_t new_capacity = max(kMinArrayCapacity, new_size*2);
//        ALOGV("shrink vector %p, new_capacity=%d", this, (int)new_capacity);
    if((where == new_size) &&
        (mFlags & HAS_TRIVIAL_COPY) &&
        (mFlags & HAS_TRIVIAL_DTOR)) {
      const SharedBuffer* cur_sb = SharedBuffer::bufferFromData(mStorage);
      SharedBuffer* sb = cur_sb->editResize(new_capacity * mItemSize);
      mStorage = sb->data();
    } else {
      SharedBuffer* sb = SharedBuffer::alloc(new_capacity * mItemSize);
      if(sb) {
        void* array = sb->data();
        if(where != 0) {
          _do_copy(array, mStorage, where);
        }
        if(where != new_size) {
          const void* from = reinterpret_cast<const uint8_t*>(mStorage) + (where+amount)*mItemSize;
          void* dest = reinterpret_cast<uint8_t*>(array) + where*mItemSize;
          _do_copy(dest, from, new_size - where);
        }
        release_storage();
        mStorage = const_cast<void*>(array);
      }
    }
  } else {
    void* array = editArrayImpl();
    void* to = reinterpret_cast<uint8_t*>(array) + where*mItemSize;
    _do_destroy(to, amount);
    if(where != new_size) {
      const void* from = reinterpret_cast<uint8_t*>(array) + (where+amount)*mItemSize;
      _do_move_backward(to, from, new_size - where);
    }
  }
  mCount = new_size;
}

void ArrayListImpl::_do_construct(void* storage, size_t num) const {
  if(!(mFlags & HAS_TRIVIAL_CTOR)) {
    do_construct(storage, num);
  }
}

void ArrayListImpl::_do_destroy(void* storage, size_t num) const {
  if(!(mFlags & HAS_TRIVIAL_DTOR)) {
    do_destroy(storage, num);
  }
}

void ArrayListImpl::_do_copy(void* dest, const void* from, size_t num) const {
  if(!(mFlags & HAS_TRIVIAL_COPY)) {
    do_copy(dest, from, num);
  } else {
    memcpy(dest, from, num*itemSize());
  }
}

void ArrayListImpl::_do_splat(void* dest, const void* item, size_t num) const {
  do_splat(dest, item, num);
}

void ArrayListImpl::_do_move_forward(void* dest, const void* from, size_t num) const {
  do_move_forward(dest, from, num);
}

void ArrayListImpl::_do_move_backward(void* dest, const void* from, size_t num) const {
  do_move_backward(dest, from, num);
}

} // namespace pivot
