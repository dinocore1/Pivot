#ifndef PIVOT_STRING_H
#define PIVOT_STRING_H

namespace pivot {

class String8 {
public:  
  String8();
  String8(const String8&);
  String8(const char*);
  ~String8();

  inline size_t length() const;
  inline size_t bytes() const;

  status_t append(const String8&);

  inline String8& operator+=(const String8&);
  inline String8 operator+(const String8&) const;

  void setTo(const String8&);
  inline String8& operator=(const String8&);

  inline const char* string() const;
  inline operator const char*() const;

private:
  const char* mString;

  status_t real_append(const char* other, size_t numChars);

};

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

inline const char* String8::string() const {
	return mString;
}

inline String8::operator const char*() const {
	return mString;
}

} // namespace pivot

#endif // PIVOT_STRING_H
