.IGNORE:
all:
	gcc -o engine src/*.c -lSDL2 -lSDL2_image -lSDL2_ttf
clean:
	rm -f test *.exe engine

.PHONY: all