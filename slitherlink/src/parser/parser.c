#include "parser.h"

struct grid* parse(){

  enum q_state state = Q0;
  int n = 0, m = 0;

  FILE *file = fopen("src/test/slithers/slither_lvl112.txt", "r");

  if (file != NULL)
    {
        matrix_size(file,&n,&m);

        struct grid* my_grid = grid_init(n,m);
        file_parse(file,&state,my_grid,n,m);

        if(state == Q_ERR)
          printf("Matrix filling fail\n");
        else if (state == Q0 && n == 0 && m == 0){
          printf("Empty matrix or contains only comments\n");
              }
        fclose(file);
        return my_grid;
    }
  else
        printf("Impossible to open the file\n");

  return NULL;
}

void matrix_size(FILE* file, int* n, int* m){

  int caractere;
  while (caractere != EOF) {
    caractere = fgetc(file);
    if (caractere != '0' && caractere != '1' && caractere != '2' && caractere != '3' && caractere != '_' && caractere != EOF){
      do{
        caractere = fgetc(file);
      }while(caractere != '\n');
      caractere = fgetc(file);
    }

     if (caractere == '0' || caractere == '1' || caractere == '2' || caractere == '3' || caractere == '_'){
       while(caractere != '\n'){
         if (caractere != ' ')
            *n += 1;
         caractere = fgetc(file);
       }
       *m += 1;
       do{
         caractere = fgetc(file);
         if (caractere != '0' && caractere != '1' && caractere != '2' && caractere != '3' && caractere != '_' && caractere != EOF){
           do{
             caractere = fgetc(file);
           }while(caractere != '\n');

           caractere = fgetc(file);
         }

         if (caractere == '0' || caractere == '1' || caractere == '2' || caractere == '3' || caractere == '_' || caractere == ' '){
           do{
             caractere = fgetc(file);
           }while(caractere != '\n');

            *m += 1;
         }
       }while(caractere != EOF);
     }
    }
    rewind(file);
  }

void file_parse(FILE* file, enum q_state *state, struct grid* my_grid, int n, int m){

  int caractere = 0;
  int my_n = 0, my_m = 0;
  while(*state != Q_OUT && *state != Q_ERR && caractere != EOF){
    caractere = fgetc(file);

    switch (caractere) {
      case '#':
        *state = Q_IGN;
        do{
          caractere = fgetc(file);
        }while(caractere != '\n');
        *state = Q0;
      break;

      case '0':
        fill_matrix(file,state,&caractere,my_grid,&my_n,&my_m,n,m);
      break;

      case '1':
        fill_matrix(file,state,&caractere,my_grid,&my_n,&my_m,n,m);
      break;

      case '2':
        fill_matrix(file,state,&caractere,my_grid,&my_n,&my_m,n,m);
      break;

      case '3':
        fill_matrix(file,state,&caractere,my_grid,&my_n,&my_m,n,m);
      break;

      case '_':
        fill_matrix(file,state,&caractere,my_grid,&my_n,&my_m,n,m);
      break;

      case EOF:
      break;

      default:
      *state = Q_ERR;
      break;
    }
  }
  if (my_m != m && *state != Q0){
    *state = Q_ERR;
  }
  if(*state != Q_ERR && *state != Q0){
    *state = Q_OUT;
  }
}

void fill_matrix(FILE* file, enum q_state *state, int *caractere, struct grid* my_grid, int *my_n, int *my_m, int n, int m){
  *state = Q1;
  while(*caractere != '\n'){
    if(*caractere != '0' && *caractere != '1' && *caractere != '2' && *caractere != '3' && *caractere != '_' && *caractere != ' '){
      *state = Q_ERR;
      break;
    }
    if(*caractere == '0' || *caractere == '1' || *caractere == '2' || *caractere == '3' || *caractere == '_'){
      if(*caractere == '_'){
        my_grid->squares[*my_m][*my_n] = 'N';
      }
      else{
        my_grid->squares[*my_m][*my_n] = *caractere;
      }
      *my_n += 1;
    }
    *caractere = fgetc(file);
    if (*caractere == '#'){
      *state = Q_IGN;
      do{
        *caractere = fgetc(file);
      }while(*caractere != '\n');
      *state = Q0;
    }
  }
  if(*my_n != n){
    *state = Q_ERR;
  }
  *my_n = 0;
  *my_m += 1;
}
