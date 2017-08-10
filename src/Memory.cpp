#include <pivot/Pivot.h>

namespace pivot {


RefCountObj::RefCountObj(void* data, uint32_t flags)
  : mData(data), mFlags(flags), mStrongRefs(1), mWeakRefs(1)
{
}

void RefCountObj::retainStrong() {
  pivot_atomic_inc(&mStrongRefs);
  pivot_atomic_inc(&mWeakRefs);
}


} // namespace pivot
