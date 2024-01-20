#include "fiden.h"
#include "lookup.h"
#include <time.h>
#include <stdbool.h>

#define reverseBf generic_reversebuff
#define mulAdd(a, b, c)\
	(((U64)(a) * (U64)(b)) + ((U64)(c)))
#ifdef __GNUC__
     #define restrict __restrict__
#endif

#define PASS (void)0
#define LIMB_SZ 100000
#define FLIMB_SZ 0.00001L
#define MULSZ_MAX 1024

typedef uint64_t U64;
const int extPow10[] = {
	10, /* 1 */
	100, /* 2 */
	1000, /* 3 */
	10000, /* 4 */
	100000, /* 5 */
	1000000, /* 6 */
	10000000, /* 7 */
	100000000, /* 8 */
	1000000000, /* 8 */
};
#define B125_SIZE 18
const int P125[] = {B125_SIZE, 3125, 43457, 90945, 34518, 25568, 50341, 43017, 41750, 11354, 37331, 13556, 44449, 73074, 59374, 57501, 1644, 9887, 235, END};

struct BigNum {
	int N[MULSZ_MAX];
	int size;
	bool sign;
};

__attribute__((nonnull)) int BigMulAdd(int * __restrict__ resAdd, const int lmb1[], size_t szLmb1, const int lmb2[], size_t szLmb2)
{
	register unsigned int oo = 0, adLmb = 0, crLmb = 0;

	resAdd[oo++] = lmb1[--szLmb1];
	for (; szLmb1 && szLmb2; oo++)
	{
		adLmb = lmb2[--szLmb2] + lmb1[--szLmb1] + crLmb;
		if (adLmb > 0x1869f)
		{
			resAdd[oo] = 1;
			crLmb = adLmb - LIMB_SZ;
			continue;
		}
		crLmb = 0;
		resAdd[oo] = adLmb;
	}
	resAdd[oo + 1] = END;
	return oo;
}

int BigMul(int bigMulResult[], const int lmb1[], int s1, const int lmb2[], int s2)
{
	register unsigned long long oo, bb, ooNbb, adLmb, crLmb;

	for (bb = 0; bb < s2; bb++)
	{
		ooNbb = bb;
		for (oo = 0, crLmb = 0; oo < s1; ooNbb++, oo++)
		{
			adLmb = mulAdd(lmb2[bb], lmb1[oo], (crLmb + bigMulResult[ooNbb]));
			crLmb = ((adLmb >> 5) * 0x053e2d6239ULL) >> 46;
			bigMulResult[ooNbb] = adLmb - (crLmb * LIMB_SZ);
		}
		bigMulResult[ooNbb] = crLmb;
	}
	bigMulResult[ooNbb + 1] = END;
	return ooNbb;
}
int BigShift(int *bigNum, int size, int shift)
{
	register int oo;
 	math_i64_bit adLmb, crLmb = 0;

	for (oo = 0; oo < shift; oo++)
	{
		adLmb = (bigNum[oo] << 1) + crLmb;
		bigNum[oo] = ((adLmb >> 5) * 171799) >> 19;
	}
}
int Big5thPow(int resPow[], int p)
{
	register unsigned int oo, adLmb, crLmb, powRange;

	if (p < 27)
		;//toLimb(resPow,
/**
	if (p > 49 && p <= _PRECALC_POW5TH)
		return _FETCH_PRECALC_LOC(p);
*/
	for (oo = 0; (p -= _PRECALC_POW5TH) > -1; oo++)
			PASS;
	resPow[0] = BigMul(resPow + 1, P125 + 1, P125[0], P125 + 1, P125[0]);
	//while (
}
__attribute__((nonnull)) int *toLimb(int lmbBf[], int *size, math_i64_bit val)
{
	register int oo = 0, si = *size;
	for (; oo < si && val; (val /= LIMB_SZ), oo++)
		lmbBf[oo] = val % LIMB_SZ;
	lmbBf[oo] = END;
	*size = oo;
	return lmbBf;
}
void print(int *n)
{
    int k;
    int oo = 0, pp = 0;
    while ((n[oo++] != END))
        ;
   oo -= 2;
   for (; (k = n[oo]), (oo > -1); oo--)
    {
        if (k < 1000)
        {
            k = k < 1000 ? k > 99 ? 2 :
                k > 9 ? 3 : 4 : 0;

            for (int j = 0; j < k; j++)
                putchar('0');
            printf("%d", n[oo]);
        }
        else
            printf("%d", n[oo]);
    }
    putchar(10);

}
/**
int main(void)
{
const static int precalc_pow[PRECALC_COL_SIZE][PRECALC_ROW_SIZE] = PRECALC_PO\
W5_TABLE();
	long long int c;
	clock_t n, p;
	int bf[6], l = 0;
	{78125, 27050, 91702, 5907, 91351, 15628, 55756, 2775},
	int a[] = {78125, 27050, 91702, 5907, 91351, 15628, 55756, 2775};
	int b[] = {13893, 76091, 20942, 6};
	int resAdd[1024];
	int quo;
	l = toLimb(bf, 6, 6209427609113893LL);
	startTime(n);
	BigMul(resAdd, , 8, b, 4);
	stopTime(n);
	printTime(n);
	print(resAdd + 1);
//	print(resAdd);
}*/
/**
	powRange = p > PRECALC_MAX ? _PRECALC_POW5TH
		: p > PRECALC_MIN ? PRECALC_MIN + 1 :
		p > RADIX_ULLMAX ? RADIX_ULLMAX : 0;
*/
