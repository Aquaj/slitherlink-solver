#ifndef ___output_h___
#define ___output_h___

#include "../generator/generator.h"
#include "../struct/map.h"

struct map;
struct grid;

void show_help();
void search_all_possible_solutions(int _verbose);
void print_grid(struct map* my_map, struct grid* my_grid, int _verbose);
void generate_grid_unique(int _verbose);
void write_result_to_file();
void verbose_output();
void show_version();

#endif
