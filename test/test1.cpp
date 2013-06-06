#include "../robdd.h"
#include "../bdd.h"
#include <stdio.h>
#include <string.h>
int main()
{
	float duration;
	clock_t start, finish;
	start = clock();

	bdd x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,s;
	Robdd *bdd = new Robdd(10);
	bdd->InitVars(10);
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
	s.robdd=bdd;
	s=!x5;

	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
	printf( "%f ms\n", duration);
	printf( "m=%d n=%d\n!x5\n", 7,10);
	return 0;
}
