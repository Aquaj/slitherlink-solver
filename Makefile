CC=gcc
GENERATOR=src/generator/generator.c
STR=src/struct
OUTPUT=src/output/output.c
SOLVER=src/solver/*.c
PARSER=src/parser/parser.c
TST=src/test
CFLAGS= -g -Og -std=c11 #  -Wall -Wextra -Werror -pedantic-errors
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
	$(CC) $(CFLAGS) $(GENERATOR) $(PARSER) $(STR)/*.c $(OUTPUT) $(SOLVER) $(TST)/solver_test.c -o $@.out
	@echo "Executable" $@.out "generated."

generator_test:
	$(CC) $(GENERATOR) $(STR)/*.c $(OUTPUT) $(TST)/generator_test.c -o $@.out
	@echo "Executable" $@.out "generated."

parser_test:
	$(CC) $(PARSER) $(STR)/*.c $(OUTPUT) -o $@.out
	@echo "Executable" $@.out "generated."

edge_test:
	$(CC) $(OUTPUT) $(STR)/*.c $(TST)/edge_test.c -o $@.out
	@echo "Executable" $@.out "generated."

point_test:
	$(CC) $(STR)/*.c $(TST)/point_test.c -o $@.out
	@echo "Executable" $@.out "generated."

tree_test:
	$(CC) $(STR)/tree.c $(TST)/tree_test.c -o $@.out
	@echo "Executable" $@.out "generated."

clean:
	@rm -fr *.out .Makefile.swp
