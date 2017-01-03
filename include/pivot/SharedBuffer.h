#ifndef PIVOT_SHAREDBUFFER_H
#define PIVOT_SHAREDBUFFER_H

namespace pivot {

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
  inline size_t size() const;

  void retain() const;
  void release(uint32_t flags = 0) const;
  inline bool isOnlyOwner() const;

  // edit the buffer (get a writtable version of it)
  SharedBuffer* edit() const;

  // edit the buffer, resizing if needed
  SharedBuffer* editResize(size_t size) const;

private:
  SharedBuffer();
  ~SharedBuffer();
  SharedBuffer(const SharedBuffer&);
  SharedBuffer& operator= (const SharedBuffer&);

  mutable int32_t mRefs;
  size_t mSize;

};

const void* SharedBuffer::data() const {
  return this + 1;
}

size_t SharedBuffer::size() const {
  return mSize;
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


} // namespace pivot

#endif // PIVOT_SHAREDBUFFER_H
