#ifndef PIVOT_STRING_H
#define PIVOT_STRING_H

namespace pivot {

class String8 {
public:
  String8();
  String8(const String8&);
  explicit String8(const char*);
  explicit String8(const char*, size_t numChars);
  ~String8();

  static inline const String8 empty();

  static String8 format(const char* fmt, ...)
#if defined(__GNUC__)
  __attribute__((format(printf, 1, 2)))
#endif
  ;
  static String8 formatV(const char* fmt, va_list args);

  inline size_t length() const;
  inline size_t bytes() const;

  status_t append(const String8&);
  status_t append(const char*);
  status_t append(const char*, size_t numChars);
  status_t appendFormat(const char* fmt, ...)
#if defined(__GNUC__)
  __attribute__((format(printf, 2, 3)))
#endif
  ;
  status_t appendFormatV(const char* fmt, va_list);


  inline String8& operator=(const String8&);

  inline String8& operator+=(const String8&);
  inline String8 operator+(const String8&) const;

  int compare(const String8& other) const;

  inline bool operator<(const String8&) const;
  inline bool operator<=(const String8&) const;
  inline bool operator==(const String8&) const;
  inline bool operator!=(const String8&) const;
  inline bool operator>(const String8&) const;
  inline bool operator>=(const String8&) const;

  void clear();
  void setTo(const String8&);
  status_t setTo(const char*);
  status_t setTo(const char*, size_t len);

  inline const char* string() const;
  inline operator const char* () const;

  char* lockBuffer(size_t size);
  void unlockBuffer();
  status_t unlockBuffer(size_t size);

private:
  const char* mString;

  status_t real_append(const char* other, size_t numChars);

};

inline const String8 String8::empty() {
  return String8();
}

inline size_t String8::length() const {
  return SharedBuffer::sizeFromData(mString) - 1;
}

inline size_t String8::bytes() const {
  return SharedBuffer::sizeFromData(mString) - 1;
}

inline String8& String8::operator+=(const String8& o) {
  append(o);
  return *this;
}

inline String8 String8::operator+(const String8& o) const {
  String8 tmp(*this);
  tmp += o;
  return tmp;
}

inline String8& String8::operator=(const String8& other) {
  setTo(other);
  return *this;
}

//inline int String8::compare(const String8& other) const {
//  return strcmp(mString, other.mString);
//}

inline bool String8::operator<(const String8& o) const {
  return compare(o) < 0;
}

inline bool String8::operator<=(const String8& o) const {
  return compare(o) <= 0;
}

inline bool String8::operator==(const String8& o) const {
  return compare(o) == 0;
}

inline bool String8::operator!=(const String8& o) const {
  return compare(o) != 0;
}

inline bool String8::operator>(const String8& o) const {
  return compare(o) > 0;
}

inline bool String8::operator>=(const String8& o) const {
  return compare(o) >= 0;
}

inline const char* String8::string() const {
  return mString;
}

inline String8::operator const char* () const {
  return mString;
}

} // namespace pivot

#endif // PIVOT_STRING_H
