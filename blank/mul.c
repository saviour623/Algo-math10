#include "../fiden.h"
#include <time.h>

#define startTime(n) ((n) = clock())
#define stopTime(n) ((n) = clock() - (n))
#define printTime(n) printf("%f\n", (n) / (double) CLOCKS_PER_SEC)
#define reverseBf generic_reversebuff
#define mulAddDiv(a, b, c)\
	(((U64)(a) * (U64)(b)) + ((U64)(c))) 
#ifdef __GNUC__
     #define restrict __restrict__
#endif
typedef long long int U64;
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
	register unsigned long long oo = 0, adLmb = 0, crLmb = 0, tmp;
	int bb = 0;
	
	for (bb = 0; s2; bb++, s2--)
	{
		tmp = s1 - 1;
		for (oo = 0, crLmb = 0; oo < tmp+1; oo++)
		{
			adLmb = mulAddDiv(lmb2[s2-1], lmb1[tmp - oo],
							  (crLmb + bigMulResult[oo + bb]));
			crLmb = adLmb / LIMB_SZ;
			bigMulResult[oo + bb] = adLmb % LIMB_SZ;
		}
		if (crLmb)
			bigMulResult[bb + oo] = crLmb;
	}
	return bigMulResult;
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
	int a[] = {23423, 472481, 55620, 40281};
	int b[] = {34234, 472481, 55620, 40281};

	int *resAdd;// = malloc(sizeof (int) * (6));
	int quo;
	l = toLimb(bf, 6, 6209427609113893LL);
	startTime(n);
	resAdd = BigMul(a, 4, b, 4);
	stopTime(n);
	printTime(n);

	div_t dg = div(123456, 1000);
	printf("quot %d, rem %d\n", dg.quot, dg.rem);
	//for (int i = 0; i < l; i++)
	//printf("%d\n", bf[i]);
	c = 9;
	for (int i = 0; i < c; i++)
		printf("%d\n", resAdd[i]);
	putchar(10);
}
/* 6, 20942, 76091 */
	/* 6, 20942, 76091 */

	/* carry 555780 */
	/* 472481,55620,40281 */
	/* 130037,83298,97722 */
	/*130042,55780,53342,40281*/
	/* 00000000000000011000011010011111 */
