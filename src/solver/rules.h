#ifndef ___rules_h___
#define ___rules_h___

#include "rule.h"

struct sub_grid;

int init_rules(struct sub_grid **my_rules);
void free_rules(struct sub_grid **my_rules, int nb_rules);

#endif
