CC=gcc
#CFLAGS=
#DEPS=
#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)
#
#
#.PHONY: clean

#all:

generator:
	cc src/generator/generator.c src/struct/map.c src/struct/point.c src/struct/grid.c src/struct/edge.c -o generator.out

output:
	cc src/generator/generator.c src/generator/loop.c src/struct/map.c src/struct/graph.c src/annexe/tsp.c src/struct/edge.c src/output/output.c
clean:
	rm *.out
