CC=cc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
CLIBS=-lSDL2
CSRS=main.c
BIN=rumble_pad

$(BIN):$(CSRS)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

.PHONY:clean

clean:
	rm -rf $(BIN)
