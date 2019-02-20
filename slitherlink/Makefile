CC=gcc
GENERATOR=src/generator/generator.c
STR=src/struct
OUTPUT=src/output/output.c
SOLVER=src/solver/solver.c
TST=src/test
#CFLAGS=
#DEPS=
#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)
#
#
#.PHONY: clean

all: slitherlink solver

default:
	@echo "Try 'make slitherlink' or 'make solver'. Stop."

#Slitherlink:
#	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) src/slitherlink.c -o $@.out
#	@echo "Executable" $@.out "generated."

Solver_Test:
	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) $(SOLVER) $(TST)/solver_test.c -o $@.out
	@echo "Executable" $@.out "generated."

Generator_Test:
	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) $(TST)/generator_test.c -o $@.out
	@echo "Executable" $@.out "generated."

Edge_Test:
	$(CC) $(STR)/edge.c $(STR)/map.c $(STR)/point.c $(TST)/edge_test.c -o $@.out
	@echo "Executable" $@.out "generated."

clean:
	@rm -fr *.out .Makefile.swp
