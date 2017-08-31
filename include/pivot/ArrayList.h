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
  ArrayListImpl(const ArrayListImpl& rhs);
  virtual ~ArrayListImpl();
  void finish_vector();

  ArrayListImpl& operator= (const ArrayListImpl&);

  inline size_t size() const;
  inline bool isEmpty() const;
  size_t capacity() const;
  int removeItemsAt(size_t index, size_t count = 1);
  void clear();
  inline const size_t itemSize() const;

  inline const void* arrayImpl() const;
  void* editArrayImpl();

  int insertAt(const void* item, size_t index, size_t numItems = 1);
  int insertArrayAt(const void* array, size_t index, size_t len);
  int appendArray(const void* array, size_t length);
  int insertArrayListAt(const ArrayListImpl&, size_t index);
  int appendArrayList(const ArrayListImpl&);
  int add(const void* item);
  const void* itemLocation(size_t index) const;

protected:
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

  void* mStorage;   // base address of the ArrayList
  size_t mCount;     // number of items
  const uint32_t mFlags;
  const size_t mItemSize;
};

inline
size_t ArrayListImpl::size() const {
  return mCount;
}

inline
bool ArrayListImpl::isEmpty() const {
  return mCount == 0;
}

inline
const void* ArrayListImpl::arrayImpl() const {
  return mStorage;
}

inline
const size_t ArrayListImpl::itemSize() const {
  return mItemSize;
}

template<typename TYPE>
class ArrayList : private ArrayListImpl {
public:
  ArrayList();
  ArrayList(const ArrayList<TYPE>&);
  virtual ~ArrayList();

  // copy constructors
  const ArrayList<TYPE>& operator= (const ArrayList<TYPE>& rhs) const;
  ArrayList<TYPE>& operator= (const ArrayList<TYPE>& rhs);

  const TYPE& operator[](size_t index) const;
  const TYPE& itemAt(size_t index) const;

  //! returns number of items in the vector
  inline size_t size() const {
    return ArrayListImpl::size();
  }
  //! returns whether or not the vector is empty
  inline bool isEmpty() const {
    return ArrayListImpl::isEmpty();
  }
  //! returns how many items can be stored without reallocating the backing store
  inline size_t capacity() const {
    return ArrayListImpl::capacity();
  }

  //! read-only C-style access
  inline const TYPE* array() const;
  //! read-write C-style access
  TYPE* editArray();

  //! same as push() but returns the index the item was added at (or an error)
  int add(const TYPE& item);

  inline int insertAt(const TYPE& item, size_t index, size_t numItems = 1);
  int insertArrayAt(const TYPE* array, size_t index, size_t len);
  int appendArray(const TYPE* array, size_t length);
  int insertArrayListAt(const ArrayList<TYPE>&, size_t index);
  int appendArrayList(const ArrayList<TYPE>&);


  //! remove several items
  inline int removeItemsAt(size_t index, size_t count = 1);
  //! remove one item
  inline int removeAt(size_t index) {
    return removeItemsAt(index);
  }

  inline void clear();

  typedef TYPE* iterator;
  typedef TYPE const* const_iterator;

  inline iterator begin() {
    return editArray();
  }
  inline iterator end() {
    return editArray() + size();
  }

  inline const_iterator begin() const {
    return array();
  }
  inline const_iterator end() const {
    return array() + size();
  }

protected:
  virtual void    do_construct(void* storage, size_t num) const;
  virtual void    do_destroy(void* storage, size_t num) const;
  virtual void    do_copy(void* dest, const void* from, size_t num) const;
  virtual void    do_splat(void* dest, const void* item, size_t num) const;
  virtual void    do_move_forward(void* dest, const void* from, size_t num) const;
  virtual void    do_move_backward(void* dest, const void* from, size_t num) const;
};

// ArrayList<T> can be trivially moved using memcpy() because moving does not
// require any change to the underlying SharedBuffer contents or reference count.
template<typename T> struct trait_trivial_move<ArrayList<T> > {
  enum { value = true };
};


template<typename TYPE> inline
ArrayList<TYPE>::ArrayList()
  : ArrayListImpl(sizeof(TYPE),
                  ((traits<TYPE>::has_trivial_ctor ? HAS_TRIVIAL_CTOR : 0)
                   | (traits<TYPE>::has_trivial_dtor ? HAS_TRIVIAL_DTOR : 0)
                   | (traits<TYPE>::has_trivial_copy ? HAS_TRIVIAL_COPY : 0)
                  )
                 ) {}

