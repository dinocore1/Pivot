#include <pivot/Pivot.h>

using namespace Pivot;

int main() {

  int buf[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  Slice<int> s(&buf[2], 3);
  printf("s0: %d\n", s[0]);
  s[0] = 8;
  printf("s0: %d\n", s[0]);
  printf("s1: %d\n", s[1]);


  return 0;
}
