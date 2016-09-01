#include "config.h"
#include <pivot/Pivot.h>

#include <pivot/File.h>

#if defined(OS_TYPE_UNIX)
#include <unistd.h>
#endif

namespace Pivot {

File::File() {

}

File::~File() {

}

File::File(const String8& filePath)
 : mFilePath(filePath) {

 }

bool File::exists() const {
  #if defined(OS_TYPE_UNIX)
  return access(mFilePath, F_OK) == 0;
  #endif

  return false;
}

} // namespace Pivot
