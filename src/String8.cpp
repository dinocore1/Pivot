#include <pivot/Pivot.h>
#include <pivot/String8.h>

#include <Static.h>

#include <string.h>

namespace pivot {

static SharedBuffer* gEmptyStringBuf = NULL;
static char* gEmptyString = NULL;

static inline char* getEmptyString() {
	gEmptyStringBuf->retain();
	return gEmptyString;
}

void initialize_string8() {
	SharedBuffer* buf = SharedBuffer::alloc(1);
	char* str = (char*)buf->data();
	*str = 0;
	gEmptyStringBuf = buf;
	gEmptyString = str;
}

void terminate_string8() {
	SharedBuffer::bufferFromData(gEmptyString)->release();
	gEmptyStringBuf = NULL;
	gEmptyString = NULL;
}

static char* allocFromUTF8(const char* o, size_t len) {
	if (len > 0) {
		SharedBuffer* buf = SharedBuffer::alloc(len + 1);
		if (buf) {
			char* str = (char*)buf->data();
			memcpy(str, o, len);
			str[len] = 0;
			return str;
		}
		return NULL;
	}

	return getEmptyString();
}

String8::String8()
  : mString(getEmptyString()) {
}

String8::String8(const String8& o)
 : mString(o.mString) {
	SharedBuffer::bufferFromData(mString)->retain();
}

String8::String8(const char* o)
 : mString(allocFromUTF8(o, strlen(o))) {

	if (mString == NULL) {
		mString = getEmptyString();
	}

}

String8::~String8() {
	SharedBuffer::bufferFromData(mString)->release();
}

status_t String8::append(const String8& o) {
	const size_t otherLen = o.length();
	if (length() == 0) {
		setTo(0);
		return OK;
	} else if (otherLen == 0) {
		return OK;
	}

	return real_append(o.string(), otherLen);
}

status_t String8::real_append(const char* other, size_t otherLen) {
	const size_t myLen = bytes();

	SharedBuffer* buf = SharedBuffer::bufferFromData(mString)->editResize(myLen + otherLen + 1);
	if (buf) {
		char* str = (char*)buf->data();
		mString = str;
		str += myLen;
		memcpy(str, other, otherLen);
		str[otherLen] = '\0';
		return OK;
	}
	return NO_MEMORY;
}

void String8::setTo(const String8& o) {
	SharedBuffer::bufferFromData(o.mString)->retain();
	SharedBuffer::bufferFromData(mString)->release();
	mString = o.mString;
}


} // namespace pivot
