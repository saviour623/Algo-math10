#include "fiden.h"
#include <string.h>

#define _PRECALC_POW5TH 64
const char *powLookupTable[] = {
	"88817841970012523233890533447265625", "444089209850062616169452667236328125",
	"2220446049250313080847263336181640625", "11102230246251565404236316680908203125",
	"55511151231257827021181583404541015625", "277555756156289135105907917022705078125",
	"1387778780781445675529539585113525390625", "6938893903907228377647697925567626953125",
	"34694469519536141888238489627838134765625", "173472347597680709441192448139190673828125",
	"867361737988403547205962240695953369140625", "4336808689942017736029811203479766845703125",
	"21684043449710088680149056017398834228515625", "108420217248550443400745280086994171142578125",
	"542101086242752217003726400434970855712890625", NULL
};

static inline math_i64_bit logbase2(math_i64_bit n){
  uint16_t r = 0;

  while (((n >>= 1) && r++))
	  ;
  return r-2;
}

static inline size_t sizeofuintmax_t(void){
  return sizeof (math_i64_bit);
}

char * bin(math_i64_bit tobin, char *__restrict__ buff){
  int oo = 0, st = 0;

  while (tobin){
    buff[oo] = (tobin & 1) + 48;
    tobin >>= 1;
    oo += 1;
  }
  generic_reversebuff(buff, st, oo);

  return buff;
}

math_i64_bit idenString(const char *__restrict__ str){
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
char *getFltBits(long double nput, size_t numBit, char *bits_bf)
{
	register size_t oo;

	if (numBit == 0 || numBit < 0)
		return NULL;

	for (oo = 0; (oo < numBit) && (nput != 0.0); oo++)
	{
	  nput = nput * 2;
	  bits_bf[oo] =  cast_to_i64(nput) ? ((nput -= 1), '1') : '0';
	}
	bits_bf[oo] = 0;
	return bits_bf;
}
int main(void){
  size_t sizevar;
  int n = 0;
  long double t = 0.1723462375345345005;

  char *s = getFltBits(t, 64 + 1, (char[65]){0});
  printf("%ld\n", strlen(s));
  puts(s);
  printf("%.23Lf\n", t);
  printf("%lu\n", idenString(s));
}
/*10000011010111000111110011011000100110001011*
0.13562
*/
