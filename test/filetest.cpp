#include <pivot/Pivot.h>
#include <pivot/File.h>

using namespace Pivot;

int main() {

  String8 s("testfile.txt");
  File f(s);
  if(f.exists()) {
    printf("it exists\n");
  }

  FileOutputStream fout(f);


  return 0;
}
