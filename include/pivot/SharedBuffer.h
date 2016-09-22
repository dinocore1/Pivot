#ifndef PIVOT_SHAREDBUFFER_H
#define PIVOT_SHAREDBUFFER_H

namespace Pivot {

class SharedBuffer {
public:

  enum {
    KeepStorage = 0x00000001
  };

  static SharedBuffer* alloc(size_t size);

  static inline SharedBuffer* bufferFromData(void* data);
  static inline const SharedBuffer* bufferFromData(const void* data);
  static inline size_t sizeFromData(const void* data);

  inline const void* data() const;
  inline void* data();

  void retain() const;
  int32_t release(uint32_t flags = 0) const;
  inline bool isOnlyOwner() const;

private:
  SharedBuffer();
  ~SharedBuffer();
  SharedBuffer(const SharedBuffer&);
  SharedBuffer& operator = (const SharedBuffer&);

  mutable int32_t mRefs;
  size_t mSize;

};

const void* SharedBuffer::data() const {
  return this + 1;
}

void* SharedBuffer::data() {
  return this + 1;
}

bool SharedBuffer::isOnlyOwner() const {
  return (mRefs == 1);
}

SharedBuffer* SharedBuffer::bufferFromData(void* data) {
  return data ? static_cast<SharedBuffer*>(data)-1 : 0;
}

const SharedBuffer* SharedBuffer::bufferFromData(const void* data) {
  return data ? static_cast<const SharedBuffer*>(data)-1 : 0;
}

size_t SharedBuffer::sizeFromData(const void* data) {
  return data ? bufferFromData(data)->mSize : 0;
}


} // namespace Pivot

#endif // PIVOT_SHAREDBUFFER_H