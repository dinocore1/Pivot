#include <gtest/gtest.h>

#include <pivot/Pivot.h>

using namespace pivot;

TEST(SharedBuffer, create) {
  SharedBuffer* sb = SharedBuffer::alloc(16);
  memcpy(sb->data(), "hello world", 11);

  sb->release();
}
