#include "Metodos.h"

int main(void) {
    heap* h = NULL; // Heap inicial
    int capacity = 0; // Capacidade inicial
    int opcao;
    char nomeArquivo[500];

    do {
        printf("\n#### MENU ####\n");
        printf("1 - Inserir por arquivo CSV\n");
        printf("2 - Inserir um único elemento\n");
        printf("3 - Remover aeronave de maior prioridade\n");
        printf("4 - Remover aeronave por identificador\n");
        printf("5 - Visualizar heap Máxima\n");
        printf("6 - Visualizar heap\n");
        printf("7 - Visualizar aeronave por identificador\n");
        printf("8 - Atualizar prioridade\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (h == NULL) {
                    // Inicializa a heap com capacidade inicial de 10
                    h = (heap*)malloc(sizeof(heap));
                    if (h == NULL) {
                        printf("Erro ao alocar memória para a heap.\n");
                        break;
                    }
                    h->capacity = 10; 
                    h->size = 0;
                    h->data = (Aviao*)malloc(h->capacity * sizeof(Aviao));
                    if (h->data == NULL) {
                        printf("Erro ao alocar memória para os dados da heap.\n");
                        free(h);
                        h = NULL;
                        break;
                    }
                }

                printf("Digite o nome do arquivo: ");
                char file[500];
                scanf("%s", file);

                carregar_voos(h, file);

                if (h->size > 0) {
                    printf("Voos carregados com sucesso.\n");
                } else {
                    printf("Nenhum voo foi carregado. Verifique o arquivo.\n");
                }
                break;
            }



            case 2: {
                if (h == NULL) {
                    printf("A heap não foi criada. Por favor, use a opção 1 primeiro.\n");
                    break;
                }

                char identificador[100];
                double combustivel;
                int tipo, emergencia, previsao;

                printf("Digite o identificador: ");
                scanf("%s", identificador);
                printf("Digite o combustível: ");
                scanf("%lf", &combustivel);
                printf("Digite o tipo (0 ou 1): ");
                scanf("%d", &tipo);
                printf("Digite emergência (0 ou 1): ");
                scanf("%d", &emergencia);
                printf("Digite a previsão: ");
                scanf("%d", &previsao);
                int comp = h->size;

                Aviao aeronave = contructorAeronave(identificador, combustivel, tipo, emergencia, previsao);
                insert(h, aeronave);
                int comp_2 = h->size;
                if(comp == comp_2){
                    break;
                }

                printf("Aeronave inserida na heap.\n");
                break;
            }
            case 3: {
                if (h == NULL || h->size == 0) {
                    printf("Heap vazia ou não inicializada.\n");
                } else {
                    printf("Removendo aeronave de maior prioridade...\n");
                    deleteNode(h);
                    printf("Removida com sucesso.\n");
                }
                break;
            }
            case 4: {
                if (h == NULL || h->size == 0) {
                    printf("Heap vazia ou não inicializada.\n");
                    break;
                }

                char identificador[100];
                printf("Digite o identificador da aeronave para remover: ");
                scanf("%s", identificador);

                removeAeronave(h, identificador);
                break;
            }
            case 5: {
                if (h == NULL || h->size == 0) {
                    printf("Heap vazia ou não inicializada.\n");
                    break;
                }

                printf("Heap máxima:\n");
                informacaoAeronave(h->data[0]);
                break;
            }
            case 6: {
                if (h == NULL || h->size == 0) {
                    printf("Heap vazia ou não inicializada.\n");
                    break;
                }

                printf("Visualizando heap\n");
                for (int i = 0; i < h->size; i++) {
                    printf("####POSIÇÃO %d####\n", i);
                    informacaoAeronave(h->data[i]);
                }
                break;
            }
            case 7: {
                if (h == NULL || h->size == 0) {
                    printf("Heap vazia ou não inicializada.\n");
                    break;
                }

                char identificador[100];
                printf("Digite o identificador da aeronave: ");
                scanf("%s", identificador);

                findAeronave(h, identificador);
                break;
            }
            case 8: {
                char identificador[100];
                printf("Digite o identificador da aeronave: ");
                scanf("%s", identificador);
                
                atualizaPrioridade(h, identificador);
                break;
            }
            case 0: {
                printf("Saindo do programa...\n");
                break;
            }
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    // Liberar memória ao finalizar
    if (h != NULL) {
        free(h->data);
        free(h);
    }

    return 0;
}
