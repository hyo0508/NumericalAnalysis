all: main

%.o: %.c
	gcc -o $@ -O3 -c $^

main: main.o
	gcc -o $@ $< -L ./nr/ -lnr -lm

clean:
	rm *.o main