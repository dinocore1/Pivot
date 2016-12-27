#ifndef PIVOT_STRING_H
#define PIVOT_STRING_H

namespace pivot {

class String8 {
public:
  virtual ~String8();

  String8();
  String8(const String8&);
  String8(const char*);

  size_t length() const;
  operator const char* () const;
  String8 operator+(const String8&);

#if (__cpluplus >= 201103L)
  String8(String&&);
  String8& operator=(String8&&);
#endif


private:
  size_t mLength;
  char* mData;

};

} // namespace pivot

#endif // PIVOT_STRING_H
