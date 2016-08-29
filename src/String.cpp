
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
 : mData(NULL) {

}

String::String(const String& copy)
 : mLength(copy.mLength) {
   mData = new char[mLength];
   memcpy(mData, copy.mData, mLength);
}

#if (__cpluplus >= 201103L)
String::String(String&& copy)
 : mLength(copy.mLength), mData(copy.mData) {
   copy.mData = NULL;
}
#endif

String::String(const char* str) {
   mLength = strlen(str);
   mData = new char[mLength];
   memcpy(mData, str, mLength);

}

size_t String::length() {
  return mLength;
}

} // namespace Pivot
