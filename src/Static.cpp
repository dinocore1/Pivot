
#include <pivot/Pivot.h>
#include <Static.h>

FORCE_LINK_THIS(staticInit)

namespace pivot {

extern void initialize_string8();
extern void terminate_string8();

class LibPivotStatics {
public:
  LibPivotStatics();
  ~LibPivotStatics();
};

LibPivotStatics::LibPivotStatics() {
  initialize_string8();
}

LibPivotStatics::~LibPivotStatics() {
  terminate_string8();
}

static LibPivotStatics gTheStaticObj;

} // namespace pivot
