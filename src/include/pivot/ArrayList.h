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
  void finish_vector();

  inline size_t size() const;
  size_t capacity() const;
  void clear();
  inline const size_t itemSize() const;

  inline const void* arrayImpl() const;
  void* editArrayImpl();

  int insertAt(const void* item, size_t index, size_t numItems = 1);
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

  //! same as push() but returns the index the item was added at (or an error)
  int add(const TYPE& item);


  /*
  //! insert one or several items initialized with their default constructor
  inline  ssize_t insertAt(size_t index, size_t numItems = 1);
  //! insert one or several items initialized from a prototype item
  ssize_t insertAt(const TYPE& prototype_item, size_t index, size_t numItems = 1);
  //! pop the top of the stack (removes the last element). No-op if the stack's empty
  inline  void pop();
  //! pushes an item initialized with its default constructor
  inline  void push();
  //! pushes an item on the top of the stack
  void push(const TYPE& item);
  //! same as push() but returns the index the item was added at (or an error)
  inline ssize_t add();
  //! replace an item with a new one initialized with its default constructor
  inline ssize_t replaceAt(size_t index);
  //! replace an item with a new one
  ssize_t replaceAt(const TYPE& item, size_t index);

  //! remove several items
  inline  ssize_t         removeItemsAt(size_t index, size_t count = 1);
  //! remove one item
  inline  ssize_t         removeAt(size_t index)  { return removeItemsAt(index); }
  */

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
ArrayList<TYPE>::~ArrayList() {
  finish_vector();
}

template<class TYPE> inline
int ArrayList<TYPE>::add(const TYPE& item) {
    return ArrayListImpl::add(&item);
}

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
