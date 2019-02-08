#include <stdlib.h>
#include <stdbool.h>
typedef struct block
{
	int size;
	void *data;
    bool frozen;
    struct block *block_next;
    struct block *block_prev;
}block;

//crée un block avec en param: list: 1er élement de la liste chainé ; type de la variable à save
block * createBlock(block * list,void * type){
	block * new= malloc(sizeof(block));
	if(new != NULL){
		new->size=sizeof(type);
		new->data=NULL;//TODO
		new->frozen= false;
		new->block_next=list;
		new->block_prev=NULL;
	}
	if(list != NULL){
		list->block_prev = new;
	}
	return list;
}

//free un block 
void freeBlock(block * list){
	if(list!=NULL){
		if(list->block_prev != NULL){
			list->block_prev->block_next = list->block_next;
		}
		if(list->block_next != NULL){
			list->block_next->block_prev = list->block_prev;
		}
		free(list);
	}
}

//libére un block pour permettre une réécriture
void unfrozenblock(block *list){
	if(list!=NULL){
		list->frozen=true;
	}
}

//cherche espacelibre et sinon crée un nouvveau block avec la taille correspondant
block* write(block *list,void *type){
	if(list != NULL){
		//parcour liste chainée
		while(list->block_next !=NULL)
		{
			if(list->frozen==true && list->size>=sizeof(type)){
				list->frozen=false;
				list->data=NULL;//TODO
				return (list);
			}
			list=list->block_next;
		}
		//si dernier elem
		if(list->frozen==true && list->size>=sizeof(type)){
				list->frozen=false;
				list->data=NULL;//TODO.
				return (list);
		}
		else{
			return(createBlock(list,type));
		}
	}
	return NULL;
}