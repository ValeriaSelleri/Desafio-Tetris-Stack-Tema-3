CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c tetris.c stack.c
OBJ = $(SRC:.c=.o)
TARGET = tetris_stack

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
