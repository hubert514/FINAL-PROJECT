.IGNORE:
all:
	gcc -o engine src/*.c -lSDL2 -lSDL2_image -lSDL2_ttf

cp1:
	gcc -o cp1 src/cp1.c src/set_character.c -lSDL2 -lSDL2_image -lSDL2_ttf

clean:
	rm -f test *.exe engine cp1

.PHONY: all