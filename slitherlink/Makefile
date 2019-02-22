CC=gcc
GENERATOR=src/generator/generator.c
STR=src/struct
OUTPUT=src/output/output.c
SOLVER=src/solver/*.c
TST=src/test
#CFLAGS=
#DEPS=
#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)
#
#
#.PHONY: clean

default:
	@echo "Avalaible options :"
	@echo "make slitherlink -> generates main executable."
	@echo "make test -> generates all tests avalaible."
	@echo "make <name_test> -> generates name_test test. (Avalaible : solver_test, generator_test, edge_test)"

test: solver_test generator_test edge_test
	@echo "Generated all tests' executables."

slitherlink:
	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) src/slitherlink.c -o $@.out
	@echo "Executable" $@.out "generated."

solver_test:
	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) $(SOLVER) $(TST)/solver_test.c -o $@.out
	@echo "Executable" $@.out "generated."

generator_test:
	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) $(TST)/generator_test.c -o $@.out
	@echo "Executable" $@.out "generated."

edge_test:
	$(CC) $(OUTPUT) $(STR)/*.c $(TST)/edge_test.c -o $@.out
	@echo "Executable" $@.out "generated."

clean:
	@rm -fr *.out .Makefile.swp
