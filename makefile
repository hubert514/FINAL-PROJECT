.IGNORE:
all:
	gcc src/*.c -o engine -L./lib -lSDL2 -lSDL2_image

clean:
	rm -f test *.exe engine

.PHONY: all