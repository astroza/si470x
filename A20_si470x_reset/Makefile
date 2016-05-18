CC=gcc
CFLAGS=-I.
DEPS = gpio_lib.h
OBJ = main.o gpio_lib.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

reset_tuner_si470x: $(OBJ)
	gcc -o $@ $^

clean:
	rm -f *.o reset_tuner_si470x
