#include <stdio.h>
#include <stdlib.h>

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
struct coord *choose_points(struct map *my_map, int N){
  int n = my_map->n;
  int m = my_map->m;

  struct coord *chosen_points = malloc(N*sizeof(struct coord));
  for(int i=0; i<N; i++){
    int diff=0;
    int changed=0;
    chosen_points[i].x = rand() % n;
    chosen_points[i].y = rand() % m;
    while(diff<i){
      while((chosen_points[diff].x == chosen_points[i].x) && (chosen_points[diff].y ==  chosen_points[i].y)){
        chosen_points[i].x = rand() % n;
        chosen_points[i].y = rand() % m;
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
