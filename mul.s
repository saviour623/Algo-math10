	.file	"mul.c"
	.text
	.p2align 4
	.globl	BigMulAdd
	.type	BigMulAdd, @function
BigMulAdd:
.LFB72:
	.cfi_startproc
	endbr64
	movq	%rsi, %r10
	leaq	-1(%rdx), %rsi
	movl	(%r10,%rsi,4), %eax
	movl	%eax, (%rdi)
	testq	%rsi, %rsi
	je	.L7
	testq	%r8, %r8
	je	.L7
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %r9
	movq	%rcx, %r11
	xorl	%edi, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	$1, %eax
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L4:
	movl	%ecx, (%rbx)
	addl	$1, %eax
	testq	%rsi, %rsi
	je	.L1
.L24:
	testq	%r8, %r8
	je	.L1
.L5:
	subq	$1, %r8
	subq	$1, %rsi
	movl	%eax, %ecx
	movl	(%r11,%r8,4), %edx
	addl	(%r10,%rsi,4), %edx
	leaq	(%r9,%rcx,4), %rbx
	addl	%edi, %edx
	xorl	%edi, %edi
	movl	%edx, %ecx
	cmpl	$99999, %edx
	jbe	.L4
	shrl	$5, %ecx
	addl	$1, %eax
	imulq	$175921861, %rcx, %rdi
	movq	%rdi, %rcx
	shrq	$39, %rdi
	shrq	$39, %rcx
	imull	$100000, %ecx, %ebp
	subl	%ebp, %edx
	movl	%edx, %ecx
	movl	%ecx, (%rbx)
	testq	%rsi, %rsi
	jne	.L24
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	.cfi_restore 3
	.cfi_restore 6
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE72:
	.size	BigMulAdd, .-BigMulAdd
	.p2align 4
	.globl	BigMul
	.type	BigMul, @function
BigMul:
.LFB73:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	leaq	bigMulResult.0(%rip), %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	testl	%ecx, %ecx
	je	.L41
	flds	.LC2(%rip)
	movq	%rdi, %r9
	movl	%esi, %ebx
	movslq	%esi, %r8
	flds	.LC0(%rip)
	movslq	%ecx, %rbp
	movq	%rdx, %rdi
	movq	%r12, %rsi
	fldt	.LC1(%rip)
	xorl	%r11d, %r11d
	movabsq	$-9223372036854775808, %r10
	.p2align 4,,10
	.p2align 3
.L27:
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	testl	%ebx, %ebx
	je	.L33
	fnstcw	-10(%rsp)
	movzwl	-10(%rsp), %eax
	orb	$12, %ah
	movw	%ax, -12(%rsp)
	jmp	.L31
	.p2align 4,,10
	.p2align 3
.L44:
	fstp	%st(1)
	fldcw	-12(%rsp)
	fistpq	-24(%rsp)
	fldcw	-10(%rsp)
	movq	-24(%rsp), %rcx
.L30:
	imull	$100000, %ecx, %r13d
	subl	%r13d, %eax
	movl	%eax, (%rsi,%rdx,4)
	addq	$1, %rdx
	cmpq	%r8, %rdx
	je	.L43
.L31:
	movslq	(%r9,%rdx,4), %r13
	movslq	(%rdi), %rax
	imulq	%r13, %rax
	movslq	(%rsi,%rdx,4), %r13
	addq	%r13, %rax
	addq	%rcx, %rax
	movq	%rax, -24(%rsp)
	fildq	-24(%rsp)
	jns	.L28
	fadd	%st(2), %st
.L28:
	fmul	%st(1), %st
	fld	%st(3)
	fxch	%st(1)
	fcomi	%st(1), %st
	jb	.L44
	fsubp	%st, %st(1)
	fldcw	-12(%rsp)
	fistpq	-24(%rsp)
	fldcw	-10(%rsp)
	movq	-24(%rsp), %rcx
	xorq	%r10, %rcx
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L43:
	testq	%rcx, %rcx
	je	.L33
	movl	%ecx, (%rsi,%r8,4)
.L33:
	addq	$1, %r11
	addq	$4, %rdi
	addq	$4, %rsi
	cmpq	%r11, %rbp
	jne	.L27
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
.L41:
	popq	%rbx
	.cfi_def_cfa_offset 32
	movq	%r12, %rax
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE73:
	.size	BigMul, .-BigMul
	.p2align 4
	.globl	toLimb
	.type	toLimb, @function
