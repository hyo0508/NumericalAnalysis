SRCS:=gaussj.c lubksb.c ludcmp.c nrutil.c svdcmp.c
OBJS:=$(SRCS:.c=.o)
STATIC_LIB:=libnr.a

all: $(STATIC_LIB)

%.o: %.c
	gcc -o $@ -c $^

$(STATIC_LIB): $(OBJS)
	ar cr $@ $^

clean:
	rm $(OBJS) $(STATIC_LIB)