#ifndef PIVOT_VECTOR_H
#define PIVOT_VECTOR_H

#include <pivot/TypeHelpers.h>
#include <pivot/VectorImpl.h>

namespace pivot {

template<class TYPE>
class Vector : private VectorImpl {
public:
  Vector();
  Vector(const Vector<TYPE>& rhs);
  virtual ~Vector();

  const Vector<TYPE>& operator = (const Vector<TYPE>& rhs) const;
  Vector<TYPE>& operator = (const Vector<TYPE>& rhs);

  inline void clear();
  inline size_t size() const;
  inline bool isEmpty() const;
  inline size_t capacity() const;

  const TYPE* array() const;
  TYPE* editArray();

  const TYPE& operator[](size_t index) const;

  inline ssize_t insertAt(const TYPE& item, size_t index, size_t numItems = 1);

private:

};

template<class TYPE> inline
Vector<TYPE>::Vector()
  : VectorImpl(sizeof(TYPE),
               ((traits<TYPE>::has_trivial_ctor   ? HAS_TRIVIAL_CTOR   : 0)
                |(traits<TYPE>::has_trivial_dtor   ? HAS_TRIVIAL_DTOR   : 0)
                |(traits<TYPE>::has_trivial_copy   ? HAS_TRIVIAL_COPY   : 0)
               )) {
}

template<class TYPE> inline
Vector<TYPE>::Vector(const Vector<TYPE>& rhs)
  : VectorImpl(rhs) {
}

template<class TYPE> inline
Vector<TYPE>::~Vector() {
  finish_vector();
}

template<class TYPE> inline
void Vector<TYPE>::clear() {
  VectorImpl::clear();
}

template<class TYPE> inline
size_t Vector<TYPE>::size() const {
  return VectorImpl::size();
}

template<class TYPE> inline
bool Vector<TYPE>::isEmpty() const {
  return VectorImpl::isEmpty();
}

template<class TYPE> inline
size_t Vector<TYPE>::capacity() const {
  return VectorImpl::capacity();
}

template<class TYPE>
inline ssize_t Vector<TYPE>::insertAt(const TYPE& item, size_t index, size_t numItems) {
  return VectorImpl::insertAt(&item, index, numItems);
}

} // namespace pivot


#endif // PIVOT_VECTOR_H
