#include "fiden.h"

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

__attribute__((nonnull)) int BigMulAdd(int * __restrict__ resAdd, const int lmb1[], size_t szLmb1, const int lmb2[], size_t szLmb2)
{
	register unsigned int oo = 0, _quo = 0, _rem = 0;

	resAdd[oo++] = lmb1[--szLmb1];
	for (; szLmb1 && szLmb2; oo++)
	{
		_quo = lmb2[--szLmb2] + lmb1[--szLmb1] + _rem;
		if (_quo > 0x1869f)
		{
			resAdd[oo] = 1;
			_rem = _quo - LIMB_SZ;
			continue;
		}
		_rem = 0;
		resAdd[oo] = _quo;
	}
	resAdd[oo + 1] = END;
	return oo;
}

int BigMul(int bigMulResult[], const int lmb1[], math_uint_t s1, const int lmb2[], math_uint_t s2)
{
	register unsigned long long oo, bb, ooNbb, _quo, _rem;

	for (bb = 0; bb < s2; bb++)
	{
		ooNbb = bb;
		for (oo = 0, _rem = 0; oo < s1; ooNbb++, oo++)
		{
			_quo = mulAdd(lmb2[bb], lmb1[oo], (_rem + bigMulResult[ooNbb]));
#ifdef OPTIMIZE
			_rem = ((_quo >> 5) * 0x053e2d6239ULL) >> 46;
#else
			_rem = _quo / LIMB_SZ;
#endif
			bigMulResult[ooNbb] = _quo - (_rem * LIMB_SZ);
		}
		bigMulResult[ooNbb] = _rem;
	}
	bigMulResult[ooNbb + 1] = END;
	return ooNbb + !!(_rem);
}

__attribute__((gnu_inline, nonnull))
inline int Bigsr31(int * restrict bigNum, int size, int shift)
{
	register long long _rem = 0, _quo = 0, k = 0, oo = size;
	const int sf = (1 << shift) - 1;

	if ((! size) || (! shift))
		return 0;
	while (oo--)
	{
		_quo = bigNum[oo];
		_rem ? (k = _quo + (_rem * LIMB_SZ)) : (k = _quo);
		bigNum[oo] = k >> shift;
		_rem = k & sf;
	}
	while ((bigNum[--size] == 0));
	return 	((bigNum[++size] = END), size);
}
int Bigsrs(int *bigNum, int size, int shift)
{
	register int j, k;
	
	if ((! size) || (! shift))
		return 0;
	if (shift < 32)
		return Bigsr31(bigNum, size, shift);
	j = shift - ((k = shift / 31) * 31);

	for (shift = 31; k--;)
	{
		size = Bigsr31(bigNum, size, shift);
		if ((! k) && j)
			shift = j, j = 0, k = 1;
	}
	return size;
}
int BigShiftl(int *bigNum, int size, int shift)
{
	int oo, ee, ne, re;
 	math_i64_bit _quo, _rem = 0;

	if (shift < 64)
	{
		int tmp[MIN_ULMB_SIZE];
		return BigMul(bigNum, bigNum, size, toLimb(tmp, &ne, 1ULL << 63), ne);
	}
	ne = shift / 9;
	re = shift - ((ne >> 2) + ne);
	shift = 9;
	ne = 62;
	while (ne--)
	{
		for (ee = 0; ee < size; ee++) 
		{
			_quo = (bigNum[ee] << shift) + _rem;
			_rem = ((_quo * 171799) >> 34);
			bigNum[ee] = _quo - (_rem * LIMB_SZ);
		}
		_rem ? bigNum[ee] = _rem, size = ee + 1 : 0;
		
		if ((ne == 0) && re)
		{
			ne += 1;
			shift = re;
			re = 0;
		}
	}
	bigNum[ee + 1] = END;
	return size;	
}
int Big5thPow(int resPow[], int p __attribute__((unused)))
{
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
void print(const int * restrict n)
{
    int k;
    int oo = 0, pp = 0;
    while ((n[oo++] != END))
        ;
   oo -= 2;
   const int p = oo;
   for (; (k = n[oo]), (oo > -1); oo--)
    {
        if ((k < 10000) && (oo != p))
        {
            k = k > 999 ? 1 : k > 99 ? 2 :
                k > 9 ? 3 : 4;

            for (int j = 0; j < k; j++)
                putchar('0');
            printf("%u", n[oo]);
        }
        else
            printf("%u", n[oo]);
    }
    putchar(10);

}
inline int subtract(int a, int b)
{
	int temp = 0;
	while (b != 0)
	{
		temp = ((~a) & b) << 1;
		a = a ^ b;
		b = temp;
	}
	return a;
}
/**
int main(void)
{
	const static int precalc_pow[PRECALC_COL_SIZE][PRECALC_ROW_SIZE] = PRECALC_POW5_TABLE();
	long long int c;
	clock_t n, p;
	int bf[6], l = 0;
	int a[256] = {99999, 99999, 2, END};
	int b[20] = {35436, 76576, 64465, 76577, 86895, 13893, 76091, 20942, 35436, 76576, 64465, 76577, 86895, 13893, 76091, 20942, 6, END};
	int resAdd[1024];
	int quo;
	print(b);
	//l = toLimb(bf, 6, 6209427609113893LL);
	startTime(n);
	quo = Bigsrs(b, 17, 31);
//	quo = subtract(5367877, 100000);
	stopTime(n);
	printTime(n);
	print(b);
}
*/