toLimb:
.LFB74:
	.cfi_startproc
	endbr64
	movq	%rsi, %r8
	movq	%rdx, %rcx
	testq	%rdx, %rdx
	je	.L51
	testq	%rsi, %rsi
	je	.L51
	movabsq	$3022314549036572937, %r9
	xorl	%esi, %esi
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L64:
	cmpq	%r8, %rsi
	jnb	.L52
.L47:
	movq	%rcx, %rax
	imulq	%r9
	movq	%rcx, %rax
	sarq	$63, %rax
	sarq	$14, %rdx
	subq	%rax, %rdx
	imulq	$100000, %rdx, %rax
	subq	%rax, %rcx
	movq	%rsi, %rax
	movl	%ecx, (%rdi,%rsi,4)
	movq	%rdx, %rcx
	addq	$1, %rsi
	testq	%rdx, %rdx
	jne	.L64
.L52:
	movslq	%eax, %rsi
	leal	1(%rax), %r8d
	movslq	%eax, %rdx
	testl	%eax, %eax
	je	.L45
.L46:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L50:
	leaq	(%rdi,%rdx,4), %rcx
	movl	(%rdi,%rax,4), %edx
	xorl	(%rcx), %edx
	movl	%edx, (%rdi,%rax,4)
	addq	$1, %rax
	xorl	(%rcx), %edx
	movl	%edx, (%rcx)
	xorl	%edx, -4(%rdi,%rax,4)
	movq	%rsi, %rdx
	subq	%rax, %rdx
	cmpq	%rdx, %rax
	jb	.L50
.L45:
	movl	%r8d, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L51:
	xorl	%r8d, %r8d
	movq	$-1, %rdx
	movq	$-1, %rsi
	jmp	.L46
	.cfi_endproc
.LFE74:
	.size	toLimb, .-toLimb
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC6:
	.string	"%f\n"
.LC7:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB75:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	$6, %esi
	movabsq	$6209427609113893, %rdx
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$64, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	movq	.LC4(%rip), %rax
	leaq	32(%rsp), %rdi
	movl	$40281, 8(%rsp)
	movl	$40281, 24(%rsp)
	movq	%rax, (%rsp)
	movq	%rax, 16(%rsp)
	call	toLimb
	call	clock@PLT
	leaq	16(%rsp), %rdx
	movq	%rsp, %rdi
	movl	$3, %ecx
	movl	$3, %esi
	movq	%rax, %rbp
	call	BigMul
	movq	%rax, %rbx
	call	clock@PLT
	pxor	%xmm0, %xmm0
	leaq	.LC6(%rip), %rsi
	movl	$1, %edi
	subq	%rbp, %rax
	leaq	120(%rbx), %r12
	leaq	.LC7(%rip), %rbp
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	divsd	.LC5(%rip), %xmm0
	call	__printf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L66:
	movl	(%rbx), %edx
	movq	%rbp, %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	addq	$4, %rbx
	call	__printf_chk@PLT
	cmpq	%rbx, %r12
	jne	.L66
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	putc@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L70
	addq	$64, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L70:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE75:
	.size	main, .-main
	.local	bigMulResult.0
	.comm	bigMulResult.0,4096,32
	.globl	extPow10
	.section	.rodata
	.align 32
	.type	extPow10, @object
	.size	extPow10, 36
extPow10:
	.long	10
	.long	100
	.long	1000
	.long	10000
	.long	100000
	.long	1000000
	.long	10000000
	.long	100000000
	.long	1000000000
	.globl	powLookUpTable125
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC8:
	.string	"12621774483536188886587657044524579674771302961744368076324462890625"
	.align 8
.LC9:
	.string	"63108872417680944432938285222622898373856514808721840381622314453125"
	.align 8
.LC10:
	.string	"315544362088404722164691426113114491869282574043609201908111572265625"
	.align 8
.LC11:
	.string	"1577721810442023610823457130565572459346412870218046009540557861328125"
	.align 8
.LC12:
	.string	"7888609052210118054117285652827862296732064351090230047702789306640625"
	.align 8
.LC13:
	.string	"39443045261050590270586428264139311483660321755451150238513946533203125"
	.align 8
.LC14:
	.string	"197215226305252951352932141320696557418301608777255751192569732666015625"
	.align 8
.LC15:
	.string	"986076131526264756764660706603482787091508043886278755962848663330078125"
	.align 8
.LC16:
	.string	"4930380657631323783823303533017413935457540219431393779814243316650390625"
	.align 8
.LC17:
	.string	"24651903288156618919116517665087069677287701097156968899071216583251953125"
	.align 8
.LC18:
	.string	"123259516440783094595582588325435348386438505485784844495356082916259765625"
	.align 8
.LC19:
	.string	"616297582203915472977912941627176741932192527428924222476780414581298828125"
	.align 8
