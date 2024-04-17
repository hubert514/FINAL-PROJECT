.IGNORE:
all:
	gcc test.c -o test -lcurl -lpthread

clean:
	rm -f test

.PHONY: all