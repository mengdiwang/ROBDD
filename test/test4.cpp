#include "../robdd.h"
#include "../bdd.h"
#include <stdio.h>
#include <string.h>
int main()
{
	float duration;
	clock_t start, finish;
	start = clock();

	bdd x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,s;
	Robdd *bdd = new Robdd(1<<15,1<<15);
	bdd->InitVars(20);
	x1.robdd = bdd;
	x1.GetIthvar(1);
	x2.robdd = bdd;
	x2.GetIthvar(2);
	x3.robdd = bdd;
	x3.GetIthvar(3);
	x4.robdd = bdd;
	x4.GetIthvar(4);
	x5.robdd = bdd;
	x5.GetIthvar(5);
	x6.robdd = bdd;
	x6.GetIthvar(6);
	x7.robdd = bdd;
	x7.GetIthvar(7);
	x8.robdd = bdd;
	x8.GetIthvar(8);
	x9.robdd = bdd;
	x9.GetIthvar(9);
	x10.robdd = bdd;
	x10.GetIthvar(10);
	x11.robdd = bdd;
	x11.GetIthvar(11);
	x12.robdd = bdd;
	x12.GetIthvar(12);
	x13.robdd = bdd;
	x13.GetIthvar(13);
	x14.robdd = bdd;
	x14.GetIthvar(14);
	x15.robdd = bdd;
	x15.GetIthvar(15);
	x16.robdd = bdd;
	x16.GetIthvar(16);
	x17.robdd = bdd;
	x17.GetIthvar(17);
	x18.robdd = bdd;
	x18.GetIthvar(18);
	x19.robdd = bdd;
	x19.GetIthvar(19);
	x20.robdd = bdd;
	x20.GetIthvar(20);
	s.robdd=bdd;
	s=!((((((x2 | !x11) > !x16) > x9) & ((!x9 > (x6 ^ ((x9 & x19) > x16))) > (x6 | (!x4 > x16)))) | (x18 & x19 & (x17 | !x9) & !(((x2 & x15) ^ !x2) & (x5 | x11) & !x12 & (x3 ^ x18)))) & !(!x17 | (x18 & !x10)));

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
	printf( "m=%d,n=%d,!((((((x2 | !x11) > !x16) > x9) & ((!x9 > (x6 ^ ((x9 & x19) > x16))) > (x6 | (!x4 > x16)))) | (x18 & x19 & (x17 | !x9) & !(((x2 & x15) ^ !x2) & (x5 | x11) & !x12 & (x3 ^ x18)))) & !(!x17 | (x18 & !x10)))\n", 80,20);
	printf( "%f ms\n", duration);
	return 0;
}
