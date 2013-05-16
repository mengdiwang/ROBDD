CC=g++

CFLAGS=-c -Wall 
#-fno-implicit-templates
SOURCES1=bddtest.cpp robdd.cpp utilfunc.cpp bddlist.h bddhtable.h
SOURCES2=listtest.cpp utilfunc.cpp bddlist.h bddhtable.h
SOURCES3=nqueentest.cpp nqueen.cpp robdd.cpp utilfunc.cpp bddlist.h bddhtable.h
OBJECTS1=$(SOURCES1:.cpp=.o)
OBJECTS2=$(SOURCES2:.cpp=.o)
OBJECTS3=$(SOURCES3:.cpp=.o)
EXECUTABLE1=robdd
EXECUTABLE2=hashtable
EXECUTABLE3=nqueens

all:robdd hashtable nqueens
default: robdd

robdd: ${SOURCES1} ${EXECUTABLE1}
hashtable: ${SOURCES2} ${EXECUTABLE2}
nqueens:  ${SOURCES3} ${EXECUTABLE3}
$(EXECUTABLE1): $(OBJECTS1) 
	$(CC) $(LDFLAGS) $(OBJECTS1) -o $@

$(EXECUTABLE2): $(OBJECTS2) 
	$(CC) $(LDFLAGS) $(OBJECTS2) -o $@

$(EXECUTABLE3): $(OBJECTS3) 
	$(CC) $(LDFLAGS) $(OBJECTS3) -o $@
		
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o robdd hashtable nqueens