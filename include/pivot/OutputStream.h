#ifndef PIVOT_OUTPUTSTREAM_H
#define PIVOT_OUTPUTSTREAM_H

namespace pivot {

class OutputStream {
public:
  virtual void close() = 0;
  virtual void write(const byte* buf, size_t offset, size_t len) = 0;
};

} // namespace pivot

#endif // PIVOT_OUTPUTSTREAM_H
