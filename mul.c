#include "fiden.h"
#include <time.h>
#include <stdbool.h>

#define startTime(n) ((n) = clock())
#define stopTime(n) ((n) = clock() - (n))
#define printTime(n) printf("%f\n", (n) / (double) CLOCKS_PER_SEC)

#define reverseBf generic_reversebuff
#define mulAdd(a, b, c)\
	(((U64)(a) * (U64)(b)) + ((U64)(c)))
#ifdef __GNUC__
     #define restrict __restrict__
#endif
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

#define LIMB_SZ 100000
#define FLIMB_SZ 0.00001L
#define MULSZ_MAX 1024
#define END -1024

struct BigNum {
	int N[MULSZ_MAX];
	int size;
	bool sign;
};

__attribute__((nonnull)) int BigMulAdd(int * __restrict__ resAdd, int lmb1[], size_t szLmb1, int lmb2[], size_t szLmb2)
{
	register unsigned int oo = 0, adLmb = 0, crLmb = 0;

	resAdd[oo++] = lmb1[--szLmb1];
	for (; szLmb1 && szLmb2; oo++)
	{
		adLmb = lmb2[--szLmb2] + lmb1[--szLmb1] + crLmb;
		if (adLmb > 0x1869f)
		{
			resAdd[oo] = adLmb % LIMB_SZ;
			crLmb = adLmb / LIMB_SZ;
			continue;
		}
		crLmb = 0;
		resAdd[oo] = adLmb;
	}

	return oo;
}

int *BigMul(int lmb1[], int s1, int lmb2[], int s2)
{
	static int bigMulResult[MULSZ_MAX];
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
		if (crLmb)
			bigMulResult[ooNbb] = crLmb;
	}
	bigMulResult[ooNbb + 1] = END;
	return bigMulResult;
}

int *BigPow(int lmb[], int p)
{
}
__attribute__((nonnull)) int toLimb(int lmbBf[], size_t size, long long int val)
{
	register int oo, tmp;
	for (oo = 0; oo < size && val; oo++, (val /= LIMB_SZ))
		lmbBf[oo] = val % LIMB_SZ;
	tmp = oo; size = 0;
	reverseBf(lmbBf, size, tmp);
	return oo;
}
int main(void)
{
	long long int c;
	clock_t n, p;
	int bf[6], l = 0;
	int a[] = {72481, 55000, 40281};
	int b[] = {72481, 55000, 40281};
	int *resAdd;
	int quo;
	
	l = toLimb(bf, 6, 6209427609113893LL);
	startTime(n);
	resAdd = BigMul(a, 3, b, 3);
	stopTime(n);
	printTime(n);

	c = 6;
	for (int i = 0; i < c; i++)
		printf("%d\n", resAdd[i]);
	putchar(10);
}
