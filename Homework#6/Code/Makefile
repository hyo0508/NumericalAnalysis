all: datafit

%.o: %.c
	gcc -o $@ -c $^

datafit: datafit.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

clean:
	rm *.o datafit