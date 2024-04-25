print-%:; @echo $($*)

CC = gcc
LD = gcc

CCFLAGS  = -std=c2x
CCFLAGS += -O2
CCFLAGS += -g
CCFLAGS += -Wall
CCFLAGS += -Wextra
CCFLAGS += -Wpedantic
CCFLAGS += -Wfloat-equal
CCFLAGS += -Wstrict-aliasing
CCFLAGS += -Wswitch-default
CCFLAGS += -Wformat=2
CCFLAGS += -Wno-unused-parameter
CCFLAGS += -Wno-strict-prototypes

LDFLAGS  = -lm
LDFLAGS += -lraylib

BIN = bin
SRC = $(shell find src -name "*.c")
OBJ = $(SRC:%.c=$(BIN)/%.o)
DEP = $(SRC:%.c=$(BIN)/%.d)
OUT = $(BIN)/game

-include $(DEP)

$(BIN):
	mkdir -p $@

dirs: $(BIN)
	rsync -a --include '*/' --exclude '*' "src" "bin"

$(OBJ): $(BIN)/%.o: %.c
	$(CC) -o $@ -MP -MMD -c $(CCFLAGS) $(INCFLAGS) $<

main: dirs $(BIN)/src/main.o $(BIN)/src/sprite.o $(BIN)/src/player.o $(BIN)/src/notes.o $(BIN)/src/dialogue.o $(BIN)/src/dyn_array.o
	$(LD) -o bin/main $(BIN)/src/main.o $(BIN)/src/sprite.o $(BIN)/src/player.o $(BIN)/src/notes.o $(BIN)/src/dialogue.o $(BIN)/src/dyn_array.o $(LDFLAGS)

all: dirs main

clean:
	rm -rf bin
