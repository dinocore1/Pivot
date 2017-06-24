#ifndef PIVOT_STATUS_H
#define PIVOT_STATUS_H

//#include <sys/types.h>
#include <errno.h>

namespace pivot {

typedef int32_t status_t;

enum {
  OK = 0,
  UNKNOWN_ERROR = 0x80000000,
  NO_MEMORY = -ENOMEM,
  BAD_INDEX = -EACCES
};

} // namespace pivot

#endif // PIVOT_STATUS_H
