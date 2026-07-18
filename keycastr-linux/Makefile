CC=gcc
CFLAGS=Wall -O2
LIBS=-lX11 -lXtst

SRC=$(wildcard src/*.c)
OUT=keycastr

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LIBS)

clean:
	rm -f $(OUT)