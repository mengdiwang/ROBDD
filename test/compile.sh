g++ -c test1.cpp -o test1.o
g++ test1.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test1
g++ bddtest1.cpp -o bddtest1 -lbdd
g++ -c test2.cpp -o test2.o
g++ test2.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test2
g++ bddtest2.cpp -o bddtest2 -lbdd
g++ -c test3.cpp -o test3.o
g++ test3.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test3
g++ bddtest3.cpp -o bddtest3 -lbdd
g++ -c test4.cpp -o test4.o
g++ test4.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test4
g++ bddtest4.cpp -o bddtest4 -lbdd
g++ -c test5.cpp -o test5.o
g++ test5.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test5
g++ bddtest5.cpp -o bddtest5 -lbdd
g++ -c test6.cpp -o test6.o
g++ test6.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test6
g++ bddtest6.cpp -o bddtest6 -lbdd
g++ -c test7.cpp -o test7.o
g++ test7.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test7
g++ bddtest7.cpp -o bddtest7 -lbdd
g++ -c test8.cpp -o test8.o
g++ test8.o ../bin/CNFExp.o ../bin/bdd.o ../bin/utilfunc.o ../bin/robdd.o -o test8
g++ bddtest8.cpp -o bddtest8 -lbdd
