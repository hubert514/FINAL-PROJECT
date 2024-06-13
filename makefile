CC = gcc
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lgif

.IGNORE:
all:
	$(CC) -o engine src/*.c $(LIBS)

cp1:
	$(CC) -o cp1 src/cp1.c src/set_character.c src/init.c src/show_text.c src/show_image.c src/playSound.c src/show_GIF.c $(LIBS)

menu:
	$(CC) -o menu src/menutest.c src/init.c src/show_image.c src/show_text.c $(LIBS)

sound:
	$(CC) -o sound src/playsound.c src/init.c src/show_image.c src/show_text.c $(LIBS)
	
gif:
	$(CC) -o gif src/show_GIF.c src/init.c src/show_image.c src/show_text.c $(LIBS)

install:
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libgif-dev


clean:
	rm -f test *.exe engine cp1 menu

.PHONY: all cp1 menu gif clean