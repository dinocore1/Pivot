#ifndef PIVOT_MEMORY
#define PIVOT_MEMORY

namespace pivot {

template<typename T>
class up {
public:
  typedef T* ptr_t;

  explicit up();
  explicit up(ptr_t);

  ~up();
  T* release();
  void reset(T* p = 0);
  T* operator-> ();
  const T* operator-> () const;
  bool operator()() const;
  up& operator=(const up&) = delete;

private:
  ptr_t mPtr;
};

class RefCountObj {
public:
  enum {
    HAS_TRIVIAL_CTOR = 0x00000001,
    HAS_TRIVIAL_DTOR = 0x00000002,
    HAS_TRIVIAL_COPY = 0x00000004
  };

  RefCountObj(void* data, uint32_t flags);

  void retainStrong();

  void* mData;
  const uint32_t mFlags;
  mutable pivot_atomic_int_t_dec pivot_atomic_int_t mStrongRefs;
  mutable pivot_atomic_int_t_dec pivot_atomic_int_t mWeakRefs;

};

template<typename T>
class wp;

template<typename T>
class sp {
public:
  typedef T* ptr_t;

  explicit sp();
  sp(ptr_t);
  sp(const sp&);
  sp(const wp<T>&);
  ~sp();

  inline bool isValid() const;
  inline T* operator-> ();
  inline const T* operator-> () const;
  sp<T>& operator= (const sp<T>&);

private:
  inline RefCountObj* getRefObj() const;
  void retain() const;
  void release();
  void* mPtr;
};

template<typename TYPE>
class wp {
public:
  wp(const sp<TYPE>&);

  inline bool isValid() const;
  bool operator()() const;
private:
  inline RefCountObj* getRefObj() const;
  void* mPtr;
};


//////////////////// Weak Pointer    //////////////////


template<typename TYPE>
inline
bool wp<TYPE>::isValid() const {
  return getRefObj().mStrongRefs > 0;
}

template<typename TYPE>
inline
RefCountObj* wp<TYPE>::getRefObj() const {
  return static_cast<RefCountObj>(mPtr);
}


//////////////////// Strong Pointer ///////////////////

template<typename T>
sp<T>::sp()
 : mPtr(0)
{}

template<typename TYPE>
sp<TYPE>::sp(ptr_t ptr)
{
  mPtr = new RefCountObj(ptr,
    ((traits<TYPE>::has_trivial_ctor ? RefCountObj::HAS_TRIVIAL_CTOR : 0)
      | (traits<TYPE>::has_trivial_dtor ? RefCountObj::HAS_TRIVIAL_DTOR : 0)
      | (traits<TYPE>::has_trivial_copy ? RefCountObj::HAS_TRIVIAL_COPY : 0)
      )
  );
}

template<typename TYPE>
sp<TYPE>::sp(const sp<TYPE>& copy)
  : mPtr(copy.mPtr)
{
  retain();
}

template<typename TYPE>
sp<TYPE>::sp(const wp<TYPE>& copy)
  : mPtr(copy.mPtr)
{
  if (copy.isValid()) {
    retain();
  }
}

template<typename T>
sp<T>::~sp() {
  release();
}

template<typename TYPE>
void sp<TYPE>::retain() const {
  if (mPtr) {
    RefCountObj* ref = getRefObj();
    ref->retainStrong();
  }
}

template<typename TYPE>
void sp<TYPE>::release() {
  if (mPtr) {
    RefCountObj* ref = getRefObj();
    pivot_atomic_int_t newval;
    if ((newval = pivot_atomic_dec(&ref->mStrongRefs)) == 0) {
      delete static_cast<TYPE*>(ref->mData);
      ref->mData = 0;
    }

    if ((newval = pivot_atomic_dec(&ref->mWeakRefs)) == 0) {
      delete ref;
    }
    mPtr = 0;
  }
}


template<typename TYPE>
bool sp<TYPE>::isValid() const {
  return getRefObj().mStrongRefs > 0;
}

template<typename T>
T* sp<T>::operator-> () {
  return static_cast<T*>(getRefObj()->mData);
}

template<typename T>
const T* sp<T>::operator-> () const {
  T* retval = static_cast<T*>(getRefObj()->mData);
  return const_cast<const T*>(retval);
}

template<typename TYPE>
sp<TYPE>& sp<TYPE>::operator= (const sp<TYPE>& rhs) {
  rhs.retain();
  release();
  mPtr = rhs.mPtr;
  return *this;
}

template<typename T>
inline
RefCountObj* sp<T>::getRefObj() const {
  return static_cast<RefCountObj*>(mPtr);
}

//////////////////// Unique Pointer ///////////////////

template<typename T>
up<T>::up()
  : mPtr(0) {}


template<typename T>
up<T>::up(ptr_t p)
  : mPtr(p) {}

template<typename T>
up<T>::~up() {
  reset();
}

template<typename T>
T* up<T>::release() {
  ptr_t retval = mPtr;
  mPtr = 0;
  return retval;
}

template<typename T>
void up<T>::reset(T* ptr) {
  if(mPtr != 0) {
    delete mPtr;
    mPtr = 0;
  }
  mPtr = ptr;
}

template<typename T>
T* up<T>::operator-> () {
  return mPtr;
}

template<typename T>
const T* up<T>::operator-> () const {
  return mPtr;
}

template<typename T>
bool up<T>::operator()() const {
  return mPtr != 0;
}

} // namespace pivot

#endif // PIVOT_MEMORY
