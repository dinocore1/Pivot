#ifndef PIVOT_VIEW_H
#define PIVOT_VIEW_H

namespace pivot {


template<class Derived>
class range_view {
public:
  Derived& begin() const;
  Derived& end() const;
};


template<class T>
class vector_view : public range_view<std::vector<T>::iterator> {
public:
  vector_view(const Derived& begin, const Derived& end)
   : mBegin(begin), mEnd(end) {}

  vector_view(std::vector<T>& v)
   : mBegin(v.begin()), mEnd(v.end()) {}

  Derived& begin() const {
    return mBegin;
  }

  Derived& end() const {
    return mEnd;
  }

private:
  Derived mBegin;
  Derived mEnd;
};



} // namespace pivot

#endif // PIVOT_VIEW_H
