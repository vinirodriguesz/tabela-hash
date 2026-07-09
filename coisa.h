#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "object.h"
#include "list.h"

typedef struct Coisa{
	int id;
	char descricao[50];
}Coisa;

void print_coisa(Object propria_caixa, int pos){
	Coisa* c = (Coisa*)propria_caixa->dado;
	printf("  -> [Posicao: %d] Etiqueta: %d | Coisa: %s\n", pos, c->id, c->descricao);
}

void destruir_coisa(Object propria_caixa){
    free(propria_caixa->dado);
    free(propria_caixa);  
}

Object New_Coisa(int id, char *descricao, int tipo){
	Object novo = new_Object();
	Coisa* c = (Coisa*) malloc(sizeof(Coisa));
	c->id = id;
	strcpy(c->descricao, descricao);
	
	novo->dado = c;
	novo->tipo = tipo;
	novo->print = print_coisa;
	novo->destroy = destruir_coisa;
	
	return novo;
}

//Vinicius Dantas Rodrigues (comment just to commit changes)
