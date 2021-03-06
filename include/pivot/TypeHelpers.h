#ifndef PIVOT_TYPEHELPERS_H
#define PIVOT_TYPEHELPERS_H

namespace pivot {
/*
 * Types traits
 */

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
    // whether this type is a pointer
    is_pointer          = trait_pointer<TYPE>::value,
    // whether this type's constructor is a no-op
    has_trivial_ctor    = is_pointer || trait_trivial_ctor<TYPE>::value,
    // whether this type's destructor is a no-op
    has_trivial_dtor    = is_pointer || trait_trivial_dtor<TYPE>::value,
    // whether this type type can be copy-constructed with memcpy
    has_trivial_copy    = is_pointer || trait_trivial_copy<TYPE>::value,
    // whether this type can be moved with memmove
    has_trivial_move    = is_pointer || trait_trivial_move<TYPE>::value
  };
};

template <typename T, typename U>
struct aggregate_traits {
  enum {
    is_pointer          = false,
    has_trivial_ctor    =
      traits<T>::has_trivial_ctor && traits<U>::has_trivial_ctor,
    has_trivial_dtor    =
      traits<T>::has_trivial_dtor && traits<U>::has_trivial_dtor,
    has_trivial_copy    =
      traits<T>::has_trivial_copy && traits<U>::has_trivial_copy,
    has_trivial_move    =
      traits<T>::has_trivial_move && traits<U>::has_trivial_move
  };
};

#define ANDROID_TRIVIAL_CTOR_TRAIT( T ) \
      template<> struct trait_trivial_ctor< T >   { enum { value = true }; };

#define ANDROID_TRIVIAL_DTOR_TRAIT( T ) \
      template<> struct trait_trivial_dtor< T >   { enum { value = true }; };

#define ANDROID_TRIVIAL_COPY_TRAIT( T ) \
      template<> struct trait_trivial_copy< T >   { enum { value = true }; };

#define ANDROID_TRIVIAL_MOVE_TRAIT( T ) \
      template<> struct trait_trivial_move< T >   { enum { value = true }; };

#define ANDROID_BASIC_TYPES_TRAITS( T ) \
      ANDROID_TRIVIAL_CTOR_TRAIT( T ) \
      ANDROID_TRIVIAL_DTOR_TRAIT( T ) \
      ANDROID_TRIVIAL_COPY_TRAIT( T ) \
      ANDROID_TRIVIAL_MOVE_TRAIT( T )

// ---------------------------------------------------------------------------

/*
 * basic types traits
 */

ANDROID_BASIC_TYPES_TRAITS(void)
ANDROID_BASIC_TYPES_TRAITS(bool)
ANDROID_BASIC_TYPES_TRAITS(char)
ANDROID_BASIC_TYPES_TRAITS(unsigned char)
ANDROID_BASIC_TYPES_TRAITS(short)
ANDROID_BASIC_TYPES_TRAITS(unsigned short)
ANDROID_BASIC_TYPES_TRAITS(int)
ANDROID_BASIC_TYPES_TRAITS(unsigned int)
ANDROID_BASIC_TYPES_TRAITS(long)
ANDROID_BASIC_TYPES_TRAITS(unsigned long)
ANDROID_BASIC_TYPES_TRAITS(long long)
ANDROID_BASIC_TYPES_TRAITS(unsigned long long)
ANDROID_BASIC_TYPES_TRAITS(float)
ANDROID_BASIC_TYPES_TRAITS(double)

// ---------------------------------------------------------------------------

/*
 * create, destroy, copy and move types...
 */

template<typename TYPE> inline
void construct_type(TYPE* p, size_t n) {
  if(!traits<TYPE>::has_trivial_ctor) {
    while(n--) {
      new(p++) TYPE;
    }
  }
}

template<typename TYPE> inline
void destroy_type(TYPE* p, size_t n) {
  if(!traits<TYPE>::has_trivial_dtor) {
    while(n--) {
      p->~TYPE();
      p++;
    }
  }
}

template<typename TYPE> inline
void copy_type(TYPE* d, const TYPE* s, size_t n) {
  if(!traits<TYPE>::has_trivial_copy) {
    while(n--) {
      new(d) TYPE(*s);
      d++, s++;
    }
  } else {
    memcpy(d,s,n*sizeof(TYPE));
  }
}

template<typename TYPE> inline
void splat_type(TYPE* where, const TYPE* what, size_t n) {
  if(!traits<TYPE>::has_trivial_copy) {
    while(n--) {
      new(where) TYPE(*what);
      where++;
    }
  } else {
    while(n--) {
      *where++ = *what;
    }
  }
}

template<typename TYPE> inline
void move_forward_type(TYPE* d, const TYPE* s, size_t n = 1) {
  if((traits<TYPE>::has_trivial_dtor && traits<TYPE>::has_trivial_copy)
      || traits<TYPE>::has_trivial_move) {
    memmove(d,s,n*sizeof(TYPE));
  } else {
    d += n;
    s += n;
    while(n--) {
      --d, --s;
      if(!traits<TYPE>::has_trivial_copy) {
        new(d) TYPE(*s);
      } else {
        *d = *s;
      }
      if(!traits<TYPE>::has_trivial_dtor) {
        s->~TYPE();
      }
    }
  }
}

template<typename TYPE> inline
void move_backward_type(TYPE* d, const TYPE* s, size_t n = 1) {
  if((traits<TYPE>::has_trivial_dtor && traits<TYPE>::has_trivial_copy)
      || traits<TYPE>::has_trivial_move) {
    memmove(d,s,n*sizeof(TYPE));
  } else {
    while(n--) {
      if(!traits<TYPE>::has_trivial_copy) {
        new(d) TYPE(*s);
      } else {
        *d = *s;
      }
      if(!traits<TYPE>::has_trivial_dtor) {
        s->~TYPE();
      }
      d++, s++;
    }
  }
}

// ---------------------------------------------------------------------------



} // namespace pivot

#endif // PIVOT_TYPEHELPERS_H
