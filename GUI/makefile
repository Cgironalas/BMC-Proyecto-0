CC = gcc
GTKLIB = `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS= -lpthread -lm
WARN = -Wall 

all:
	$(CC) -o mendel mendel.c $(WARN) $(GTKLIB) $(LDFLAGS) -export-dynamic
