#include <pivot/Pivot.h>

namespace pivot {


RefCountObj::RefCountObj(void* data, uint32_t flags)
  : mData(data), mFlags(flags), mStrongRefs(1), mWeakRefs(0)
{
}


} // namespace pivot
