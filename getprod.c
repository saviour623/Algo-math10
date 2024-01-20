#include "fiden.h"
#include <float.h>
#include <string.h>

#define PASS (void)0
#define BITS_EXPECT_R 1024
const static int precalc_pow[PRECALC_COL_SIZE][PRECALC_ROW_SIZE] = PRECALC_POW5_TABLE();

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
		bit_id = (bit_id << 1) | 1;
		if (!(*str & 0x0f))
			k = (k << 1) + 2;
		else {
			bit_id = bit_id - k;
			k = 0;
		}
	}
	return bit_id;
}
math_i64_bit getIdentityFromBits_i(math_i64_bit n, size_t bitsize)
{
	register math_i64_bit bit_id = 0, k = 0, r = 0;
	register math_i64_bit s = 1ULL << bitsize;

	for (; s; s >>= 1)
	{
		bit_id = (bit_id << 1) | 1;
		if (! (n & s))
		{
			k = (k << 1) + 2;
			continue;
		}
		bit_id = bit_id - k;
		k = 0;
	}
	return bit_id;
}

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
#ifdef __GNUC__
__attribute__((gnu_inline))
#endif
inline math_i64_bit pow5(int n)
{
	register math_i64_bit xn = 5;
	for (--n; n--;)
		xn = (xn << 2) + xn;
	return xn;
}
__attribute__((nonnull, gnu_inline))
inline int extpow54(int n, int * restrict res)
{
	int k, h;
	int tmpbf[2][MIN_ULMB_SIZE];

	k = h = MIN_ULMB_SIZE;
	if (n < 27)
	{
		(void) toLimb(res, &h, pow5(n));
		return h;
	}
	n -= 27;
	return BigMul(res, toLimb(tmpbf[0], &k, pow5(27)), k, toLimb(tmpbf[1], &h, pow5(n)), h);
}
char *fltoStr(double db_nput, size_t prec)
{
	int bfn[25];
	int lmb[15];
	int lmb2[15];
	int lmbsize;
	math_i64_bit bit;
	math_i64_bit exp, mant, sign;
	int k, h, len; /* tmp variables */

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
	bitinfo.F = db_nput;
	exp = abs(((bitinfo.U & 0xfff0000000000000) >> 52) - 1023) + 52;
	mant = ((bitinfo.U & 0xfffffffffffff) | 0x10000000000000);
	mant >>= prec < 7 ? (exp -= 32), 32 : prec < 11 ? (exp -= 16), 16 : 0;

	k = h = len = MIN_ULMB_SIZE;
	if (exp < 55)
	{
		if (exp < 17)
			toLimb(bfn, &len, (mant * pow5(exp)));
		else if (exp < 28)
			len = BigMul(bfn, toLimb(lmb, &k, pow5(exp)), k, toLimb(lmb2, &h, mant), h);
   		else
		{
			len = extpow54(exp, lmb);
			len = BigMul(bfn, lmb, len, toLimb(lmb2, &k, mant), k);
		}
		goto edit;
	}
	bit = getIdentityFromBits_i(mant, 20);
	//lmbsize = toLimb(lmb, 5, mant);
edit:
	if (prec < 7)
	{
#if defined(HONOUR_ROUND)
#endif
	}
//	print(bfn);
}
int main(void){
	size_t sizevar = 256;
	int n = 0;
	double t = 0.12659876;//0.1723462375345345005;
	clock_t time;
	char *s = getFltBits(t, &sizevar, (char[1024]){0});
	startTime(time);
	fltoStr(t, 6);
	stopTime(time);
	printTime(time);
	printf("pow %llu\n", pow5(27));
	printf("%u\n", strlen(s));
	puts(s);
	printf("%f\n", t);
	printf("mant_i %llu\n", getIdentityFromBits(s));
	printf("%d\n", FLT_ROUNDS);
}
/*10000011010111000111110011011000100110001011*
  0.13562

  56700
  
*/
