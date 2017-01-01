#ifndef PIVOT_VECTOR_H
#define PIVOT_VECTOR_H

namespace pivot {

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