template<typename TYPE> inline
ArrayList<TYPE>::ArrayList(const ArrayList<TYPE>& rhs)
 : ArrayListImpl(rhs) {}

template<typename TYPE> inline
ArrayList<TYPE>::~ArrayList() {
  finish_vector();
}

template<class TYPE> inline
ArrayList<TYPE>& ArrayList<TYPE>::operator= (const ArrayList<TYPE>& rhs) {
  ArrayListImpl::operator=(rhs);
  return *this;
}

template<class TYPE> inline
const ArrayList<TYPE>& ArrayList<TYPE>::operator= (const ArrayList<TYPE>& rhs) const {
  ArrayListImpl::operator=(static_cast<const ArrayList&>(rhs));
  return *this;
}

template<class TYPE> inline
const TYPE& ArrayList<TYPE>::operator[](size_t index) const {
// LOG_FATAL_IF(index>=size(),
//            "%s: index=%u out of range (%u)", __PRETTY_FUNCTION__,
//            int(index), int(size()));
  return *(array() + index);
}

template<class TYPE> inline
const TYPE& ArrayList<TYPE>::itemAt(size_t index) const {
  return operator[](index);
}

template<class TYPE> inline
int ArrayList<TYPE>::add(const TYPE& item) {
  return ArrayListImpl::add(&item);
}

template<class TYPE> inline
int ArrayList<TYPE>::insertAt(const TYPE& item, size_t index, size_t numItems) {
  return ArrayListImpl::insertAt(&item, index, numItems);
}

template<class TYPE> inline
int ArrayList<TYPE>::insertArrayAt(const TYPE* array, size_t index, size_t len) {
  return ArrayListImpl::insertArrayAt(array, index, len);
}

template<class TYPE> inline
int ArrayList<TYPE>::appendArray(const TYPE* array, size_t length) {
  return ArrayListImpl::appendArray(array, length);
}

template<class TYPE> inline
int ArrayList<TYPE>::insertArrayListAt(const ArrayList<TYPE>& o, size_t index) {
  return ArrayListImpl::insertArrayListAt(reinterpret_cast<const ArrayListImpl&>(o), index);
}

template<class TYPE> inline
int ArrayList<TYPE>::appendArrayList(const ArrayList<TYPE>& o) {
  return ArrayListImpl::appendArrayList(reinterpret_cast<const ArrayListImpl&>(o));
}

template<class TYPE> inline
int ArrayList<TYPE>::removeItemsAt(size_t index, size_t count) {
  return ArrayListImpl::removeItemsAt(index, count);
}

template<class TYPE> inline
const TYPE* ArrayList<TYPE>::array() const {
  return static_cast<const TYPE*>(arrayImpl());
}

template<class TYPE> inline
TYPE* ArrayList<TYPE>::editArray() {
  return static_cast<TYPE*>(editArrayImpl());
}

template<class TYPE>
void ArrayList<TYPE>::do_construct(void* storage, size_t num) const {
  construct_type(reinterpret_cast<TYPE*>(storage), num);
}

template<class TYPE>
void ArrayList<TYPE>::do_destroy(void* storage, size_t num) const {
  destroy_type(reinterpret_cast<TYPE*>(storage), num);
}

template<class TYPE>
void ArrayList<TYPE>::do_copy(void* dest, const void* from, size_t num) const {
  copy_type(reinterpret_cast<TYPE*>(dest), reinterpret_cast<const TYPE*>(from), num);
}

template<class TYPE>
void ArrayList<TYPE>::do_splat(void* dest, const void* item, size_t num) const {
  splat_type(reinterpret_cast<TYPE*>(dest), reinterpret_cast<const TYPE*>(item), num);
}

template<class TYPE>
void ArrayList<TYPE>::do_move_forward(void* dest, const void* from, size_t num) const {
  move_forward_type(reinterpret_cast<TYPE*>(dest), reinterpret_cast<const TYPE*>(from), num);
}

template<class TYPE>
void ArrayList<TYPE>::do_move_backward(void* dest, const void* from, size_t num) const {
  move_backward_type(reinterpret_cast<TYPE*>(dest), reinterpret_cast<const TYPE*>(from), num);
}

template<class TYPE>
void ArrayList<TYPE>::clear() {
  ArrayListImpl::clear();
}

} // namespace pivot

#endif // PIVOT_ARRAYLIST_H
