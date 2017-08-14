#include <pivot/Pivot.h>

#include <gtest/gtest.h>


using namespace pivot;

static int numDeleted = 0;
struct MyObj {

  ~MyObj() {
    numDeleted++;
  }
};

TEST(Memory, StrongPointer) {

  {
    sp<MyObj> obj3;
    sp<MyObj> obj1 = new MyObj();
    {
      sp<MyObj> obj2 = obj1;
      obj3 = obj2;
    }
  }

  EXPECT_EQ(1, numDeleted);
}