.LC20:
	.string	"3081487911019577364889564708135883709660962637144621112383902072906494140625"
	.align 8
.LC21:
	.string	"15407439555097886824447823540679418548304813185723105561919510364532470703125"
	.align 8
.LC22:
	.string	"77037197775489434122239117703397092741524065928615527809597551822662353515625"
	.align 8
.LC23:
	.string	"385185988877447170611195588516985463707620329643077639047987759113311767578125"
	.align 8
.LC24:
	.string	"1925929944387235853055977942584927318538101648215388195239938795566558837890625"
	.align 8
.LC25:
	.string	"9629649721936179265279889712924636592690508241076940976199693977832794189453125"
	.align 8
.LC26:
	.string	"48148248609680896326399448564623182963452541205384704880998469889163970947265625"
	.align 8
.LC27:
	.string	"240741243048404481631997242823115914817262706026923524404992349445819854736328125"
	.align 8
.LC28:
	.string	"1203706215242022408159986214115579574086313530134617622024961747229099273681640625"
	.align 8
.LC29:
	.string	"6018531076210112040799931070577897870431567650673088110124808736145496368408203125"
	.align 8
.LC30:
	.string	"30092655381050560203999655352889489352157838253365440550624043680727481842041015625"
	.align 8
.LC31:
	.string	"150463276905252801019998276764447446760789191266827202753120218403637409210205078125"
	.align 8
.LC32:
	.string	"752316384526264005099991383822237233803945956334136013765601092018187046051025390625"
	.align 8
.LC33:
	.string	"3761581922631320025499956919111186169019729781670680068828005460090935230255126953125"
	.align 8
.LC34:
	.string	"18807909613156600127499784595555930845098648908353400344140027300454676151275634765625"
	.align 8
.LC35:
	.string	"94039548065783000637498922977779654225493244541767001720700136502273380756378173828125"
	.align 8
.LC36:
	.string	"470197740328915003187494614888898271127466222708835008603500682511366903781890869140625"
	.align 8
.LC37:
	.string	"2350988701644575015937473074444491355637331113544175043017503412556834518909454345703125"
	.section	.data.rel.local,"aw"
	.align 32
	.type	powLookUpTable125, @object
	.size	powLookUpTable125, 248
powLookUpTable125:
	.quad	.LC8
	.quad	.LC9
	.quad	.LC10
	.quad	.LC11
	.quad	.LC12
	.quad	.LC13
	.quad	.LC14
	.quad	.LC15
	.quad	.LC16
	.quad	.LC17
	.quad	.LC18
	.quad	.LC19
	.quad	.LC20
	.quad	.LC21
	.quad	.LC22
	.quad	.LC23
	.quad	.LC24
	.quad	.LC25
	.quad	.LC26
	.quad	.LC27
	.quad	.LC28
	.quad	.LC29
	.quad	.LC30
	.quad	.LC31
	.quad	.LC32
	.quad	.LC33
	.quad	.LC34
	.quad	.LC35
	.quad	.LC36
	.quad	.LC37
	.quad	0
	.globl	powLookUpTable95
	.section	.rodata.str1.8
	.align 8
.LC38:
	.string	"2710505431213761085018632002174854278564453125"
	.align 8
.LC39:
	.string	"13552527156068805425093160010874271392822265625"
	.align 8
.LC40:
	.string	"67762635780344027125465800054371356964111328125"
	.align 8
.LC41:
	.string	"338813178901720135627329000271856784820556640625"
	.align 8
.LC42:
	.string	"1694065894508600678136645001359283924102783203125"
	.align 8
.LC43:
	.string	"8470329472543003390683225006796419620513916015625"
	.align 8
.LC44:
	.string	"42351647362715016953416125033982098102569580078125"
	.align 8
.LC45:
	.string	"211758236813575084767080625169910490512847900390625"
	.align 8
.LC46:
	.string	"1058791184067875423835403125849552452564239501953125"
	.align 8
.LC47:
	.string	"5293955920339377119177015629247762262821197509765625"
	.align 8
.LC48:
	.string	"26469779601696885595885078146238811314105987548828125"
	.align 8
.LC49:
	.string	"132348898008484427979425390731194056570529937744140625"
	.align 8
.LC50:
	.string	"661744490042422139897126953655970282852649688720703125"
	.align 8
.LC51:
	.string	"3308722450212110699485634768279851414263248443603515625"
	.align 8
.LC52:
	.string	"16543612251060553497428173841399257071316242218017578125"
	.align 8
.LC53:
	.string	"82718061255302767487140869206996285356581211090087890625"
	.align 8
