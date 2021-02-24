CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=`pkg-config --libs gtk+-3.0`
CFLAGS+= -DMY_USE_LIST
CFLAGS+=`pkg-config --cflags gtk+-3.0`

all: main

main: main.o UI.o session_controller.o session_view.o connect_struct_UI.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< $^


clean:
	rm -f *.o
	rm -f main


process:
	make clean
	make
	./main