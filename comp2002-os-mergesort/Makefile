CC = gcc
CFLAGS = -Wall -pthread
TARGET = test-mergesort
EXTRA_TESTS = test_basic test_merge test_merge_advanced test_merge_boundary test_merge_stress

all: $(TARGET)

$(TARGET): test-mergesort.c mergesort.c
	$(CC) $(CFLAGS) -o $(TARGET) test-mergesort.c mergesort.c

tests: $(EXTRA_TESTS)

test_basic: test_basic.c mergesort.c
	$(CC) $(CFLAGS) -o test_basic test_basic.c mergesort.c

test_merge: test_merge.c mergesort.c
	$(CC) $(CFLAGS) -o test_merge test_merge.c mergesort.c

test_merge_advanced: test_merge_advanced.c mergesort.c
	$(CC) $(CFLAGS) -o test_merge_advanced test_merge_advanced.c mergesort.c

test_merge_boundary: test_merge_boundary.c mergesort.c
	$(CC) $(CFLAGS) -o test_merge_boundary test_merge_boundary.c mergesort.c

test_merge_stress: test_merge_stress.c mergesort.c
	$(CC) $(CFLAGS) -o test_merge_stress test_merge_stress.c mergesort.c

clean:
	rm -f $(TARGET) $(EXTRA_TESTS)

.PHONY: all tests clean