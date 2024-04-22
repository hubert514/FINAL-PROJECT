.IGNORE:
all:
	gcc src/*.c -o engine -lSDL2 -lSDL2_image -lSDL2_ttf
clean:
	rm -f test *.exe engine

.PHONY: all