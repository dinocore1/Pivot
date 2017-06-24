#include <pivot/Pivot.h>

namespace pivot {

ArrayListImpl::ArrayListImpl(size_t itemSize, uint32_t flags)
 : mStorage(0), mCount(0), mFlags(flags), mItemSize(itemSize) {}

ArrayListImpl::~ArrayListImpl()
{}

size_t ArrayListImpl::capacity() const {
  if(mStorage) {
    return SharedBuffer::bufferFromData(mStorage)->size() / mItemSize;
  }
  return 0;
}

int ArrayListImpl::insertAt(const void* item, size_t index, size_t numItems) {
  if(index > size()) {
    return BAD_INDEX;
  }
}

} // namespace pivot
