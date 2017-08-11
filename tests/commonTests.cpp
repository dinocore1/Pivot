#include <pivot/Pivot.h>

#include <gtest/gtest.h>


using namespace pivot;

TEST(Memory, StrongPointer) {

  struct MyObj {

    bool mDeleted;
    MyObj()
      : mDeleted(false) {}

    ~MyObj() {
      mDeleted = true;
      std::cout << "deleted" << std::endl;
    }
  };

  sp<MyObj> obj1 = new MyObj();
  {
    sp<MyObj> obj2 = obj1;
  }
}
