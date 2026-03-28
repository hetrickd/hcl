CC = gcc
CFLAGS = -Wall -O3 -std=c11

TARGET = hcl
SRCS = src/sort.c src/main.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
