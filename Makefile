CC = g++

src = $(wildcard src/*.c) \
	$(wildcard src/camera/*.c) \
	$(wildcard src/base/*.c) \
	$(wildcard src/light/*.c) \
	$(wildcard src/materials/*.c) \
	$(wildcard src/shapes/*.c) \
    $(wildcard src/util/*.c)

ifeq ($(OS),Windows_NT)
	CLEAN_CMD = del src\camera\*.o src\base\*.o src\light\*.o src\materials\*.o src\shapes\*.o src\util\*.o
else
	CLEAN_CMD = rm -f $(obj)
endif
	

obj = $(src:.c=.o)

LDFLAGS = -lm -O3

all: raytracer test

raytracer: $(obj)
	$(CC) src/main/raytracer.c -o bin/$@.exe $^ $(LDFLAGS)

test: $(obj)
	$(CC) src/main/test.c -o bin/$@.exe $^ $(LDFLAGS)

.PHONY: clean

clean:
	$(CLEAN_CMD)
