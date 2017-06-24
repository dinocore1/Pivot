#ifndef PIVOT_VECTORIMPL_H
#define PIVOT_VECTORIMPL_H

namespace pivot {

class VectorImpl {
public:
  enum {
    HAS_TRIVIAL_CTOR     = 0x00000001,
    HAS_TRIVIAL_DTOR    = 0x00000002,
    HAS_TRIVIAL_COPY    = 0x00000004,
  };

  VectorImpl(size_t itemSize, uint32_t flags);
  VectorImpl(const VectorImpl& rhs);
  virtual ~VectorImpl();

  void finish_vector();

  VectorImpl& operator= (const VectorImpl&);
  inline size_t size() const;
  inline bool isEmpty() const;
  size_t capacity() const;
  ssize_t insertAt(const void* item, size_t index, size_t numItems);
  void clear();

protected:
  size_t itemSize() const;
  void release_storage();

  virtual void do_construct(void* storage, size_t num) const = 0;
  virtual void do_destroy(void* storage, size_t num) const = 0;
  virtual void do_copy(void* dest, const void* from, size_t num) const = 0;
  virtual void do_splat(void* dest, const void* item, size_t num) const = 0;
  virtual void do_move_forward(void* dest, const void* from, size_t num) const = 0;
  virtual void do_move_backward(void* dest, const void* from, size_t num) const = 0;

private:
  void* _grow(size_t where, size_t amount);
  void  _shrink(size_t where, size_t amount);

  inline void _do_construct(void* storage, size_t num) const;
  inline void _do_destroy(void* storage, size_t num) const;
  inline void _do_copy(void* dest, const void* from, size_t num) const;
  inline void _do_splat(void* dest, const void* item, size_t num) const;
  inline void _do_move_forward(void* dest, const void* from, size_t num) const;
  inline void _do_move_backward(void* dest, const void* from, size_t num) const;


  void* mStorage;   // base address of the vector
  size_t mCount;     // number of items
  const uint32_t mFlags;
  const size_t mItemSize;



};

inline
size_t VectorImpl::size() const {
  return mCount;
}

inline
bool VectorImpl::isEmpty() const {
  return mCount == 0;
}

} // namespace pivot

#endif // PIVOT_VECTORIMPL_H
