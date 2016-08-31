#ifndef PIVOT_STRING_H
#define PIVOT_STRING_H

namespace Pivot {

class String {
public:
  virtual ~String();

  String();
  String(const String&);
  String(const char*);

  size_t length() const;
  operator const char* () const;
  String operator+(const String&);

#if (__cpluplus >= 201103L)
  String(String&&);
  String& operator=(String&&);
#endif


private:
  size_t mLength;
  char* mData;

};

} // namespace Pivot

#endif // PIVOT_STRING_H
