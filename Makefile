CC = gcc
CFLAGS = -Wall -Wextra -g

INCLUDES = -Iinclude
LIBS = -lm
SRC = $(wildcard src/*.c)
OBJ = obj
OBJS = $(patsubst src/%.c,$(OBJ)/%.o,$(SRC))

REMOVE = rm -r

MAIN = guiao

.DEFAULT_GOAL = build

build: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $^

$(OBJ)/%.o:	src/%.c
	@mkdir -p $(OBJ)
	$(CC) -c $(INCLUDES) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	$(REMOVE) $(OBJ)/*.o
	$(REMOVE) $(MAIN)