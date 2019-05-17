CPPFLAGS = -std=c++1z -I.
LIBS = -lncurses -lstdc++
CXX = clang

TARGET = life
TESTS = rules_unittest.o
SRC = life.cpp
OBJ = life.o

HEADERS = life.hpp rules.hpp world.hpp

all: $(TARGET)

$(TARGET): $(OBJ) $(HEADERS)
	$(CXX) -o $@ $< $(LIBS)

.o.c:
	$(CXX) $(CPPFLAGS) $<

unittest: $(TESTS)

clean:
	rm -f *.o a.out *~ $(TARGET) core







