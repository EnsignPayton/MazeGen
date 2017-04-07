CC = gcc
CFLAGS = -g -Wall -std=c99 -c
LIBS = -lpng

SRC = main.c mypng.c
OBJ = $(SRC:.c=.o)
TAR = img

$(TAR): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TAR) *.o
