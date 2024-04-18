.IGNORE:
all:
	# gcc test.c -o test -lcurl -lpthread
	gcc src/main.c -o engine

clean:
	rm -f test *.exe engine

.PHONY: all