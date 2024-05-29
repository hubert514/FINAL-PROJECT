CC = gcc
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

.IGNORE:
all:
	$(CC) -o engine src/*.c $(LIBS)

cp1:
	$(CC) -o cp1 src/cp1.c src/set_character.c src/init.c src/show_text.c src/show_image.c $(LIBS)

menu:
	$(CC) -o menu src/menu.c src/init.c src/show_image.c src/show_text.c $(LIBS)

install:
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

clean:
	rm -f test *.exe engine cp1 menu

.PHONY: all cp1 menu clean