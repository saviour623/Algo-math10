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

math_i64_bit callidentity(math_i64_bit identifier){
  register int32_t sizeofbit;
  register math_i64_bit zerocbits __attribute__((unused));
  register math_i64_bit bit_id = 0;
  register math_i64_bit k, r;
  
  k = r = 0;
  sizeofbit = size(identifier) - 1; /* we don't care about the sign */

  identifier >>= 2;
  puts(bin(49, (char[65]){0}));

  /* id = p - k. let p = 2r + 1 and k = 2c + 2; where r and c is dependent on p and k, thus: r = p or 0, and c = k or 0
   * however here, both id and r is the same, as well as k and c */
  do {
    bit_id = (bit_id << 1) + 1;
    if (NOT(identifier & 1) && identifier)
      k = (k << 1) + 2;
    else {
      bit_id = bit_id - k;
      k = 0;
    }
  } while ((identifier >>= 1));
  return bit_id;
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

int main(void){
  size_t sizevar;
  int n = 0;
  double t = 0.1723462375000005;
  int get = 0;
  char *s = "00101100000111101110001000001101101001101011000111001";
  printf("%ld\n", strlen(s));
  while (n < 64)
  {
	  t = t * 2;
	  get = (int)t;

	  if (get > 0)
	  {
		  putchar(49);
		  t -= get;
	  }
	  else
		  putchar('0');
	  n++;
  }
  putchar('\n');
  printf("%lu\n", idenString(s));
}
/*10000011010111000111110011011000100110001011001011101 */
/*
0.13562
*/
