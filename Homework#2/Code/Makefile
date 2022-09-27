all: main interesting

%.o: %.c
	gcc -o $@ -O3 -c $^

main: main.o
	gcc -o $@ $< -L ./nr/ -lnr -lm

interesting: interesting.o
	gcc -o $@ $< -L ./nr/ -lnr -lm

clean:
	rm *.o main interesting