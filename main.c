#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
//created by Vini Rodriguesz
int inspetor_da_coisa(Object caixa){
	Coisa* c = (Coisa*)caixa->dado;
	return c->id;
}

int main(){
	Galpao meu_galpao = monta_galpao(5, inspetor_da_coisa);
	int opcao = 0;
	int id_temp;
	char desc_temp[50];
	
	while(opcao != 6) {
		printf("\n1 guardar nova caixa\n");
		printf("2 buscar uma caixa\n");
		printf("3 remover uma caixa\n");
		printf("4 imprimir galpao\n");
		printf("5 limpar galpao\n");
		printf("6 sair\n");
		printf("opcao: ");
		scanf("%d", &opcao);
		
		switch(opcao) {
			case 1:
				printf("Digite o ID: ");
				scanf("%d", &id_temp);
				printf("Digite a descricao: ");
				scanf(" %[^\n]", desc_temp); 
				Object nova_caixa = New_Coisa(id_temp, desc_temp, 1);
				guarda_galpao(meu_galpao, nova_caixa);
				printf("caixa [%d] guardada.\n", id_temp);
				break;
			case 2:
				printf("Qual id voce quer procurar? ");
				scanf("%d", &id_temp);
				Object achado = busca_galpao(meu_galpao, id_temp);
				if(achado != NULL) {
					printf("encontrado:\n");
					int numero_da_prateleira = (id_temp % 5);
					achado->print(achado, numero_da_prateleira);
				}
				break;
			case 3:
				printf("Qual id remover? ");
				scanf("%d", &id_temp);
				remove_galpao(meu_galpao, id_temp);
				break;
			case 4:
				imprime_galpao(meu_galpao);
				break;
			case 5:
				limpa_galpao(meu_galpao);
				break;
			case 6:
				printf("\nFechando\n");
				break;
			default:
				printf("\nopcao invalida\n");
		}
	}

	destroi_galpao(meu_galpao);

	return 0;
}
