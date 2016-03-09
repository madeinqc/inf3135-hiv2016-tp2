CC = gcc
EXEC = tp2
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
LDFLAGS = `sdl2-config --libs` -lSDL2_image
CCFLAGS = `sdl2-config --cflags`
OS = -D`uname`

.PHONY: all clean test doc

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $< $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(OS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)

test:
	echo "TODO"

doc:
	doxygen config.doxygen
