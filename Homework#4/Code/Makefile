all: gaussian uniform

%.o: %.c
	gcc -o $@ -c $^

gaussian: gaussian.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

uniform: uniform.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

clean:
	rm *.o gaussian uniform