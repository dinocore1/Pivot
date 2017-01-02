#include <pivot/Pivot.h>
#include <pivot/VectorImpl.h>


namespace pivot {

const size_t kMinVectorCapacity = 4;

static inline size_t max(size_t a, size_t b) {
  return a > b ? a : b;
}

VectorImpl::VectorImpl(size_t itemSize, uint32_t flags)
 : mStorage(0), mCount(0), mFlags(flags), mItemSize(itemSize) {}

VectorImpl::VectorImpl(const VectorImpl& rhs)
 : mStorage(rhs.mStorage), mCount(rhs.mCount),
  mFlags(rhs.mFlags), mItemSize(rhs.mItemSize) {

  if(mStorage) {
    SharedBuffer::bufferFromData(mStorage)->retain();
  }
}

size_t VectorImpl::capacity() const {
  if(mStorage) {
    return SharedBuffer::bufferFromData(mStorage)->size() / mItemSize;
  }
  return 0;
}

ssize_t VectorImpl::insertAt(const void* item, size_t index, size_t numItems) {
  if (index > size()) {
    return BAD_INDEX;
  }

  void* where = _grow(index, numItems);
  if (where) {
    if (item) {
      _do_splat(where, item, numItems);
    }
    else {
      _do_construct(where, numItems);
    }
  }
  return where ? index : NO_MEMORY;
}

void* VectorImpl::_grow(size_t where, size_t amount) {
  const size_t new_size = mCount + amount;
  if (capacity() < new_size) {
    const size_t new_capacity = max(kMinVectorCapacity, ((new_size * 3) + 1) / 2);

  }
}

} // namespace pivot
