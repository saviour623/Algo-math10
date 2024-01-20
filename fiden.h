#include <string.h>
#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>
#include <gmp.h>
#include "lookup.h"
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
#define _BASE_RADIX 2
#define _RADIX 5
#define _PRECALC_POW5TH 125
#define PRECALC_MIN 49
#define PRECALC_MAX _PRECALC_POW5TH
#define RADIX_ULLMAX 27
#define MIN_ULMB_SIZE 5
#define END -1024
#define _FETCH_PRECALC_LOC(n)\
	(((n) > 49 && (n) < 64) ? powLookUpTable64[n] : ((n) > 64 && (n) < 96) ? \
	 powLookUpTable95[n] : ((n) > 95 && (n) < 126) ? powLookUpTable95[n] ? NULL)

#define startTime(n) ((n) = clock())
#define stopTime(n) ((n) = clock() - (n))
#define printTime(n) printf("%f\n", (n) / (double) CLOCKS_PER_SEC)

math_i64_bit getIdentityFromBits(const char *__restrict__ str);
char *getFltBits(double nput, size_t *numBit, char *bits_bf);
char *fltoStr(double db_nput, size_t dig_output);
int BigMul(int bigMulResult[], const int lmb1[], int s1, const int lmb2[], int s2);
__attribute__((nonnull)) int *toLimb(int lmbBf[], int *size, math_i64_bit val);
math_i64_bit pow5(int);
int extpow54(int n, int * restrict res);
void print(int *n);
