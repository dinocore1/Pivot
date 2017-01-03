#include <pivot/Pivot.h>

#include <pivot/FileOutputStream.h>

#if defined(OS_TYPE_UNIX)
#include <unistd.h>
#include <fcntl.h>
#endif

namespace pivot {

#if defined(OS_TYPE_UNIX)
struct Unix_Impl {
  int mHandle;
};
#endif

FileOutputStream::FileOutputStream(const File& file)
  : mFile(file), mImpl(NULL) {

#if defined(OS_TYPE_UNIX)
  Unix_Impl* data = new Unix_Impl();
  data->mHandle = open(file.getAbsolutePath(), O_WRONLY | O_CREAT);
  mImpl = data;
#endif
}

FileOutputStream::~FileOutputStream() {

}

void FileOutputStream::close() {

}

void FileOutputStream::write(const byte* buf, size_t offset, size_t len) {

#if defined(OS_TYPE_UNIX)
  Unix_Impl* data = (Unix_Impl*)mImpl;
  size_t bytesWritten = 0;
  while(bytesWritten < len) {
    ssize_t i = ::write(data->mHandle, &buf[offset + bytesWritten], len - bytesWritten);
    if(i > 0) {
      bytesWritten += i;
    } else {
      //error
      break;
    }
  }
#endif

}

} // namespace pivot
