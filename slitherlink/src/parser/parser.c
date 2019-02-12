#include "parser.h"


int main(int argc, char *argv[]){

  enum q_state state = Q0;
  FILE* file = NULL;
  file = fopen("../test/parser_test.txt", "r");
  if (file != NULL)
    {
        file_parse(file,state);
        printf("ficher ouvert \n");
        fclose(file);
    }
  else
        printf("Impossible d'ouvrir le fichier\n");

  return 0;
}


void file_parse(FILE* file, enum q_state state){

  int caractere = 0;
  int my_m = 0, my_n = 0;

  while(state != Q_OUT && state != Q_ERR && caractere != EOF){
    caractere = fgetc(file);

    switch (caractere) {
      case '#':
        state = Q_IGN;
        do{
          caractere = fgetc(file);
        }while(caractere != '\n');
      break;

      case 1:
        state = Q1;
        while(caractere != '\n'){
          if(caractere != 0 && caractere != 1 && caractere != 2 && caractere != 3 && caractere != '_'){
            state = Q_ERR;
            break;
          }
          ++my_m;
          caractere = fgetc(file);
        }
        // #ifndef m
        // //m = my_m;
        // #define m
        // #endif
        //comparer my_m avec m de la grille
        // si my_m != m alors state = Q_ERR
      break;

      case 2:
      state = Q1;
      while(caractere != '\n'){
        if(caractere != 0 && caractere != 1 && caractere != 2 && caractere != 3 && caractere != '_'){
          state = Q_ERR;
          break;
        }
        ++my_m;
        caractere = fgetc(file);
      }
      break;

      case 3:
      state = Q1;
      while(caractere != '\n'){
        if(caractere != 0 && caractere != 1 && caractere != 2 && caractere != 3 && caractere != '_'){
          state = Q_ERR;
          break;
        }
        ++my_m;
        caractere = fgetc(file);
      }
      break;

      case '_':
      state = Q1;
      while(caractere != '\n'){
        if(caractere != 0 && caractere != 1 && caractere != 2 && caractere != 3 && caractere != '_'){
          state = Q_ERR;
          break;
        }
        ++my_m;
        caractere = fgetc(file);
      }
      break;
    }
  }
}
