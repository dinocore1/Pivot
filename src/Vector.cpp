#include "config.h"
#include <pivot/Pivot.h>

namespace Pivot {



VectorImpl::VectorImpl(size_t itemSize, uint32_t flags)
 : mFlags(flags), mItemSize(itemSize), mStorage(NULL), mCount(0) {}

VectorImpl::VectorImpl(const VectorImpl& rhs)
 : mStorage() {

}


} // namespace Pivot
