#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tsp.h"

int TSP=0;

struct coord* tsp_init(struct map *my_map, int N)
{

  int **cost_ary = malloc(N*N*sizeof(int*));
  for(int i=0; i<N; i++){
    cost_ary[i] = malloc(N*sizeof(int));
  }

  int *completed = calloc(N,sizeof(int));
  int cost = 0;

  struct coord *chosen_points = choose_points(my_map, N);

  for(int i=0; i<N; i++){
    printf("Random Chosen Point : (%d, %d)\n", chosen_points[i].x, chosen_points[i].y);
  }

  // Distances entre les points

  cost_distance(my_map, chosen_points, cost_ary, N);

  mincost(0, &cost, cost_ary, completed, chosen_points, N);

  return chosen_points;
}

void cost_distance(struct map* my_map, struct coord *chosen_points, int **cost_ary, int N){
  int dist_x = 0;
  int dist_y = 0;
  for(int i=0; i<N; i++){
    for(int j=i+1; j<N; j++){
      dist_x = abs(chosen_points[i].x - chosen_points[j].x);
      dist_y = abs(chosen_points[i].y - chosen_points[j].y);
      cost_ary[i][j] = dist_x + dist_y;
      cost_ary[j][i] = dist_x + dist_y;
    }
  }

}

struct coord random_coords(int min_x, int max_x, int min_y, int max_y){
  struct coord my_coord;
  int xr = (rand() % (max_x + 1 - min_x)) + min_x;
  int yr = (rand() % (max_y + 1 - min_y)) + min_y;
  my_coord.x = xr;
  my_coord.y = yr;

  return my_coord;
}

struct coord *choose_points(struct map *my_map, int N){
  int n = my_map->n;
  int m = my_map->m;

  srand(time(0));

  struct coord *chosen_points = malloc(N*sizeof(struct coord));
  chosen_points[0] = random_coords(0, n/2, 0, m/2);
  chosen_points[1] = random_coords(0, n/2, m/2+1, m);
  chosen_points[2] = random_coords(n/2+1, n, 0, m/2);
  chosen_points[3] = random_coords(n/2+1, n, m/2+1, m);
  printf("x -> [%d, %d], y -> [%d, %d]\n", 0, n/2, 0, m/2);
  printf("x -> [%d, %d], y -> [%d, %d]\n", 0, n/2, m/2+1, m);
  printf("x -> [%d, %d], y -> [%d, %d]\n", n/2+1, n, 0, m/2);
  printf("x -> [%d, %d], y -> [%d, %d]\n", n/2+1, n, m/2+1, m);

  /*
  for(int i=0; i<N; i++){
    //int diff=0;
    //int changed=0;

    //do{
      chosen_points[i] = random_coords(0, n/2, (m/2)*(i%2), (m/2)*((i+1)%2));
    //}while(chosen_points[i].x == 0 || chosen_points[i].x == n || chosen_points[i].y == 0 || chosen_points[i].y == m);

    while(diff<i){
      while((chosen_points[diff].x == chosen_points[i].x) && (chosen_points[diff].y ==  chosen_points[i].y)){
        //do{
          chosen_points[i] = random_coords(n, m);
        //}while(chosen_points[i].x == 0 || chosen_points[i].x == n || chosen_points[i].y == 0 || chosen_points[i].y == m);
        changed = 1;
      }
      if(changed){
        diff = 0;
        changed = 0;
      }
      else{
        diff++;
      }
    }

  }
*/
  return chosen_points;
}

void mincost(int point, int *cost, int **cost_ary, int *completed, struct coord *chosen_points, int N)
{
	int i,npoint;

	completed[point]=1;
  struct coord tmp = chosen_points[point];
  chosen_points[point] = chosen_points[TSP];
  chosen_points[TSP] = tmp;
  TSP++;

	npoint=least(point, cost, cost_ary, completed, N);

	if(npoint==999){
		npoint=0;
		cost+=cost_ary[point][npoint];
		return;
	}

	mincost(npoint, cost, cost_ary, completed, chosen_points, N);
}

int least(int c, int *cost, int **cost_ary, int *completed, int N)
{
	int i,nc=999;
	int min=999,kmin;

	for(i=0;i < N;i++)
	{
		if((cost_ary[c][i]!=0)&&(completed[i]==0))
			if(cost_ary[c][i]+cost_ary[i][c] < min)
			{
				min=cost_ary[i][0]+cost_ary[c][i];
				kmin=cost_ary[c][i];
				nc=i;
			}
	}

	if(min!=999)
		cost+=kmin;

	return nc;
}
