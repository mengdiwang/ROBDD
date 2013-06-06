#include <bdd.h>
#include <stdio.h>
#include <string.h>
int main()
{
	float duration;
	clock_t start, finish;
	start = clock();

	bdd x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,s;
	bdd_init(1<<15,1<<15);
	bdd_setvarnum(20);
	x1 = bdd_ithvar(0);
	x2 = bdd_ithvar(1);
	x3 = bdd_ithvar(2);
	x4 = bdd_ithvar(3);
	x5 = bdd_ithvar(4);
	x6 = bdd_ithvar(5);
	x7 = bdd_ithvar(6);
	x8 = bdd_ithvar(7);
	x9 = bdd_ithvar(8);
	x10 = bdd_ithvar(9);
	x11 = bdd_ithvar(10);
	x12 = bdd_ithvar(11);
	x13 = bdd_ithvar(12);
	x14 = bdd_ithvar(13);
	x15 = bdd_ithvar(14);
	x16 = bdd_ithvar(15);
	x17 = bdd_ithvar(16);
	x18 = bdd_ithvar(17);
	x19 = bdd_ithvar(18);
	x20 = bdd_ithvar(19);
	s=!(x4 & !x2 & (((((x10 & x15) > x8) > x9) & !((x4 ^ (x4 > (x3 | x19))) ^ (x16 > (x6 ^ x16)))) | (x14 & (x13 ^ !(x20 ^ !x8)) & (x2 | x17 | !x9) & ((x13 & !x2) > x16))));

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
	printf( "m=%d,n=%d,!(x4 & !x2 & (((((x10 & x15) > x8) > x9) & !((x4 ^ (x4 > (x3 | x19))) ^ (x16 > (x6 ^ x16)))) | (x14 & (x13 ^ !(x20 ^ !x8)) & (x2 | x17 | !x9) & ((x13 & !x2) > x16))))\n", 60,20);
	printf( "%f ms\n", duration);
	return 0;
}
