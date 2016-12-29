#include <pivot/Pivot.h>

#include <pivot/String8.h>

#include <stdio.h>
#include <string.h>


namespace pivot {

String8::~String8() {
  if(mLength != 0) {
    delete[] mData;
	mLength = 0;
  }
}

String8::String8()
 : mLength(0), mData(NULL) {

}

String8::String8(const String8& copy)
 : mLength(copy.mLength) {
   mData = new char[mLength];
   memcpy(mData, copy.mData, mLength);
}

String8::String8(const char* str) {
   mLength = strlen(str);
   mData = new char[mLength];
   memcpy(mData, str, mLength);

}

size_t String8::length() const {
  return mLength;
}

String8 String8::operator+ (const String8& rhs) {

  String8 retval;
  retval.mLength = mLength + rhs.mLength;
  retval.mData = new char[retval.mLength];
  memcpy(&retval.mData[0], mData, mLength);
  memcpy(&retval.mData[mLength], rhs.mData, rhs.mLength);

  return retval;
}

String8::operator const char* () const {
  return mData;
}

#if (__cpluplus >= 201103L)

String8::String8(String8&& copy)
 : mLength(copy.mLength), mData(copy.mData) {
   copy.mData = NULL;
}


String8& String8::operator=(String8&& other) {
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

} // namespace pivot
