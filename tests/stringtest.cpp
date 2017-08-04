#include <pivot/Pivot.h>

#include <stdio.h>

using namespace pivot;

String8 createString() {
    return String8("hello world");
}

int main() {

  String8 fmt;
  fmt.appendFormat("%g %g", 4.0, 2.0);
  printf("%s\n", (const char*)fmt);

  String8 str2;
  str2 = createString();
  printf("done %s\n", (const char*)str2);

  //String8 str3 = String8("this ") + "is cool";
  //printf("str3: %s\n", (const char*)str3);

  return 0;
}
