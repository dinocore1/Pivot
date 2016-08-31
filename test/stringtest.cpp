

#include <pivot/Pivot.h>

using namespace Pivot;

String createString() {
    return String("hello world");
}

int main() {
  String str2;
  str2 = createString();
  printf("done %s\n", (const char*)str2);

  String str3 = String("this ") + "is cool";
  printf("str3: %s\n", (const char*)str3);

  return 0;
}
