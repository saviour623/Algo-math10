#include "fiden.h"
#include "lookup.h"
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

#define PASS (void)0
#define LIMB_SZ 100000
#define FLIMB_SZ 0.00001L
#define MULSZ_MAX 1024
#define END -1024

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
const static int precalculate_pow[PRECALC_COL_SIZE][PRECALC_ROW_SIZE] = PRECALC_POW5_TABLE(); 

struct BigNum {
	int N[MULSZ_MAX];
	int size;
	bool sign;
};
void print(int *n);
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
	return 0;
}

char *Big5thPow(int resPow[], int p)
{
	register unsigned int oo, adLmb, crLmb, powRange;
/**
	if (p > 49 && p <= _PRECALC_POW5TH)
		return _FETCH_PRECALC_LOC(p);
*/
	for (oo = 0; (p -= _PRECALC_POW5TH) > -1; oo++)
			PASS;
		resPow[0] = BigMul(resPow + 1, P125 + 1, P125[0], P125 + 1, P125[0]);
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
void print(int *n)
{
    int k;
    int oo = 0, pp = 0;
    while ((n[oo++] != END))
        ;
    oo--;
    reverseBf(n, pp, oo);
    while ((k = *n) != END)
    {
        if (k < 1000)
        {
            k = k < 1000 ? k > 99 ? 2 :
                k > 9 ? 3 : 4 : 0;

            for (int j = 0; j < k; j++)
                putchar('0');
            printf("%d", *n);
        }
        else
            printf("%d", *n);
        n++;
    }
    putchar(10);

}
int main(void)
{
	long long int c;
	clock_t n, p;
	int bf[6], l = 0;
	int a[] = {72481, 55000, 40281};
	int b[] = {72481, 55000, 40281};
	int resAdd[1024];
	int quo;
	l = toLimb(bf, 6, 6209427609113893LL);
	startTime(n);
	Big5thPow(resAdd, 125);
	stopTime(n);
	printTime(n);
	print(resAdd + 1);
//	print(resAdd);
}
/**
	powRange = p > PRECALC_MAX ? _PRECALC_POW5TH
		: p > PRECALC_MIN ? PRECALC_MIN + 1 :
		p > RADIX_ULLMAX ? RADIX_ULLMAX : 0;
*/
