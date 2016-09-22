#include "config.h"
#include <pivot/Pivot.h>

#include <pivot/SharedBuffer.h>

namespace Pivot {

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

int32_t SharedBuffer::release(uint32_t flags) const {
  int32_t prev;
  if (((prev = pivot_atomic_dec(&mRefs)) == 1)) {
    mRefs = 0;
    if ((flags & KeepStorage) == 0) {
      free(const_cast<SharedBuffer*>(this));
    }
  }
  return prev;

}



} // namespace Pivot
