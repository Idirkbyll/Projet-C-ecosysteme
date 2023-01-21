#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter
CC = gcc

PROGRAMS =   tests_ecosys ecosys test_ecosys2

.PHONY:	all clean

all: $(PROGRAMS)

test_ecosys2: main_test2.o ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys: ecosys.o main_ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

main_test2.o: main_test2.c
	gcc $(CFLAGS) -c main_test2.c 

ecosys.o: ecosys.c
	gcc $(CFLAGS) -c ecosys.c

main_tests.o: main_tests.c
	gcc $(CFLAGS) -c main_tests.c


main_ecosys.o: main_ecosys.c 
	gcc $(CFLAGS) -c main_ecosys.c

#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
