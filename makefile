.IGNORE:
all:
	gcc src/main.c -o engine -lSDL2 -lSDL2_image

clean:
	rm -f test *.exe engine

.PHONY: all