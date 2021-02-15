CC := gcc
CFLAGS := -g

BIN := bin
SRC := src
INC := inc
LIB := lib

all: clean $(BIN)/main.exe

$(BIN)/main.exe: main.c $(INC)/*.h $(SRC)/*.c
	$(CC) $(CFLAGS) -I$(INC) $^ -o $@

clean:
	del $(BIN)\main.exe