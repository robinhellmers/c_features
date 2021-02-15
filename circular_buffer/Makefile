CC := gcc
CFLAGS :=

BIN := bin
SRC := src
INC := inc
LIB := lib

all: $(BIN)/main.exe

$(BIN)/main.exe: main.c $(INC)/*.h $(SRC)/*.c
	$(CC) $(CFLAGS) -I$(INC) $^ -o $@

clean:
	rm $(BIN)/main.exe