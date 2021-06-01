bin/Open: main.c
	gcc -DEVAL -Wall -Werror -std=gnu11 -O2 -pipe -static -s -o bin/Open main.c -lm

bin/UpTo18: main.c
	gcc -DEVAL -Wall -Werror -std=gnu11 -O2 -pipe -static -s -o bin/UpTo18 main.c -lm

bin/UpTo30: main.c
	gcc -DEVAL -Wall -Werror -std=gnu11 -O2 -pipe -static -s -o bin/UpTo30 main.c -lm

bin/CumLaude: main.c
	gcc -DEVAL -Wall -Werror -std=gnu11 -O2 -pipe -static -s -o bin/CumLaude main.c -lm

bin/test: main.c
	gcc -g -std=gnu11 -O2 -o bin/test main.c -lm

all: bin/Open bin/UpTo18 bin/UpTo30 bin/CumLaude bin/test

clean:
	-rm bin/*
	-rm massif.out.*
	-rm callgrind.out.*