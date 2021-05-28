Open: Open.c
	gcc -DEVAL -std=gnu11 -O2 -pipe -static -s -o Open Open.c -lm