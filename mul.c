#include "fiden.h"
#include <time.h>

#define startTime(n) ((n) = clock())
#define stopTime(n) ((n) = clock() - (n))
#define printTime(n) printf("%f\n", (n) / (double) CLOCKS_PER_SEC)
#define reverseBf generic_reversebuff
#ifdef __GNUC__
     #define restrict __restrict__
#endif
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
#define MULSZ_MAX 6

__attribute__((nonnull)) int BigMulAdd(int * __restrict__ resAdd, int lmb1[], size_t szLmb1, int lmb2[], size_t szLmb2)
{
	register unsigned int oo = 0, adLmb = 0, crLmb = 0;

	resAdd[oo++] = lmb1[--szLmb1];
	for (; szLmb1; oo++)
	{
		adLmb = lmb2[--szLmb2] + lmb1[--szLmb1] + crLmb;
		crLmb = 0;
		if (adLmb > 0x1869f)
		{
			resAdd[oo] = adLmb % LIMB_SZ;
			crLmb = adLmb / LIMB_SZ;
			continue;
		}
		resAdd[oo] = adLmb;
	}
	resAdd[oo] = lmb2[0] + crLmb;
	return oo + 1;
}
int *BigMul(int lmb1[], int lmb2[])
{
	long long int bigMulResult[MULSZ_MAX];
	/* 6, 20942, 76091 */
	/* 6, 20942, 76091 */

	/* carry 555780 */
	/* 472481,55620,40281 */
	/* 130037,83298,97722 */
	/*130042,55780,53342,40281*/
	/* 00000000000000011000011010011111 */
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
	int a[] = {472481, 55620, 40281};
	int b[] = {130037, 83298, 97722};
	int *resAdd = malloc(sizeof (int) * (6));
	l = toLimb(bf, 6, 6209427609113893LL);
	startTime(n);
	c = BigMulAdd(resAdd, a, 3, b, 3);
	stopTime(n);
	printTime(n);

	//for (int i = 0; i < l; i++)
	//printf("%d\n", bf[i]);
	for (int i = 0; i < c; i++)
		printf("%d\n", resAdd[i]);
	putchar(10);
}
