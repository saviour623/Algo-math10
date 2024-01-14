#include "fiden.h"
#include <float.h>
#include <string.h>

#define PASS (void)0
#define BITS_EXPECT_R 256

static inline math_i64_bit logbase2(math_i64_bit n)
{
  uint16_t r = 0;

  while (((n >>= 1) && r++))
	  ;
  return r-2;
}

static inline size_t sizeofuintmax_t(void)
{
  return sizeof (math_i64_bit);
}

char * bin(math_i64_bit tobin, char *__restrict__ buff)
{
  int oo = 0, st = 0;

  while (tobin){
	buff[oo] = (tobin & 1) + 48;
	tobin >>= 1;
	oo += 1;
  }
  generic_reversebuff(buff, st, oo);

  return buff;
}

math_i64_bit getIdentityFromBits(const char *__restrict__ str)
{
  register math_i64_bit bit_id = 0;
  register math_i64_bit k, r, oo;

  if (str == NULL || *str == 0)
	  return 0;
  k = r = 0;
  /* id = p - k. let p = 2r + 1 and k = 2c + 2; where r and c is dependent on p and k, thus: r = p or 0, and c = k or 0
   * however here, both id and r is the same, as well as k and c */
  for (; *str != 0; str++)
  {
	bit_id = (bit_id << 1) + 1;
	if (!(*str & 0x0f))
	  k = (k << 1) + 2;
	else {
	  bit_id = bit_id - k;
	  k = 0;
	}
  }
  return bit_id;
}

#define cast_to_i64(n) ((math_i64_bit)(n))
char *getFltBits(double nput, size_t *numBit, char *bits_bf)
{
	register size_t oo, nmax;

	if (numBit == NULL || *numBit <= 0)
		return NULL;

	nmax = *numBit;
	for (oo = 0; (oo < nmax) && (nput != 0.0); oo++)
	{
		nput += nput;
		bits_bf[oo] = 48 | !!(unsigned int) nput;
		if (nput >= 1.0)
			nput -= 1.0;
	}
	bits_bf[oo] = 0;
	*numBit = oo;
	return bits_bf;
}

char *fltoStr(double db_nput, size_t dig_output)
{
	char nbitBuf[BITS_EXPECT_R];
	math_i64_bit fid;
	int exp, rawmant, sign;

	union {
		double F;
		math_i64_bit U;
	} bitinfo;

	if (db_nput == 0.0)
		return "0.0";

	if (db_nput < 0)
	{
		sign = 1;
		db_nput = -db_nput;
	}
	exp = (((bitinfo.U << 1) & 0x0ffe000000000000) >> 52) - 1023;
	rawmant = (bitinfo.U << 1) & ~0x0ffe000000000000;
	fid = getIdentityFromBits( getFltBits(db_nput, &dig_output, nbitBuf) );

	if (exp > 0)
		PASS;
}
int main(void){
  size_t sizevar = 64;
  int n = 0;
  long double t = 0.1723462375345345005;
  clock_t time;

  startTime(time);
  char *s = getFltBits(t, &sizevar, (char[65]){0});
  stopTime(time);
  printTime(time);

  printf("%ld\n", strlen(s));
  puts(s);
  printf("%.23Lf\n", t);
  printf("%lu\n", getIdentityFromBits(s));
}
/*10000011010111000111110011011000100110001011*
0.13562
*/
