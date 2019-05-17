CPPFLAGS = -std=c++1z -I. -Wall -pedantic -g
LIBS = -g -lncurses -lstdc++
CXX = clang

TARGET = life
TESTS = rules_unittest.o
SRC = life.cpp
OBJ = life.o

HEADERS = life.hpp rules.hpp world.hpp

all: $(TARGET)

$(TARGET): $(OBJ) 
	$(CXX) -o $@ $< $(LIBS)

$(OBJ): $(HEADERS)

.o.c:
	$(CXX) $(CPPFLAGS) $<

unittest: $(TESTS)

clean:
	rm -f *.o a.out *~ $(TARGET) core







