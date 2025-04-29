# Author: Hoai Dinh

PROJ := disjoint_set

OBJ_DIR := ./obj

EXE  := $(PROJ)
SRCS := ${wildcard ./src/*.c}
OBJS := ${SRCS:./src/%.c=$(OBJ_DIR)/%.o}

CC := gcc

all: $(EXE)

$(EXE): $(OBJ_DIR) $(OBJS)
	$(CC) -g $(OBJS) -o $@

$(OBJ_DIR): $(SRC)
	mkdir -p $(OBJ_DIR)

$(OBJS): $(OBJ_DIR)/%.o : ./src/%.c
	$(CC) -g -c $<
	mv *.o $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(EXE)