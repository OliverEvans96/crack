all: crack.out

%.out: %.c
	gcc -lcrypt -lm -fopenmp -Ofast $^ -o $@
