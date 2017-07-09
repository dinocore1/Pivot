#ifndef PIVOT_STATUS_H
#define PIVOT_STATUS_H

//#include <sys/types.h>
#include <errno.h>

namespace pivot {

typedef int32_t status_t;

// Win32 #defines NO_ERROR as well.  It has the same value, so there's no
// real conflict, though it's a bit awkward.
#ifdef _WIN32
# undef NO_ERROR
#endif

enum {
  OK = 0,
  NO_ERROR = 0,
  UNKNOWN_ERROR = 0x80000000,
  NO_MEMORY = -ENOMEM,
  BAD_INDEX = -EACCES,
  BAD_VALUE = -EINVAL
};

} // namespace pivot

#endif // PIVOT_STATUS_H
