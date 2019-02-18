CC=gcc
GENERATOR=src/generator/generator.c
STR=src/struct
OUTPUT=src/output/output.c
SOLVER=src/solver/solver.c
#CFLAGS=
#DEPS=
#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)
#
#
#.PHONY: clean

#all:

default:
	@echo "Try 'make slitherlink' or 'make solver'. Stop."

slitherlink:
	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) src/slitherlink.c -o $@.out

# this need to be removed later when the test on solver are done
solver:
	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) $(SOLVER) -o $@.out

clean:
	@rm -fr *.out .Makefile.swp
