#ifndef PIVOT_VECTOR_H
#define PIVOT_VECTOR_H

namespace pivot {

class VectorImpl {
public:
  enum {
    HAS_TRIVIAL_CTR     = 0x00000001,
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

template<class TYPE>
class Vector : private VectorImpl {
public:
  Vector();
  Vector(const Vector<TYPE>& rhs);
  virtual ~Vector();

  const Vector<TYPE>& operator = (const Vector<TYPE>& rhs) const;
  Vector<TYPE>& operator = (const Vector<TYPE>& rhs);

  void clear();
  size_t size() const;
  bool isEmpty() const;
  size_t capacity() const;

  const TYPE* array() const;
  TYPE* editArray();

  const TYPE& operator[] (size_t index) const;

  void insertAt(const TYPE& item, size_t index);

private:

};

} // namespace pivot


#endif // PIVOT_VECTOR_H
