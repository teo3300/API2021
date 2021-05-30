Open: Open.c
	gcc -DEVAL -std=gnu11 -O2 -pipe -static -s -o Open Open.c -lm

testOpen: Open.c
	gcc -std=gnu11 -O2 -g -o testOpen Open.c

Open.c: header.h support.h heapHandler.c openPart.c
	cat header.h support.h heapHandler.c openPart.c > Open.c

clean:
	-rm Open
	-rm testOpen
	-rm massif.out.*
