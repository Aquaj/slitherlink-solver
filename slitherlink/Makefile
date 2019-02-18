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
	$(CC) src/slitherlink.c $(GEN)/generator.c $(STR)/*.c -o $@.out

# this need to be removed later when the test on solver are done
solver:
	$(CC) $(GEN)/generator.c $(STR)/*.c $(OUT)/output.c $(SOL)/solver.c -o $@.out

clean:
	@rm -fr *.out .Makefile.swp