.LC54:
	.string	"413590306276513837435704346034981426782906055450439453125"
	.align 8
.LC55:
	.string	"2067951531382569187178521730174907133914530277252197265625"
	.align 8
.LC56:
	.string	"10339757656912845935892608650874535669572651386260986328125"
	.align 8
.LC57:
	.string	"51698788284564229679463043254372678347863256931304931640625"
	.align 8
.LC58:
	.string	"258493941422821148397315216271863391739316284656524658203125"
	.align 8
.LC59:
	.string	"1292469707114105741986576081359316958696581423282623291015625"
	.align 8
.LC60:
	.string	"6462348535570528709932880406796584793482907116413116455078125"
	.align 8
.LC61:
	.string	"32311742677852643549664402033982923967414535582065582275390625"
	.align 8
.LC62:
	.string	"161558713389263217748322010169914619837072677910327911376953125"
	.align 8
.LC63:
	.string	"807793566946316088741610050849573099185363389551639556884765625"
	.align 8
.LC64:
	.string	"4038967834731580443708050254247865495926816947758197784423828125"
	.align 8
.LC65:
	.string	"20194839173657902218540251271239327479634084738790988922119140625"
	.align 8
.LC66:
	.string	"100974195868289511092701256356196637398170423693954944610595703125"
	.align 8
.LC67:
	.string	"504870979341447555463506281780983186990852118469774723052978515625"
	.align 8
.LC68:
	.string	"2524354896707237777317531408904915934954260592348873615264892578125"
	.section	.data.rel.local
	.align 32
	.type	powLookUpTable95, @object
	.size	powLookUpTable95, 256
powLookUpTable95:
	.quad	.LC38
	.quad	.LC39
	.quad	.LC40
	.quad	.LC41
	.quad	.LC42
	.quad	.LC43
	.quad	.LC44
	.quad	.LC45
	.quad	.LC46
	.quad	.LC47
	.quad	.LC48
	.quad	.LC49
	.quad	.LC50
	.quad	.LC51
	.quad	.LC52
	.quad	.LC53
	.quad	.LC54
	.quad	.LC55
	.quad	.LC56
	.quad	.LC57
	.quad	.LC58
	.quad	.LC59
	.quad	.LC60
	.quad	.LC61
	.quad	.LC62
	.quad	.LC63
	.quad	.LC64
	.quad	.LC65
	.quad	.LC66
	.quad	.LC67
	.quad	.LC68
	.quad	0
	.globl	powLookupTable64
	.section	.rodata.str1.8
	.align 8
.LC69:
	.string	"88817841970012523233890533447265625"
	.align 8
.LC70:
	.string	"444089209850062616169452667236328125"
	.align 8
.LC71:
	.string	"2220446049250313080847263336181640625"
	.align 8
.LC72:
	.string	"11102230246251565404236316680908203125"
	.align 8
.LC73:
	.string	"55511151231257827021181583404541015625"
	.align 8
.LC74:
	.string	"277555756156289135105907917022705078125"
	.align 8
.LC75:
	.string	"1387778780781445675529539585113525390625"
	.align 8
.LC76:
	.string	"6938893903907228377647697925567626953125"
	.align 8
.LC77:
	.string	"34694469519536141888238489627838134765625"
	.align 8
.LC78:
	.string	"173472347597680709441192448139190673828125"
	.align 8
.LC79:
	.string	"867361737988403547205962240695953369140625"
	.align 8
.LC80:
	.string	"4336808689942017736029811203479766845703125"
	.align 8
.LC81:
	.string	"21684043449710088680149056017398834228515625"
	.align 8
.LC82:
	.string	"108420217248550443400745280086994171142578125"
	.align 8
.LC83:
	.string	"542101086242752217003726400434970855712890625"
	.section	.data.rel.local
	.align 32
	.type	powLookupTable64, @object
	.size	powLookupTable64, 128
powLookupTable64:
	.quad	.LC69
	.quad	.LC70
	.quad	.LC71
	.quad	.LC72
	.quad	.LC73
	.quad	.LC74
	.quad	.LC75
	.quad	.LC76
	.quad	.LC77
	.quad	.LC78
	.quad	.LC79
	.quad	.LC80
	.quad	.LC81
	.quad	.LC82
	.quad	.LC83
	.quad	0
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1602224128
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.long	457671715
	.long	-1480217529
	.long	16366
	.long	0
	.section	.rodata.cst4
	.align 4
.LC2:
	.long	1593835520
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC4:
	.long	72481
	.long	55000
	.align 8
.LC5:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 13.1.0-8ubuntu1~20.04.2) 13.1.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
