CC = gcc
CFLAGS = -Wall -pthread

test-mergesort: test-mergesort.c mergesort.c mergesort.h
	$(CC) $(CFLAGS) -o test-mergesort test-mergesort.c mergesort.c

clean:
	rm -f test-mergesort