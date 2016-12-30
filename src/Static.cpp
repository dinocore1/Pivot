
#include <Pivot/Pivot.h>
#include <Static.h>

namespace pivot {

extern void initialize_string8();
extern void terminate_string8();

LibPivotStatics::LibPivotStatics() {
  initialize_string8();
}

LibPivotStatics::~LibPivotStatics() {
  terminate_string8();
}


} // namespace pivot
