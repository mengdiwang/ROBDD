g++ -c test1.cpp -o test1.o
g++ test1.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test1
g++ -c test2.cpp -o test2.o
g++ test2.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test2
g++ -c test3.cpp -o test3.o
g++ test3.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test3
g++ -c test4.cpp -o test4.o
g++ test4.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test4
