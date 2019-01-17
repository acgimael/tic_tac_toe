SRC_DIR = src
BIN_DIR = bin
OBJ = $(SRC_DIR)/tic_tac_toe.o
BIN = $(subst $(SRC_DIR),$(BIN_DIR),$(patsubst %.o,%,$(OBJ)))

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: $(BIN)

$(BIN_DIR)/%: $(SRC_DIR)/%.o
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean

clean:
	-rm -f $(SRC_DIR)/*.o $(BIN_DIR)/*
