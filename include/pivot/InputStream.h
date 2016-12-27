#ifndef PIVOT_INPUTSTREAM_H
#define PIVOT_INPUTSTREAM_H

namespace pivot {

class InputStream {
public:
  virtual void close() = 0;
  virtual int read(byte* buf, size_t offset, size_t len) = 0;
};

} // namespace pivot

#endif // PIVOT_INPUTSTREAM_H
