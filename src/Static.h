
#define FORCE_LINK_THIS(x) int force_link_##x = 0;
#define FORCE_LINK_THAT(x) void force_linkf_##x() { extern int force_link_##x; force_link_##x = 1; }

namespace pivot {



} // namespace pivot
