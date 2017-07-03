CC=g++
OBJ=triangle.o
CFLAGS=-Wall -std=c++11 -I/usr/include/libpng16
LDFLAGS=-L/usr/lib -lpng16

triangle: $(OBJ)
	$(CC) -o triangle $(OBJ) $(LDFLAGS)

triangle.o: triangle.cpp
	$(CC) -c triangle.cpp $(CFLAGS)

.PHONY: clean
clean:
	-rm triangle $(OBJ)
