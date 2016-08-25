#ifndef PIVOT_INPUTSTREAM_H
#define PIVOT_INPUTSTREAM_H

namespace Pivot {

class InputStream {
public:
  virtual void close() = 0;
  virtual int read(byte* buf, size_t offset, size_t len) = 0;
};

} // namespace Pivot

#endif // PIVOT_INPUTSTREAM_H
