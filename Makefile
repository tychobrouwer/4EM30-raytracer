CC = gcc

src = $(wildcard src/*.c) \
	$(wildcard src/camera/*.c) \
	$(wildcard src/base/*.c) \
	$(wildcard src/light/*.c) \
	$(wildcard src/materials/*.c) \
	$(wildcard src/shapes/*.c) \
    $(wildcard src/util/*.c)

ifeq ($(OS),Windows_NT)
	CLEAN_CMD = rm src/camera/*.o src/base/*.o src/light/*.o src/materials/*.o src/shapes/*.o src/util/*.o
else
	CLEAN_CMD = rm -f $(obj)
endif
	

obj = $(src:.c=.o)

LDFLAGS = -lm -O3 -fopenmp -pg
CFLAGS = -lm -O3 -fopenmp -pg



all: raytracer test

raytracer: $(obj)
	$(CC) $(CFLAGS) src/main/raytracer.c -o bin/$@.exe $^ $(LDFLAGS)

test: $(obj)
	$(CC) $(CFLAGS) src/main/test.c -o bin/$@.exe $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	$(CLEAN_CMD)
