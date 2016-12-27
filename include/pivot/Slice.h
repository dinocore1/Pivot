#ifndef PIVOT_SLICE_H
#define PIVOT_SLICE_H

namespace pivot {

template <typename T>
class Slice {
public:
  Slice()
   : mData(NULL), mLength(0) {}

  Slice(T* data, size_t size)
   : mData(data), mLength(size) { }

  Slice(const Slice& copy)
   : mData(copy.mData), mLength(copy.mLength) { }

  size_t length() const {
    return mLength;
  }

  const T operator[](size_t i) const {
    return mData[i];
  }

  T& operator[](size_t i) {
    return mData[i];
  }

private:
  T* mData;
  size_t mLength;

};



} // namespace pivot

#endif // PIVOT_SLICE_H
