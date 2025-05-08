CC = gcc
CFLAGS = -Wall -O2 -Iinclude
SRC = src/memalloc.c src/heap.c src/policy.c src/metric.c test/workload.c
OBJ = $(SRC:.c=.o)
TARGET = memtest

all: $(TARGET)

$(TARGET): main.c $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(SRC)

clean:
	rm -f $(TARGET) src/*.o
