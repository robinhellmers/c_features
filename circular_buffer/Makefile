CC := gcc
CFLAGS :=

BIN := bin
SRC := src
INCLUDE := include
LIB := lib

all: $(BIN)/main.exe

$(BIN)/main.exe: main.c $(INCLUDE)/*.h $(SRC)/*.c
	$(CC) $(CFLAGS) -I$(INCLUDE) $^ -o $@

clean:
	rm $(BIN)/main.exe