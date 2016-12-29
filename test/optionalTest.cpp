#include <pivot/Pivot.h>

#include <cstdio>
#include <utility>

using namespace pivot;

class Obj {

public:
	static Obj&& createWithNum(int num) {
		Obj retval;
		retval.i = num;
		return std::move(retval);
	}

	~Obj() {
		printf("~Obj() called\n");
	}

	int getNum() const {
		return i;
	}

private:
	int i;

};

int main() {

  Optional<Obj> myObj;
  printf("%d \n", myObj.isInitialized());

  Obj a = Obj::createWithNum(5);
  myObj = a;
  printf("%d \n", ((Obj&)myObj).getNum());


  return 0;
}
