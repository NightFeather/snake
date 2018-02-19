CC=gcc
TARGET=snake
CFLAGS += -Wall
SRCDIR=src/
INCLUDEDIR=include/
BUILDDIR="build/"
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))

default: ${TARGET}

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) $(OBJS) -o $(TARGET)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -c $< -o $@

clean:
	rm build/* $(TARGET)
