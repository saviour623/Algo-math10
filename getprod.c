#include "fiden.h"
#include <string.h>

#define _BASE_RADIX 2
#define _RADIX 5
#define _PRECALC_POW5TH 125
#define _FETCH_PRECALC_LOC(n)\
	(((n) > 49 && (n) < 64) ? powLookUpTable64[n] : ((n) > 64 && (n) < 96) ? \
	 powLookUpTable95[n] : ((n) > 95 && (n) < 126) ? powLookUpTable95[n] ? NULL)

/** for the major normalised floating point the number, the minmum rounded bits, b, corresponding to _RADIX ^ b, falls closely within
 * 50 and 125. Since we know this, there's no need to recalculate these values at each time of use during runtime (for optimisation),
 * so lookup table(s) for these values is the most sensible way to do things
 */
const char *powLookupTable64[] = {
	"88817841970012523233890533447265625", "444089209850062616169452667236328125",
	"2220446049250313080847263336181640625", "11102230246251565404236316680908203125",
	"55511151231257827021181583404541015625", "277555756156289135105907917022705078125",
	"1387778780781445675529539585113525390625", "6938893903907228377647697925567626953125",
	"34694469519536141888238489627838134765625", "173472347597680709441192448139190673828125",
	"867361737988403547205962240695953369140625", "4336808689942017736029811203479766845703125",
	"21684043449710088680149056017398834228515625", "108420217248550443400745280086994171142578125",
	"542101086242752217003726400434970855712890625", NULL
};
/* powers of _RADIX greater than 64 and less than 95 */
const char *powLookUpTable95[] = {
	"2710505431213761085018632002174854278564453125", "13552527156068805425093160010874271392822265625",
	"67762635780344027125465800054371356964111328125", "338813178901720135627329000271856784820556640625",
	"1694065894508600678136645001359283924102783203125", "8470329472543003390683225006796419620513916015625",
	"42351647362715016953416125033982098102569580078125", "211758236813575084767080625169910490512847900390625",
	"1058791184067875423835403125849552452564239501953125", "5293955920339377119177015629247762262821197509765625",
	"26469779601696885595885078146238811314105987548828125", "132348898008484427979425390731194056570529937744140625",
	"661744490042422139897126953655970282852649688720703125", "3308722450212110699485634768279851414263248443603515625",
	"16543612251060553497428173841399257071316242218017578125", "82718061255302767487140869206996285356581211090087890625",
	"413590306276513837435704346034981426782906055450439453125", "2067951531382569187178521730174907133914530277252197265625",
	"10339757656912845935892608650874535669572651386260986328125", "51698788284564229679463043254372678347863256931304931640625",
	"258493941422821148397315216271863391739316284656524658203125", "1292469707114105741986576081359316958696581423282623291015625",
	"6462348535570528709932880406796584793482907116413116455078125", "32311742677852643549664402033982923967414535582065582275390625",
	"161558713389263217748322010169914619837072677910327911376953125", "807793566946316088741610050849573099185363389551639556884765625",
	"4038967834731580443708050254247865495926816947758197784423828125", "20194839173657902218540251271239327479634084738790988922119140625",
	"100974195868289511092701256356196637398170423693954944610595703125", "504870979341447555463506281780983186990852118469774723052978515625",
	"2524354896707237777317531408904915934954260592348873615264892578125", NULL
};
/* powers of _RADIX greater than 95 and less than 125 */
const char *powLookUpTable125[] = {
	"12621774483536188886587657044524579674771302961744368076324462890625",
	"63108872417680944432938285222622898373856514808721840381622314453125",
	"315544362088404722164691426113114491869282574043609201908111572265625",
	"1577721810442023610823457130565572459346412870218046009540557861328125",
	"7888609052210118054117285652827862296732064351090230047702789306640625",
	"39443045261050590270586428264139311483660321755451150238513946533203125",
	"197215226305252951352932141320696557418301608777255751192569732666015625",
	"986076131526264756764660706603482787091508043886278755962848663330078125",
	"4930380657631323783823303533017413935457540219431393779814243316650390625",
	"24651903288156618919116517665087069677287701097156968899071216583251953125",
	"123259516440783094595582588325435348386438505485784844495356082916259765625",
	"616297582203915472977912941627176741932192527428924222476780414581298828125",
	"3081487911019577364889564708135883709660962637144621112383902072906494140625",
	"15407439555097886824447823540679418548304813185723105561919510364532470703125",
	"77037197775489434122239117703397092741524065928615527809597551822662353515625",
	"385185988877447170611195588516985463707620329643077639047987759113311767578125",
	"1925929944387235853055977942584927318538101648215388195239938795566558837890625",
	"9629649721936179265279889712924636592690508241076940976199693977832794189453125",
	"48148248609680896326399448564623182963452541205384704880998469889163970947265625",
	"240741243048404481631997242823115914817262706026923524404992349445819854736328125",
	"1203706215242022408159986214115579574086313530134617622024961747229099273681640625",
	"6018531076210112040799931070577897870431567650673088110124808736145496368408203125",
	"30092655381050560203999655352889489352157838253365440550624043680727481842041015625",
	"150463276905252801019998276764447446760789191266827202753120218403637409210205078125",
	"752316384526264005099991383822237233803945956334136013765601092018187046051025390625",
	"3761581922631320025499956919111186169019729781670680068828005460090935230255126953125",
	"18807909613156600127499784595555930845098648908353400344140027300454676151275634765625",
	"94039548065783000637498922977779654225493244541767001720700136502273380756378173828125",
	"470197740328915003187494614888898271127466222708835008603500682511366903781890869140625",
	"2350988701644575015937473074444491355637331113544175043017503412556834518909454345703125",	NULL
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

char *fltoStr(
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
