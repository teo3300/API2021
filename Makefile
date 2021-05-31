Open: Open.c
	gcc -DEVAL -std=gnu11 -O2 -pipe -static -s -o Open Open.c -lm

testOpen: Open.c
	gcc -std=gnu11 -O2 -pipe -s -o testOpen Open.c -lm

clean:
	-rm Open
	-rm testOpen
	-rm massif.out.*
	-rm callgrind.out.*