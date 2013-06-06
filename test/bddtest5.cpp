#include <bdd.h>
#include <stdio.h>
#include <string.h>
int main()
{
	float duration;
	clock_t start, finish;
	start = clock();

	bdd x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,s;
	bdd_init(1<<15,1<<15);
	bdd_setvarnum(40);
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
	x21 = bdd_ithvar(20);
	x22 = bdd_ithvar(21);
	x23 = bdd_ithvar(22);
	x24 = bdd_ithvar(23);
	x25 = bdd_ithvar(24);
	x26 = bdd_ithvar(25);
	x27 = bdd_ithvar(26);
	x28 = bdd_ithvar(27);
	x29 = bdd_ithvar(28);
	x30 = bdd_ithvar(29);
	x31 = bdd_ithvar(30);
	x32 = bdd_ithvar(31);
	x33 = bdd_ithvar(32);
	x34 = bdd_ithvar(33);
	x35 = bdd_ithvar(34);
	x36 = bdd_ithvar(35);
	x37 = bdd_ithvar(36);
	x38 = bdd_ithvar(37);
	x39 = bdd_ithvar(38);
	x40 = bdd_ithvar(39);
	s=!(((!x30 & (x11 ^ x32)) | (x5 & x16) | (x7 ^ (x6 > x18))) & !x2);

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
	printf( "m=%d,n=%d,!(((!x30 & (x11 ^ x32)) | (x5 & x16) | (x7 ^ (x6 > x18))) & !x2)\n", 20,40);
	printf( "%f ms\n", duration);
	return 0;
}
