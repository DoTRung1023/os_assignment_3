CC = gcc
CFLAGS = -Wall -pthread
TARGET = test-mergesort

all: $(TARGET)

$(TARGET): test-mergesort.c mergesort.c
	$(CC) $(CFLAGS) -o $(TARGET) test-mergesort.c mergesort.c

clean:
	rm -f $(TARGET)

.PHONY: all clean