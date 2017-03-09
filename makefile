CC=gcc

SOURCE= test.c
OUTPUT=test
OBJECT=test.o
LDFLAGS= -lpthread -lm


$(OUTPUT): $(OBJECT)
	$(CC) $(OBJECT) -o $(OUTPUT) $(LDFLAGS) 

$(OBJECT): $(SOURCE)
	$(CC) -c $(SOURCE) -o test.o $(LDFLAGS)

clean:
	rm -f *.o
	rm -f test
