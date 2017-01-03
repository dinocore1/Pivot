#ifndef PIVOT_TYPEHELPERS_H
#define PIVOT_TYPEHELPERS_H

namespace pivot {

template <typename T> struct trait_trivial_ctor {
  enum { value = false };
};
template <typename T> struct trait_trivial_dtor {
  enum { value = false };
};
template <typename T> struct trait_trivial_copy {
  enum { value = false };
};
template <typename T> struct trait_trivial_move {
  enum { value = false };
};
template <typename T> struct trait_pointer      {
  enum { value = false };
};
template <typename T> struct trait_pointer<T*>  {
  enum { value = true };
};


template <typename TYPE>
struct traits {
  enum {
    is_pointer = trait_pointer<TYPE>::value,

    // whether this type's constructor is a no-op
    has_trivial_ctor = is_pointer || trait_trivial_ctor<TYPE>::value,

    // whether this type's destrutor is a no-op
    has_trivial_dtor = is_pointer || trait_trivial_dtor<TYPE>::value,

    // whether this type can be copy-constructed with memcpy
    has_trivial_copy = is_pointer || trait_trivial_copy<TYPE>::value,

    // whether this type can be moved with memmove
    has_trivial_move = is_pointer || trait_trivial_move<TYPE>::value

  };
};

} // namespace pivot

#endif // PIVOT_TYPEHELPERS_H
