
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

String::String(const char* str) {
   mLength = strlen(str);
   mData = new char[mLength];
   memcpy(mData, str, mLength);

}

size_t String::length() {
  return mLength;
}

} // namespace Pivot
