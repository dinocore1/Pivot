#ifndef PIVOT_SHAREDBUFFER_H
#define PIVOT_SHAREDBUFFER_H

namespace pivot {

class SharedBuffer {
public:

  enum {
    eKeepStorage = 0x00000001
  };

  static SharedBuffer* alloc(size_t size);

  /*! free the memory associated with the SharedBuffer.
  * Fails if there are any users associated with this SharedBuffer.
  * In other words, the buffer must have been release by all its
  * users.
  */
  static int dealloc(const SharedBuffer* released);

  static inline SharedBuffer* bufferFromData(void* data);
  static inline const SharedBuffer* bufferFromData(const void* data);
  static inline size_t sizeFromData(const void* data);

  inline const void* data() const;
  inline void* data();
  inline size_t size() const;

  void retain() const;
  pivot_atomic_int_t release(uint32_t flags = 0) const;
  inline bool isOnlyOwner() const;

  // edit the buffer (get a writtable version of it)
  SharedBuffer* edit() const;

  // edit the buffer, resizing if needed
  SharedBuffer* editResize(size_t size) const;

  //! like edit() but fails if a copy is required
  SharedBuffer* attemptEdit() const;

private:
  SharedBuffer();
  ~SharedBuffer();
  SharedBuffer(const SharedBuffer&);
  SharedBuffer& operator= (const SharedBuffer&);

  mutable pivot_atomic_int_t_dec pivot_atomic_int_t mRefs;
  size_t mSize;

};

inline
const void* SharedBuffer::data() const {
  return this + 1;
}

inline
size_t SharedBuffer::size() const {
  return mSize;
}

inline
void* SharedBuffer::data() {
  return this + 1;
}

inline
bool SharedBuffer::isOnlyOwner() const {
  return (mRefs == 1);
}

inline
SharedBuffer* SharedBuffer::bufferFromData(void* data) {
  return data ? static_cast<SharedBuffer*>(data)-1 : 0;
}

inline
const SharedBuffer* SharedBuffer::bufferFromData(const void* data) {
  return data ? static_cast<const SharedBuffer*>(data)-1 : 0;
}

inline
size_t SharedBuffer::sizeFromData(const void* data) {
  return data ? bufferFromData(data)->mSize : 0;
}


} // namespace pivot

#endif // PIVOT_SHAREDBUFFER_H
