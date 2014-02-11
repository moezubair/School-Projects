CC = gcc
CFLAGS 	= -g
OBJECTS = main.o hello.o
OUTPUT = main.out

main:	$(Objects)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTPUT)
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJECTS) $(OUTPUT)
