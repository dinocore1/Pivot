#ifndef PIVOT_OPTIONAL_H
#define PIVOT_OPTIONAL_H

namespace pivot {

template<typename T>
class Optional {
public:
  Optional();
  ~Optional();
  Optional(const T& obj);

  bool isInitialized() const;
  operator bool() const;
  void clear();
  T& get();
  T& operator= (const T&);
  operator T&();

private:
  bool mInitialized;
  uint8_t mData[sizeof(T)];
};

template<typename T>
Optional<T>::Optional()
 : mInitialized(false) {
}

template<typename T>
Optional<T>::~Optional() {
	clear();
}

template<typename T>
Optional<T>::Optional(const T& obj) {
  get() = obj;
  mInitialized = true;
}

template<typename T>
bool Optional<T>::isInitialized() const {
	return mInitialized;
}

template<typename T>
Optional<T>::operator bool() const {
	return mInitialized;
}

template<typename T>
void Optional<T>::clear() {
	if (mInitialized) {
		reinterpret_cast<T*>(mData)->~T();
		mInitialized = false;
	}
}

template<typename T>
T& Optional<T>::get() {
  return reinterpret_cast<T*>(mData);
}

template<typename T>
T& Optional<T>::operator= (const T& obj) {
	T& retval = *reinterpret_cast<T*>(mData);
	retval = obj;
	mInitialized = true;
	return retval;
}

template<typename T>
Optional<T>::operator T&() {
	return *reinterpret_cast<T*>(mData);
}

} // namespace pivot


#endif // PIVOT_OPTIONAL_H
