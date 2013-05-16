CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=bddlist.cpp nqueen.cpp utilfunc.cpp bddhtable.cpp robdd.cpp BddMain.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MIPSsim
TEST=robdd

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

robdd: $(SOURCES) $(TEST)
	
$(TEST): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o robdd