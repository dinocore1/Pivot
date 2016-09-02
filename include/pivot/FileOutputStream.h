#ifndef PIVOT_FILEOUTPUTSTREAM_H
#define PIVOT_FILEOUTPUTSTREAM_H

namespace Pivot {

class FileOutputStream : public OutputStream {
public:
  FileOutputStream(const File&);
  virtual ~FileOutputStream();

  virtual void close();
  virtual void write(const byte* buf, size_t offset, size_t len);


private:
  File mFile;
  void* mImpl;
};

} // namespace Pivot

#endif // PIVOT_FILEOUTPUTSTREAM_H
