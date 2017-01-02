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

  VectorImpl& operator= (const VectorImpl&);
  inline size_t size() const;
  inline bool isEmpty() const;
  size_t capacity() const;
  void insertAt(const void* item, size_t index);
  void clear();

private:
  const uint32_t mFlags;
  const size_t mItemSize;
  void* mStorage;
  size_t mCount;

};

inline size_t VectorImpl::size() const {
	return mCount;
}

inline bool VectorImpl::isEmpty() const {
	return mCount == 0;
}

} // namespace pivot

#endif // PIVOT_VECTORIMPL_H
