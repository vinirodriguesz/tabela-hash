#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int inspetor_da_coisa(Object caixa) {
    Coisa* c = (Coisa*)caixa->dado;
    return c->id;
}

int main() {
    Galpao meu_galpao = monta_galpao(5, inspetor_da_coisa);
    int opcao = 0;
    int id_temp;
    char desc_temp[50];
    while (opcao != 4) {
        printf("1 guardar nova caixa (Cadastrar)\n");
        printf("2 buscar uma caixa\n");
        printf("3 remover uma caixa\n");
        printf("4 sair\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Digite o ID: ");
                scanf("%d", &id_temp);
                printf("Digite a descricao: ");
                scanf(" %[^\n]", desc_temp); 
                Object nova_caixa = New_Coisa(id_temp, desc_temp, 1);
                guarda_galpao(meu_galpao, nova_caixa);
                printf("caixa [%d] guardada na prateleira.\n", id_temp);
                break;
            case 2:
                printf("Qual id voce quer procurar? ");
                scanf("%d", &id_temp);
                Object achado = busca_galpao(meu_galpao, id_temp);
                if (achado != NULL) {
                    printf("caixa encontrada, detalhes da caixa:\n");
                    achado->print(achado, 0);
                }
                break;
            case 3:
                printf("Qual id da caixa que o cliente veio buscar? ");
                scanf("%d", &id_temp);
                remove_galpao(meu_galpao, id_temp);
                break;
            case 4:
                printf("\nFechando\n");
                break;
            default:
                printf("\n opcao invalida\n");
        }
    }

    return 0;
}
