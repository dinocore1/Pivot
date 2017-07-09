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

private:
  ptr_t mPtr;
};

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




} // namespace pivot

#endif // PIVOT_MEMORY
