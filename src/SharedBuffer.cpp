#include <pivot/Pivot.h>

namespace pivot {

SharedBuffer* SharedBuffer::alloc(size_t size) {
  SharedBuffer* retval = static_cast<SharedBuffer*>(malloc(sizeof(SharedBuffer) + size));
  if(retval) {
    retval->mRefs = 1;
    retval->mSize = size;
  }

  return retval;
}

void SharedBuffer::retain() const {
  pivot_atomic_inc(&mRefs);
}

void SharedBuffer::release(uint32_t flags) const {
  if ((pivot_atomic_dec(&mRefs) == 0)) {
    if ((flags & KeepStorage) == 0) {
      free(const_cast<SharedBuffer*>(this));
    }
  }
}



} // namespace pivot
