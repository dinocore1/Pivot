
#include "config.h"
#include <pivot/Pivot.h>

#include <pivot/String.h>

namespace Pivot {

String::~String() {
  if(mData != NULL) {
    delete[] mData;
  }
}

String::String()
 : mLength(0), mData(NULL) {

}

String::String(const String& copy)
 : mLength(copy.mLength) {
   mData = new char[mLength];
   memcpy(mData, copy.mData, mLength);
}

String::String(const char* str) {
   mLength = strlen(str);
   mData = new char[mLength];
   memcpy(mData, str, mLength);

}

size_t String::length() const {
  return mLength;
}

String String::operator+ (const String& rhs) {

  String retval;
  retval.mLength = mLength + rhs.mLength;
  retval.mData = new char[retval.mLength];
  memcpy(&retval.mData[0], mData, mLength);
  memcpy(&retval.mData[mLength], rhs.mData, rhs.mLength);

  return retval;
}

String::operator const char* () const {
  return mData;
}

#if (__cpluplus >= 201103L)

String::String(String&& copy)
 : mLength(copy.mLength), mData(copy.mData) {
   copy.mData = NULL;
}


String& String::operator=(String&& other) {
  if(this != &other) {
    if(mData != NULL) {
      delete[] mData;
    }
    mLength = other.mLength;
    mData = other.mData;
    other.mData = NULL;
    other.mLength = 0;
  }
  return *this;
}

#endif // (__cpluplus >= 201103L)

} // namespace Pivot
