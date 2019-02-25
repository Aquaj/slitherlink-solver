#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "rules.h"

/**************************************************

*    Title: Slitherlink Deduction Rules
*    Authors: David Anderson, Dan Hamalainen, Edward Kwiatkowski, Valerie Lambert, Sam Spaeth
*    Date: 2016
*    Availability: http://cs.carleton.edu/cs_comps/1516/slither/final-results/index.html

***************************************************/

int init_rules(struct sub_grid **my_rules){
  int i = 0;
  struct coord my_edge, my_square;


  /**
  * Rule #0
  * Before   After
  * .   .    . x .
  *   0      x   x
  * .   .    . x .
  */
  my_rules[i] = rule_init(1, 1);

  my_square.x = 0;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '0');

  my_edge.x = 0;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 0);
  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 0);
  my_edge.x = 0;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);

  i++;
  /**
  * Rule #1
  * Before       After
  * .   .   .    .   .   .
  *     x
  * . x . x .    .   .   .
  *                  x
  * .   .   .    .   .   .
  */

  my_rules[i] = rule_init(2, 2);
  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);

  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #2
  * Before       After
  * .   .   .    .   .   .
  *     |
  * . - .   .    .   . x .
  *                  x
  * .   .   .    .   .   .
  */
  my_rules[i] = rule_init(2, 2);
  my_edge.x = 1;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  draw_rule_edge(my_rules[i], my_edge, 0, 1);

  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 1, 0);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #3
  * Before       After
  * .   .   .    .   .   .
  *                  x
  * . - . - .    .   .   .
  *                  x
  * .   .   .    .   .   .
  */
  my_rules[i] = rule_init(2, 2);
  my_edge.x = 1;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 1;
  my_edge.y = 1;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);

  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #4
  * Before       After
  * .   .   .    .   .   .
  *     x
  * . - .   .    .   . - .
  *     x
  * .   .   .    .   .   .
  */
  my_rules[i] = rule_init(2, 2);
  my_edge.x = 1;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);

  my_edge.x = 1;
  my_edge.y = 1;
  draw_rule_edge(my_rules[i], my_edge, 1, 0);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #5
  * Before       After
  * .   .   .    .   .   .
  *     x
  * . - . x .    .   .   .
  *                  |
  * .   .   .    .   .   .
  */
  my_rules[i] = rule_init(2, 2);
  my_edge.x = 1;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);

  my_edge.x = 1;
  my_edge.y = 1;
  draw_rule_edge(my_rules[i], my_edge, 0, 0);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #6
  * Before   After
  * . - .    .   .
  *   1      x   x
  * .   .    . x .
  */
  my_rules[i] = rule_init(1, 1);

  my_square.x = 0;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '1');
  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);

  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 0);
  my_edge.x = 0;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #7
  * Before   After
  * .   .    . - .
  * x 1 x
  * . x .    .   .
  */
  my_rules[i] = rule_init(1, 1);

  my_square.x = 0;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '1');

  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);


  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 0);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #8
  * Before   After
  * . - .    .   .
  * | 2          x
  * .   .    . x .
  */
  my_rules[i] = rule_init(1, 1);

  my_square.x = 0;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '2');

  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 0, 1);

  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #9
  * Before   After
  * .   .    . - .
  *   2 x    |
  * . x .    .   .
  */
  my_rules[i] = rule_init(1, 1);

  my_square.x = 0;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '2');
  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);

  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 0);
  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 0, 0);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #10
  * Before   After
  * . - .    .   .
  *   2      x   x
  * . - .    .   .
  */
  my_rules[i] = rule_init(1, 1);

  my_square.x = 0;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '2');
  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);
  my_edge.x = 1;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 1);

  my_edge.x = 0;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #11
  * Before   After
  * .   .    . - .
  * x 2 x
  * .   .    . - .
  */
  my_rules[i] = rule_init(1, 1);

  my_square.x = 0;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '2');
  my_edge.x = 0;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);

  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 0);
  my_edge.x = 1;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 0);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /**
  * Rule #12
  * Before   After
  * . x .    .   .
  *   3      |   |
  * .   .    . - .
  */
  my_rules[i] = rule_init(1, 1);

  my_square.x = 0;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '3');
  my_edge.x = 0;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);

  my_edge.x = 0;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 0;
  my_edge.y = 1;
  draw_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 1;
  my_edge.y = 0;
  draw_rule_edge(my_rules[i], my_edge, 1, 0);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(1, 1);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /** Rule 13
  * Before         After
  * .   .   .   .      .   .   .   .
  *         |
  * .   .   . x .      .   .   .   .
  *       1                x
  * .   .   .   .      .   . x .   .
  *
  * .   .   .   .      .   .   .   .
  *
  */
  my_rules[i] = rule_init(2, 2);

  my_square.x = 1;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '1');
  my_edge.x = 0;
  my_edge.y = 1;
  draw_rule_edge(my_rules[i], my_edge, 0, 1);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);

  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 2;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 0);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /** Rule 14
  * Before         After
  * .   .   .   .      .   .   .   .
  *         |
  * .   .   .   .      .   .   . x .
  *     x 1
  * .   . x .   .      .   .   .   .
  *
  * .   .   .   .      .   .   .   .
  *
  */
  my_rules[i] = rule_init(2, 2);

  my_square.x = 1;
  my_square.y = 0;
  set_rule_square(my_rules[i], my_square, '1');
  my_edge.x = 0;
  my_edge.y = 1;
  draw_rule_edge(my_rules[i], my_edge, 0, 1);
  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);
  my_edge.x = 2;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);

  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 1, 0);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /** Rule 15
  * Before         After
  * .   .   .   .      .   .   .   .
  *
  * .   .   .   .      .   .   .   .
  *       1                x
  * . x .   .   .      .   . x .   .
  *     x
  * .   .   .   .      .   .   .   .
  *
  */
  my_rules[i] = rule_init(2, 2);

  my_square.x = 0;
  my_square.y = 1;
  set_rule_square(my_rules[i], my_square, '1');
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 1);
  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(my_rules[i], my_edge, 1, 1);

  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 0, 0);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(my_rules[i], my_edge, 1, 0);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  my_rules[i] = rule_init(2, 2);
  rotate_rule(my_rules[i-1], my_rules[i], 1);

  i++;

  /** Rule 16
     * Before         After
     * .   .   .   .      .   .   .   .
     *     |   |
     * . x .   . x .      .   . _ .   .
     *       1
     * .   .   .   .      .   .   .   .
     *
     * .   .   .   .      .   .   .   .
     *
     */
     my_rules[i] = rule_init(3, 3);

     my_square.x = 1;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '1');
     my_edge.x = 0;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 0;
     my_edge.y = 2;
     draw_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 1;
     my_edge.y = 2;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);
     my_edge.x = 1;
     my_edge.y = 0;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);

     my_edge.x = 1;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     /** Rule 17
     * Before         After
     * .   .   .   .      .   .   .   .
     *
     * .   . x .   .      .   .   .   .
     *       2                |
     * . x .   .   .      .   . _ .   .
     *     x
     * .   .   .   .      .   .   .   .
     *
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 0;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '2');
     my_edge.x = 1;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 1;
     my_edge.y = 0;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);
     my_edge.x = 0;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);

     my_edge.x = 1;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 0;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     /** Rule 19
     * Before         After
     * .   .   .   .      .   .   .   .
     *     x   x
     * .   .   . x .      . _ .   .   .
     *       2
     * .   .   .   .      .   .   .   .
     *
     * .   .   .   .      .   .   .   .
     *
     */
     my_rules[i] = rule_init(3, 3);

     my_square.x = 1;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '2');
     my_edge.x = 0;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 0;
     my_edge.y = 2;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 1;
     my_edge.y = 2;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);

     my_edge.x = 1;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     /** Rule 20
     * Before         After
     * .   .   .   .      .   .   .   .
     *         |
     * .   .   .   .      .   .   . x .
     *       3                |
     * .   .   .   .      .   . _ .   .
     *
     * .   .   .   .      .   .   .   .
     *
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 1;
     my_square.y = 0;
     set_rule_square(my_rules[i], my_square, '3');
     my_edge.x = 0;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 0, 1);

     my_edge.x = 2;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 1;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 1;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     /** Rule 21
     * Before         After
     * .   .   .   .      .   .   .   .
     *
     * .   .   .   .      .   .   .   .
     *       3                |
     * . x .   .   .      .   . _ .   .
     *     x
     * .   .   .   .      .   .   .   .
     *
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 0;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '3');
     my_edge.x = 1;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 1;
     my_edge.y = 0;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);

     my_edge.x = 1;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 0;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /** Rule 22
     * Before         After
     * .   .   .      .   .   .
     *   3   1
     * .   .   .      . _ .   .
     * x   x
     * .   .   .      .   .   .
     *
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 0;
     my_square.y = 0;
     set_rule_square(my_rules[i], my_square, '3');
     my_square.x = 0;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '1');
     my_edge.x = 1;
     my_edge.y = 0;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 1;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);

     my_edge.x = 1;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /** Rule 23
    * Before         After
    * .   .   .   .      .   .   .   .
    *     x   x
    * . x .   . _ .      .   .   .   .
    *
    * . x .   . x .      .   .   .   .
    *         x              |
    * .   .   .   .      .   .   .   .
    *
    */
    my_rules[i] = rule_init(3, 3);

    my_edge.x = 0;
    my_edge.y = 1;
    cross_rule_edge(my_rules[i], my_edge, 0, 1);
    my_edge.x = 0;
    my_edge.y = 2;
    cross_rule_edge(my_rules[i], my_edge, 0, 1);
    my_edge.x = 2;
    my_edge.y = 2;
    cross_rule_edge(my_rules[i], my_edge, 0, 1);
    my_edge.x = 1;
    my_edge.y = 2;
    draw_rule_edge(my_rules[i], my_edge, 1, 1);
    my_edge.x = 1;
    my_edge.y = 0;
    cross_rule_edge(my_rules[i], my_edge, 1, 1);
    my_edge.x = 2;
    my_edge.y = 0;
    cross_rule_edge(my_rules[i], my_edge, 1, 1);
    my_edge.x = 2;
    my_edge.y = 2;
    cross_rule_edge(my_rules[i], my_edge, 1, 1);

    my_edge.x = 2;
    my_edge.y = 1;
    draw_rule_edge(my_rules[i], my_edge, 0, 0);

    i++;

    my_rules[i] = rule_init(3, 3);
    rotate_rule(my_rules[i-1], my_rules[i], 1);

    i++;

    my_rules[i] = rule_init(3, 3);
    rotate_rule(my_rules[i-1], my_rules[i], 1);

    i++;

    my_rules[i] = rule_init(3, 3);
    rotate_rule(my_rules[i-1], my_rules[i], 1);

    i++;
    /** Rule 24
     * Before         After
     *
     * . _ .      .   .
     * |   |
     * .   .      . x .
     *
     */
     my_rules[i] = rule_init(1, 1);

     my_edge.x = 0;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 0;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 0;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 1);

     my_edge.x = 1;
     my_edge.y = 0;
     cross_rule_edge(my_rules[i], my_edge, 1, 0);

     i++;

     my_rules[i] = rule_init(1, 1);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(1, 1);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(1, 1);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /** Rule 25
     * Before         After
     *
     * . x .   .     .   .   .
     * x 1
     * .   .   .     .   .   .
     *       1               x
     * .   .   .     .   . x .
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 0;
     my_square.y = 0;
     set_rule_square(my_rules[i], my_square, '1');
     my_square.x = 1;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '1');
     my_edge.x = 0;
     my_edge.y = 0;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 0;
     my_edge.y = 0;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);

     my_edge.x = 2;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 1;
     my_edge.y = 2;
     cross_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /** Rule 26
     * Before         After
     *
     * .   .   .     .   .   .
     *     x
     * . x .   .     .   . x .
     *       1           x
     * .   .   .     .   .   .
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 1;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '1');
     my_edge.x = 0;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);
     my_edge.x = 1;
     my_edge.y = 0;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);

     my_edge.x = 1;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 1;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /** Rule 27
     * Before         After
     *
     * .   . x .     .   .   .
     *       2               |
     * . - .   .     .   .   .
     *                   x
     * .   .   .     .   .   .
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 0;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '2');
     my_edge.x = 0;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);
     my_edge.x = 1;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 1);

     my_edge.x = 0;
     my_edge.y = 2;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);
     my_edge.x = 1;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /** Rule 28
     * Before         After
     *
     * .   .   .     .   . - .
     *       2               |
     * . - .   .     .   .   .
     *     |
     * .   .   .     .   .   .
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 0;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '2');
     my_edge.x = 1;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 1);
     my_edge.x = 1;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 0, 1);

     my_edge.x = 0;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 0;
     my_edge.y = 2;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /** Rule 29
     * Before         After
     *
     * . - .   .     .   .   .
     * | 3
     * .   .   .     .   .   .
     *       1               x
     * .   .   .     .   . x .
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 0;
     my_square.y = 0;
     set_rule_square(my_rules[i], my_square, '3');
     my_square.x = 1;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '1');
     my_edge.x = 0;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 1);
     my_edge.x = 0;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 0, 1);

     my_edge.x = 2;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 1;
     my_edge.y = 2;
     cross_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /** Rule 30
     * Before         After
     *
     * .   .   .     . - .   .
     *   3           |
     * .   .   .     .   .   .
     *       1 x
     * .   . x .     .   .   .
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 0;
     my_square.y = 0;
     set_rule_square(my_rules[i], my_square, '3');
     my_square.x = 1;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '1');
     my_edge.x = 2;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 1, 1);
     my_edge.x = 1;
     my_edge.y = 2;
     cross_rule_edge(my_rules[i], my_edge, 0, 1);

     my_edge.x = 0;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 0;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /**
     * Rule 32
     * Before       After
     * .   .   .    .   . _ .
     *       3              |
     * .   .   .    .   .   .
     *   3          |
     * .   .   .    . _ .   .
     */
     my_rules[i] = rule_init(2, 2);

     my_square.x = 1;
     my_square.y = 0;
     set_rule_square(my_rules[i], my_square, '3');
     my_square.x = 0;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '3');

     my_edge.x = 0;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 2;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 1, 0);
     my_edge.x = 1;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);
     my_edge.x = 0;
     my_edge.y = 2;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(2, 2);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
     /**
     * Rule 33
     * Before       After
     * .   .   .    .   .   .
     *                  x
     * .   .   .    .   .   .
     *   3   3      |   |   |
     * .   .   .    .   .   .
     *                  x
     * .   .   .    .   .   .
     */
     my_rules[i] = rule_init(3, 3);
     my_square.x = 1;
     my_square.y = 0;
     set_rule_square(my_rules[i], my_square, '3');
     my_square.x = 1;
     my_square.y = 1;
     set_rule_square(my_rules[i], my_square, '3');

     my_edge.x = 1;
     my_edge.y = 0;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);
     my_edge.x = 1;
     my_edge.y = 1;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);
     my_edge.x = 1;
     my_edge.y = 2;
     draw_rule_edge(my_rules[i], my_edge, 0, 0);
     my_edge.x = 0;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 0);
     my_edge.x = 2;
     my_edge.y = 1;
     cross_rule_edge(my_rules[i], my_edge, 0, 0);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;

     my_rules[i] = rule_init(3, 3);
     rotate_rule(my_rules[i-1], my_rules[i], 1);

     i++;
/*
  print_grid(my_rules[i-4]->rule_map, my_rules[i-4]->rule_grid, 1);
  print_grid(my_rules[i-4]->res_map, my_rules[i-4]->rule_grid, 1);

  print_grid(my_rules[i-3]->rule_map, my_rules[i-3]->rule_grid, 1);
  print_grid(my_rules[i-3]->res_map, my_rules[i-3]->rule_grid, 1);

  print_grid(my_rules[i-2]->rule_map, my_rules[i-2]->rule_grid, 1);
  print_grid(my_rules[i-2]->res_map, my_rules[i-2]->rule_grid, 1);

  print_grid(my_rules[i-1]->rule_map, my_rules[i-1]->rule_grid, 1);
  print_grid(my_rules[i-1]->res_map, my_rules[i-1]->rule_grid, 1);
*/

  return i;
}

void free_rules(struct sub_grid **my_rules, int nb_rules){
  assert(my_rules);

  for(int i=0; i<nb_rules; i++){
    rule_free(my_rules[i]);
  }

  free(my_rules);
}
