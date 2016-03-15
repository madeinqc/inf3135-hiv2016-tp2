CC = gcc
EXEC = tp2
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
CCFLAGS = `sdl2-config --cflags`
OS = -D`uname`

.PHONY: all clean test doc

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(OS) -c $<

clean:
	rm -f *.o $(EXEC)
	rm -rf doc

test:
	echo "TODO"

doc:
	doxygen config.doxygen