#include <pivot/Pivot.h>
#include <pivot/File.h>

using namespace Pivot;

int main() {

  File f("testfile.txt");
  if(f.exists()) {
    printf("it exists\n");
  }


  return 0;
}
