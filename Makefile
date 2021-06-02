CC=gcc
CFLAGS=-lcrypt -lm -fopenmp -Ofast 

crack: crack.c
	$(CC) $(CFLAGS) $^ -o $@
