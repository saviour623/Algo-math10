#include <string.h>
#include <fenv.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <gmp.h>
#define generic_reversebuff(ARR, ST, LEN)\
  do {\
  --LEN;\
  while (ST < LEN){\
  ARR[ST] ^= ARR[LEN];\
  ARR[LEN] ^= ARR[ST];\
  ARR[ST++] ^= ARR[LEN--];\
  }\
  }\
  while (0)

#define INT_ALERT(val)((int)(cos(M_PI * val)))
#define PERFECT_ROOT(_base, _exp)(INT_ALERT((log10(_base))/(log10(_exp))))
#define POWER2(v) ((v) && !(v & (v-1)))
#define GET_N(b, n)((log10(n))/(log10(b)))
#define BIT_CNT(bit)() //TODO
#define UNUSED(val)(void)val

/* bitsize of an integer, n, is exactly ceil(log(abs(n) + 1)), however to account for the sign bit we could add 1 */
#define size(n) ((size_t)(1 + ceil(log(abs(n) + 1))))
#define NOT(EXP) (!(EXP))

typedef uint64_t math_i64_bit;
