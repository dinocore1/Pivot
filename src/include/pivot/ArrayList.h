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
  inline const size_t itemSize() const;

  inline const void* arrayImpl() const;
  void* editArrayImpl();

  int insertAt(const void* item, size_t index, size_t numItems);
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

  const TYPE& operator[](size_t index) const;

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
template<typename T> struct trait_trivial_move<ArrayList<T> > { enum { value = true }; };


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

  template<class TYPE>
  void ArrayList<TYPE>::do_construct(void* storage, size_t num) const {
      construct_type( reinterpret_cast<TYPE*>(storage), num );
  }

  template<class TYPE>
  void ArrayList<TYPE>::do_destroy(void* storage, size_t num) const {
      destroy_type( reinterpret_cast<TYPE*>(storage), num );
  }

  template<class TYPE>
  void ArrayList<TYPE>::do_copy(void* dest, const void* from, size_t num) const {
      copy_type( reinterpret_cast<TYPE*>(dest), reinterpret_cast<const TYPE*>(from), num );
  }

  template<class TYPE>
  void ArrayList<TYPE>::do_splat(void* dest, const void* item, size_t num) const {
      splat_type( reinterpret_cast<TYPE*>(dest), reinterpret_cast<const TYPE*>(item), num );
  }

  template<class TYPE>
  void ArrayList<TYPE>::do_move_forward(void* dest, const void* from, size_t num) const {
      move_forward_type( reinterpret_cast<TYPE*>(dest), reinterpret_cast<const TYPE*>(from), num );
  }

  template<class TYPE>
  void ArrayList<TYPE>::do_move_backward(void* dest, const void* from, size_t num) const {
      move_backward_type( reinterpret_cast<TYPE*>(dest), reinterpret_cast<const TYPE*>(from), num );
  }

} // namespace pivot

#endif PIVOT_ARRAYLIST_H
