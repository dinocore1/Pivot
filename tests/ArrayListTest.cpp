
#include <gtest/gtest.h>

#include <pivot/Pivot.h>

using namespace pivot;

TEST(ArrayList, addItem) {
  ArrayList<int> list;
  list.add(42);
  EXPECT_EQ(1, list.size());
  EXPECT_EQ(42, list[0]);

  list.add(66);
  EXPECT_EQ(2, list.size());
  EXPECT_EQ(42, list[0]);
  EXPECT_EQ(66, list.itemAt(1));
}

TEST(ArrayList, deleteItem) {
  ArrayList<int> list;
  list.add(42);
  list.add(55);
  list.add(68);

  list.removeAt(1);
  EXPECT_EQ(2, list.size());
  EXPECT_EQ(42, list[0]);
  EXPECT_EQ(68, list.itemAt(1));
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	const int retval = RUN_ALL_TESTS();
  return retval;
}
