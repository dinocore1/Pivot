
#include <gtest/gtest.h>

#include <pivot/Pivot.h>

using namespace pivot;

TEST(ArrayList, create) {
  ArrayList<int> list;
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	const int retval = RUN_ALL_TESTS();
  return retval;
}