#include "fiden.h"
#include <string.h>

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

char *fltoStr(double dbl_input, size_t dig_output)
{
	char *nbitBuf = NULL;
	if (dbl_input == 0.0)
		return "0.0";
	
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
