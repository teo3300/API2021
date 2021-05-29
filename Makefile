Open: Open.c
	gcc -DEVAL -std=gnu11 -O2 -pipe -static -s -o Open Open.c -lm

Open.c: header.h support.h heapHandler.c openPart.c
	cat header.h support.h heapHandler.c openPart.c > Open.c

clean:
	rm massif.out.*
	rm Open
