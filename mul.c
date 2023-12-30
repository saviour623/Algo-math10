#include "fiden.h"
#include <time.h>

#define startTime(n) ((n) = clock())
#define stopTime(n) ((n) = clock() - (n))
#define printTime(n) printf("%f\n", (n) / (double) CLOCKS_PER_SEC)
#define reverseBf generic_reversebuff

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

int *BigAdd(int lmb1[], size_t szLmb1, int lmb2[], size_t szLmb2)
{
	int *resAdd = malloc(sizeof (int) * (szLmb1 + szLmb2));
	register size_t oo = 0, tSz = szLmb1 + szLmb2;
	register unsigned int adLmb = 0, crLmb = 0;

	resAdd[0] = lmb1[--szLmb];

	for (; oo < (szlmb2 - 1); oo++)
	{
		adLmb = lmb2[szLmb2 - 1] + lmb2[szLmb1] + crLmb;
		if (adLmb > 0x1869f)
		{
		}
	}
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
int toLimb(int lmbBf[], size_t size, long long int val)
{
	register int oo;
	if (size == 0 || lmbBf == NULL)
		return -1;
	for (oo = 0; oo < size && val; oo++, (val /= LIMB_SZ))
		lmbBf[oo] = val % LIMB_SZ;
	size = 0;
	reverseBf(lmbBf, size, oo);
	return (oo << 1 | 1);
}
int main(void)
{
	long long int c;
	clock_t n, p;
	int bf[6], l = 0;

	startTime(n);

	l = toLimb(bf, 6, 6209427609113893LL);

	stopTime(n);
	printTime(n);

	for (int i = 0; i < l; i++)
		printf("%d\n", bf[i]);
	putchar(10);
}
