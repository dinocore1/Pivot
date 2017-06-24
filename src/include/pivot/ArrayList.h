#ifndef PIVOT_ARRAYLIST_H
#define PIVOT_ARRAYLIST_H

namespace pivot {

class ArrayListImpl {
public:
  enum {
    HAS_TRIVIAL_CTOR = 0x00000001,
    HAS_TRIVIAL_DTOR = 0x00000002,
    HAS_TRIVIAL_COPY = 0x00000004
  };

  ArrayListImpl(size_t itemSize, uint32_t flags);
  virtual ~ArrayListImpl();

  inline size_t size() const;
  size_t capacity() const;

  int insertAt(const void* item, size_t index, size_t numItems);

protected:
  void* grow(size_t, size_t);

private:
  void* mStorage;   // base address of the vector
  size_t mCount;     // number of items
  const uint32_t mFlags;
  const size_t mItemSize;
};

size_t ArrayListImpl::size() const {
  return mCount;
}

template<typename TYPE>
class ArrayList : private ArrayListImpl {
public:
  ArrayList();
  ArrayList(const ArrayList<TYPE>&);
  virtual ~ArrayList();

  const TYPE& operator[](size_t index) const;

};

template<typename TYPE> inline
ArrayList<TYPE>::ArrayList()
 : ArrayListImpl(sizeof(TYPE),
  ( (traits<TYPE>::has_trivial_ctor ? HAS_TRIVIAL_CTOR : 0)
  | (traits<TYPE>::has_trivial_dtor ? HAS_TRIVIAL_DTOR : 0)
  | (traits<TYPE>::has_trivial_copy ? HAS_TRIVIAL_COPY : 0)
  )
){}

template<typename TYPE> inline
ArrayList<TYPE>::~ArrayList()
{}

} // namespace pivot

#endif PIVOT_ARRAYLIST_H
