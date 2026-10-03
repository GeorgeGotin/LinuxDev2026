GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so *.out

CFLAGS = -Wall -fPIC

all: prog prog-a prog-so README

prog:   const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc $(CFLAGS) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc $(CFLAGS) -L. $< -loutput -o $@

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

fun.o: outlib.h

README: prog
	./$< 2> $@

test:prog prog-a prog-so
	./prog          > def_o_0.out 2>&1
	./prog a        > def_o_1.out 2>&1
	./prog a b c    > def_o_3.out 2>&1
	./prog-a        > def_a_0.out 2>&1
	./prog-a a      > def_a_1.out 2>&1
	./prog-a a b c  > def_a_3.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so       > def_so_0.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so a     > def_so_1.out 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so a b c > def_so_3.out 2>&1
	cmp def_o_0.out def_a_0.out
	cmp def_o_1.out def_a_1.out
	cmp def_o_3.out def_a_3.out
	cmp def_o_0.out def_so_0.out
	cmp def_o_1.out def_so_1.out
	cmp def_o_3.out def_so_3.out

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)