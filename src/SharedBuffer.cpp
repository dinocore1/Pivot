#include <pivot/Pivot.h>

#include <stdlib.h>
#include <string.h>

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

SharedBuffer* SharedBuffer::edit() const {
	if (isOnlyOwner()) {
		return const_cast<SharedBuffer*>(this);
	}
	
	SharedBuffer* sb = alloc(mSize);
	if (sb) {
		memcpy(sb->data(), data(), size());
		release();
	}
	return sb;
}

SharedBuffer* SharedBuffer::editResize(size_t newSize) const {
	if (isOnlyOwner()) {
		SharedBuffer* buf = const_cast<SharedBuffer*>(this);
		if (buf->mSize == newSize) {
			return buf;
		}
		buf = (SharedBuffer*)realloc(buf, sizeof(SharedBuffer) + newSize);
		if (buf != NULL) {
			buf->mSize = newSize;
			return buf;
		}
	}
	SharedBuffer* sb = alloc(newSize);
	if (sb) {
		const size_t mySize = mSize;
		memcpy(sb->data(), data(), newSize < mySize ? newSize : mySize);
		release();
	}

	return sb;
}



} // namespace pivot
