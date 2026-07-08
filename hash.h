#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coisa.h"

typedef struct _Galpao{
	int capacidade;
	List* prateleiras;
	int (*ler_etiqueta)(Object);
}_Galpao;

typedef _Galpao* Galpao;

Galpao monta_galpao(int capacidade, int (*func_espia)(Object)){
	Galpao g = malloc(sizeof(_Galpao));
	g->capacidade = capacidade;
	g->ler_etiqueta = func_espia;
	g->prateleiras = malloc(capacidade * sizeof(List));
	
	for (int i = 0; i < capacidade; i++){
		g->prateleiras[i] = new_List();
	}
	
	return g;	
}

void guarda_galpao(Galpao g, Object nova_caixa) {
	int idcaixa = g->ler_etiqueta(nova_caixa);
	int indice = (idcaixa % g->capacidade);
	List prateleira_certa = g->prateleiras[indice];

	prateleira_certa->enqueue(prateleira_certa, nova_caixa);
}

Object busca_galpao(Galpao g, int id_buscado) {
	int indice = (id_buscado % g->capacidade);
	List prateleira_certa = g->prateleiras[indice];
	Object detetive = prateleira_certa->inicio;

	while (detetive != NULL) {
		int id_lido = g->ler_etiqueta(detetive);
		if (id_lido == id_buscado) {
			return detetive;
		} else {
			detetive = detetive->proximo; 
		}
	}
	printf("A caixa não existe!!!\n");
	return NULL;
}

void remove_galpao(Galpao g, int id_remover) {
	int indice = id_remover % g->capacidade;
	List prateleira_certa = g->prateleiras[indice];
	Object detetive = prateleira_certa->inicio;
	int pos = 0;

	while (detetive != NULL) {
		int id_lido = g->ler_etiqueta(detetive);
		if (id_lido == id_remover) {
			prateleira_certa->del(prateleira_certa, pos);
			printf("A caixa %d foi removida do galpao com sucesso!\n", id_remover);
			return;
		}
		detetive = detetive->proximo;
		pos++;
	}
	printf("Erro: A caixa %d nao esta no galpao para ser removida.\n", id_remover);
}

void imprime_galpao(Galpao g) {
	for(int i=0; i < g->capacidade; i++) {
		printf("prateleira %d:\n", i);
		List prateleira_certa = g->prateleiras[i];
		Object detetive = prateleira_certa->inicio;
		if(detetive == NULL){
			printf("	vazia\n");
		}
		while(detetive != NULL) {
			detetive->print(detetive, i); 
			detetive = detetive->proximo;
		}
	}
	printf("\n");
}

void limpa_galpao(Galpao g) {
	for(int i=0; i < g->capacidade; i++) {
		List prateleira_certa = g->prateleiras[i];
		prateleira_certa->clear(prateleira_certa);
	}
}

void destroi_galpao(Galpao g) {
	limpa_galpao(g);
	for(int i=0; i < g->capacidade; i++) {
		free(g->prateleiras[i]);
	}
	free(g->prateleiras);
	free(g);
}
