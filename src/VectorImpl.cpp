#include <pivot/Pivot.h>
#include <pivot/VectorImpl.h>


namespace pivot {

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

} // namespace pivot
