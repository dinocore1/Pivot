#include <pivot/Pivot.h>
#include <pivot/String8.h>

#include <Static.h>

#include <string.h>

#include <cstdio>

//For some reason Windows's linker excludes static variable symbols when statically linking libraries
//objects. This is a weird workaround. See: http://stackoverflow.com/questions/599035/force-visual-studio-to-link-all-symbols-in-a-lib-file
//another solution is to set 'Linker->General->Link Library Dependencies' and 'Linker->General->Use Library Dependency Inputs' set to 'Yes' for your main app
FORCE_LINK_THAT(staticInit)

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
  if(len > 0) {
    SharedBuffer* buf = SharedBuffer::alloc(len + 1);
    if(buf) {
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

  if(mString == NULL) {
    mString = getEmptyString();
  }
}

String8::String8(const char* o, size_t numChars)
  : mString(allocFromUTF8(o, numChars)) {

  if(mString == NULL) {
    mString = getEmptyString();
  }
}

String8::~String8() {
  SharedBuffer::bufferFromData(mString)->release();
}

String8 String8::format(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  String8 result(formatV(fmt, args));

  va_end(args);
  return result;
}

String8 String8::formatV(const char* fmt, va_list args) {
  String8 result;
  result.appendFormatV(fmt, args);
  return result;
}

status_t String8::append(const String8& other) {
  const size_t otherLen = other.bytes();
  if(bytes() == 0) {
    setTo(other);
    return NO_ERROR;
  } else if(otherLen == 0) {
    return NO_ERROR;
  }

  return real_append(other.string(), otherLen);
}

status_t String8::appendFormat(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  status_t result = appendFormatV(fmt, args);

  va_end(args);
  return result;
}

status_t String8::appendFormatV(const char* fmt, va_list args) {
  int result = NO_ERROR;
  int n = vsnprintf(NULL, 0, fmt, args);
  if(n != 0) {
    size_t oldLength = length();
    char* buf = lockBuffer(oldLength + n);
    if(buf) {
      vsnprintf(buf + oldLength, n + 1, fmt, args);
    } else {
      result = NO_MEMORY;
    }
  }
  return result;
}

status_t String8::real_append(const char* other, size_t otherLen) {
  const size_t myLen = bytes();

  SharedBuffer* buf = SharedBuffer::bufferFromData(mString)->editResize(myLen + otherLen + 1);
  if(buf) {
    char* str = (char*)buf->data();
    mString = str;
    str += myLen;
    memcpy(str, other, otherLen);
    str[otherLen] = '\0';
    return OK;
  }
  return NO_MEMORY;
}

char* String8::lockBuffer(size_t size) {
  SharedBuffer* buf = SharedBuffer::bufferFromData(mString)->editResize(size+1);
  if(buf) {
    char* str = (char*)buf->data();
    mString = str;
    return str;
  }
  return NULL;
}

void String8::unlockBuffer() {
  unlockBuffer(strlen(mString));
}

status_t String8::unlockBuffer(size_t size) {
  if(size != this->length()) {
    SharedBuffer* buf = SharedBuffer::bufferFromData(mString)->editResize(size+1);
    if(! buf) {
      return NO_MEMORY;
    }

    char* str = (char*)buf->data();
    str[size] = 0;
    mString = str;
  }

  return NO_ERROR;
}

void String8::clear() {
  SharedBuffer::bufferFromData(mString)->release();
  mString = getEmptyString();
}

void String8::setTo(const String8& o) {
  SharedBuffer::bufferFromData(o.mString)->retain();
  SharedBuffer::bufferFromData(mString)->release();
  mString = o.mString;
}

int String8::compare(const String8& other) const {
  return strcmp(mString, other.mString);
}


} // namespace pivot
