CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=utilfunc.cpp robdd.cpp bddtest.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Bddtest
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