//g++ testbdd.cpp -o testbdd -lbdd


#include <bdd.h>
#include <stdio.h>
#include <time.h>

void test1()
{
	bdd x, y, z, s;
	bdd_init(1000, 100);
	bdd_setvarnum(4);
	
	x = bdd_ithvar(0);
	y = bdd_ithvar(1);
	z = bdd_ithvar(2);
	s = x&y|!z;
	
	bdd_printtable(s);
}

void test2()
{
	const int size = 10;
	bdd x[size], s;
	bdd_init(1000,10);
	bdd_setvarnum(size);
	
	for(int i=0; i<size; i++)
	{
		x[i] = bdd_ithvar(i);
	}
	
	s = x[1] & x[2] & x[3] | x[4] |x[5] |x[6]|x[7] &x[8] &x[9] & x[0];
		
	bdd_printtable(s);
}

int main()
{
	float duration;
	clock_t start, finish;
	
	/*
	start = clock();
	test1();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
	printf( "%f ms\n", duration);
	*/
	
	start = clock();
	test2();
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
	printf( "%f ms\n", duration);
	
	return 0;
}