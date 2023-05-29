CFLAGS  = -Wall
CFLAGS2 = -lm -o
all:	prog

prog:	data100.o data500.o data1000.o data30.o dfs.o bfs.o clique.o
	cc data100.o data500.o data1000.o dfs.o $(CFLAGS2) dfs
	cc data100.o data500.o data1000.o bfs.o $(CFLAGS2) bfs
	cc data30.o clique.o $(CFLAGS2) clique

data100.o:	data100.c data100.h
data500.o:	data500.c data500.h
data1000.o:	data1000.c data1000.h
dfs.o: dfs.c data100.h data500.h data1000.h
bfd.o: bfs.c data100.h data500.h data1000.h
data30.o:	data30.c data30.h
clique.o:	clique.c data30.h
c.o:
	cc -c $< $(CFLAGS)

.SUFFIXES:	.c .o


clean:	distclean
		-rm clique dfs bfs

distclean:
		-rm *.o

.PHONY: all distclean