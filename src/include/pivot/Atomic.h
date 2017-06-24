#ifndef PIVOT_ATOMIC_H
#define PIVOT_ATOMIC_H


#ifdef __cplusplus
extern "C" {
#endif

int32_t pivot_atomic_inc(volatile int32_t* addr);
int32_t pivot_atomic_dec(volatile int32_t* addr);

#if defined(__GNUC__)

inline int32_t pivot_atomic_inc(volatile int32_t* addr) {
  return __atomic_add_fetch(addr, 1, __ATOMIC_RELAXED);
}

inline int32_t pivot_atomic_dec(volatile int32_t* addr) {
  return __atomic_sub_fetch(addr, 1, __ATOMIC_RELAXED);
}

#elif defined(WIN32)

#include <Windows.h>

inline int32_t pivot_atomic_inc(volatile int32_t* addr) {
  return InterlockedIncrement((LONG volatile*)addr);
}

inline int32_t pivot_atomic_dec(volatile int32_t* addr) {
  return InterlockedDecrement((LONG volatile*)addr);
}

#elif defined(__i386__) || defined(__x86_64__)

extern inline int32_t pivot_atomic_add(int32_t increment, volatile int32_t* ptr) {
  __asm__ __volatile__("lock; xaddl %0, %1"
                       : "+r"(increment), "+m"(*ptr)
                       : : "memory");
  /* increment now holds the old value of *ptr */
  return increment;
}

extern inline int32_t pivot_atomic_inc(volatile int32_t* addr) {
  return pivot_atomic_add(1, addr);
}

extern inline int32_t pivot_atomic_dec(volatile int32_t* addr) {
  return pivot_atomic_add(-1, addr);
}

#else
#error atomic operation are unsupported
#endif


#ifdef __cplusplus
} // extern "C"
#endif


#endif // PIVOT_ATOMIC_H
