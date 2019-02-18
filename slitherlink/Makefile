CC=gcc
GEN=src/generator
STR=src/struct
OUT=src/output
SOL=src/solver
#CFLAGS=
#DEPS=
#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)
#
#
#.PHONY: clean

#all:

slitherlink:
	cc src/slitherlink.c -o slitherlink

generator:
	cc $(GEN)/generator.c $(STR)/map.c $(STR)/point.c $(STR)/grid.c $(STR)/edge.c $(OUT)/output.c -o generator.out

solver:
	cc $(GEN)/generator.c $(STR)/map.c $(STR)/point.c $(STR)/grid.c $(STR)/edge.c $(OUT)/output.c $(SOL)/solver.c -o solver.out

clean:
	rm *.out
