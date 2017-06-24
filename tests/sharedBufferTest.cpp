#include <gtest/gtest.h>

#include <pivot/Pivot.h>

using namespace pivot;

TEST(SharedBuffer, create) {
  SharedBuffer* sb = SharedBuffer::alloc(16);
  memcpy(sb->data(), "hello world", 11);
  
  sb->release();
}


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	const int retval = RUN_ALL_TESTS();
  return retval;
}
