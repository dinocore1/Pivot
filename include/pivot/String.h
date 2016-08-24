#ifndef PIVOT_STRING_H
#define PIVOT_STRING_H

namespace Pivot {

class String {
public:
  virtual ~String();

  String();
  String(const char*);

  size_t length();

private:
  size_t mLength;
  char* mData;

};

} // namespace Pivot

#endif // PIVOT_STRING_H
