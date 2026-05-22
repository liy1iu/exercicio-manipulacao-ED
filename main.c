#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct NoMusica {
    char musica[100];
    struct NoMusica *prox;
    struct NoMusica *ant;
} NoMusica;

int stringLength(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void stringCopy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirLista(No *head) {
    No *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->valor);
        temp = temp->prox;
    }
    printf("NULL\n");
}

void inserirFim(No **head, int valor) {
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    
    if (*head == NULL) {
        *head = novo;
        return;
    }
    
    No *temp = *head;
    while (temp->prox != NULL) {
        temp = temp->prox;
    }
    temp->prox = novo;
}

void inserirPosicao(No **head, int valor, int posicao) {
    if (posicao < 0) {
        printf("Erro: Posição inválida!\n");
        return;
    }
    
    No *novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    
    if (posicao == 0) {
        novo->prox = *head;
        *head = novo;
        return;
    }
    
    No *temp = *head;
    int i = 0;
    
    while (temp != NULL && i < posicao - 1) {
        temp = temp->prox;
        i++;
    }
    
    if (temp == NULL) {
        printf("Erro: Posição inválida!\n");
        free(novo);
        return;
    }
    
    novo->prox = temp->prox;
    temp->prox = novo;
}

int buscarValor(No *head, int valor) {
    No *temp = head;
    int posicao = 0;
    
    while (temp != NULL) {
        if (temp->valor == valor) {
            return posicao;
        }
        temp = temp->prox;
        posicao++;
    }
    
    return -1;
}

void inverterLista(No **head) {
    No *anterior = NULL;
    No *atual = *head;
    No *proximo = NULL;
    
    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }
    
    *head = anterior;
}

void dividirLista(No *head, No **lista1, No **lista2) {
    if (head == NULL) {
        *lista1 = NULL;
        *lista2 = NULL;
        return;
    }
    
    No *lento = head;
    No *rapido = head;
    No *anterior = NULL;
    
    while (rapido != NULL && rapido->prox != NULL) {
        anterior = lento;
        lento = lento->prox;
        rapido = rapido->prox->prox;
    }
    
    *lista1 = head;
    *lista2 = lento;
    
    if (anterior != NULL) {
        anterior->prox = NULL;
    }
}

void liberarLista(No *head) {
    No *temp;
    while (head != NULL) {
        temp = head;
        head = head->prox;
        free(temp);
    }
}

void adicionarMusica(NoMusica **head, char *nome) {
    NoMusica *novo = (NoMusica*)malloc(sizeof(NoMusica));
    stringCopy(novo->musica, nome);
    
    if (*head == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        *head = novo;
        return;
    }
    
    NoMusica *ultimo = (*head)->ant;
    
    novo->prox = *head;
    novo->ant = ultimo;
    ultimo->prox = novo;
    (*head)->ant = novo;
}

void proximaMusica(NoMusica **atual) {
    if (*atual != NULL) {
        *atual = (*atual)->prox;
    }
}

void musicaAnterior(NoMusica **atual) {
    if (*atual != NULL) {
        *atual = (*atual)->ant;
    }
}

void exibirPlaylist(NoMusica *head) {
    if (head == NULL) {
        printf("Playlist vazia!\n");
        return;
    }
    
    NoMusica *temp = head;
    printf("Playlist: ");
    do {
        printf("[%s] <-> ", temp->musica);
        temp = temp->prox;
    } while (temp != head);
    printf("(circular)\n");
}

int totalMusicas(NoMusica *head) {
    if (head == NULL) {
        return 0;
    }
    
    int count = 1;
    NoMusica *temp = head->prox;
    
    while (temp != head) {
        count++;
        temp = temp->prox;
    }
    
    return count;
}

void liberarPlaylist(NoMusica **head) {
    if (*head == NULL) {
        return;
    }
    
    NoMusica *atual = *head;
    NoMusica *proximo;
    NoMusica *primeiro = *head;
    
    do {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    } while (atual != primeiro);
    
    *head = NULL;
}

void menuPrincipal() {
    printf("\n========================================\n");
    printf("         MENU PRINCIPAL\n");
    printf("========================================\n");
    printf("1. Testar Inserção em Posição\n");
    printf("2. Testar Busca por Valor\n");
    printf("3. Testar Inversão de Lista\n");
    printf("4. Testar Divisão de Lista\n");
    printf("5. Gerenciar Playlist de Músicas\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha: ");
}

void testarInsercao() {
    No *lista = NULL;
    
    printf("\n========================================\n");
    printf("    TESTE: INSERÇÃO EM POSIÇÃO\n");
    printf("========================================\n");
    
    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);
    
    printf("\nLista original: ");
    exibirLista(lista);
    
    printf("\nInserindo 99 na posição 1...\n");
    inserirPosicao(&lista, 99, 1);
    printf("Lista após inserção: ");
    exibirLista(lista);
    
    printf("\nInserindo 5 na posição 0 (início)...\n");
    inserirPosicao(&lista, 5, 0);
    printf("Lista após inserção: ");
    exibirLista(lista);
    
    printf("\nTentando inserir na posição 10 (inválida)...\n");
    inserirPosicao(&lista, 100, 10);
    
    liberarLista(lista);
    pausar();
}

void testarBusca() {
    No *lista = NULL;
    
    printf("\n========================================\n");
    printf("       TESTE: BUSCA POR VALOR\n");
    printf("========================================\n");
    
    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);
    inserirFim(&lista, 40);
    
    printf("\nLista: ");
    exibirLista(lista);
    
    printf("\nBuscando valor 20...\n");
    int valor = 20;
    int pos = buscarValor(lista, valor);
    if (pos != -1) {
        printf("Valor %d encontrado na posição %d\n", valor, pos);
    } else {
        printf("Valor %d não encontrado\n", valor);
    }
    
    printf("\nBuscando valor 99...\n");
    valor = 99;
    pos = buscarValor(lista, valor);
    if (pos != -1) {
        printf("Valor %d encontrado na posição %d\n", valor, pos);
    } else {
        printf("Valor %d não encontrado\n", valor);
    }
    
    printf("\nBuscando valor 10...\n");
    valor = 10;
    pos = buscarValor(lista, valor);
    if (pos != -1) {
        printf("Valor %d encontrado na posição %d\n", valor, pos);
    } else {
        printf("Valor %d não encontrado\n", valor);
    }
    
    liberarLista(lista);
    pausar();
}

void testarInversao() {
    No *lista = NULL;
    
    printf("\n========================================\n");
    printf("      TESTE: INVERSÃO DE LISTA\n");
    printf("========================================\n");
    
    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);
    inserirFim(&lista, 40);
    
    printf("\nLista original: ");
    exibirLista(lista);
    
    printf("\nInvertendo lista...\n");
    inverterLista(&lista);
    
    printf("Lista invertida: ");
    exibirLista(lista);
    
    liberarLista(lista);
    pausar();
}

void testarDivisao() {
    No *lista = NULL;
    No *lista1 = NULL;
    No *lista2 = NULL;
    
    printf("\n========================================\n");
    printf("      TESTE: DIVISÃO DE LISTA\n");
    printf("========================================\n");
    
    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);
    inserirFim(&lista, 40);
    inserirFim(&lista, 50);
    
    printf("\nLista original (5 elementos - ímpar): ");
    exibirLista(lista);
    
    dividirLista(lista, &lista1, &lista2);
    
    printf("\nApós divisão:\n");
    printf("Lista 1 (primeira metade): ");
    exibirLista(lista1);
    
    printf("Lista 2 (segunda metade): ");
    exibirLista(lista2);
    
    liberarLista(lista1);
    liberarLista(lista2);
    
    printf("\n\nTestando com lista par (4 elementos)...\n");
    lista = NULL;
    inserirFim(&lista, 100);
    inserirFim(&lista, 200);
    inserirFim(&lista, 300);
    inserirFim(&lista, 400);
    
    printf("Lista original: ");
    exibirLista(lista);
    
    dividirLista(lista, &lista1, &lista2);
    
    printf("\nApós divisão:\n");
    printf("Lista 1: ");
    exibirLista(lista1);
    
    printf("Lista 2: ");
    exibirLista(lista2);
    
    liberarLista(lista1);
    liberarLista(lista2);
    
    pausar();
}

void removerNovaLinha(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

void gerenciarPlaylist() {
    NoMusica *playlist = NULL;
    NoMusica *atual = NULL;
    int opcao;
    char musica[100];
    
    do {
        printf("\n========================================\n");
        printf("       PLAYLIST DE MÚSICAS\n");
        printf("========================================\n");
        printf("1. Adicionar música\n");
        printf("2. Próxima música\n");
        printf("3. Música anterior\n");
        printf("4. Exibir playlist completa\n");
        printf("5. Total de músicas\n");
        printf("6. Mostrar música atual\n");
        printf("0. Voltar ao menu principal\n");
        printf("========================================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                printf("\nNome da música: ");
                fgets(musica, 100, stdin);
                removerNovaLinha(musica);
                adicionarMusica(&playlist, musica);
                if (atual == NULL) {
                    atual = playlist;
                }
                printf("✓ Música '%s' adicionada!\n", musica);
                pausar();
                break;
                
            case 2:
                if (playlist != NULL) {
                    proximaMusica(&atual);
                    printf("\n♪ Tocando agora: %s\n", atual->musica);
                } else {
                    printf("\nPlaylist vazia!\n");
                }
                pausar();
                break;
                
            case 3:
                if (playlist != NULL) {
                    musicaAnterior(&atual);
                    printf("\n♪ Tocando agora: %s\n", atual->musica);
                } else {
                    printf("\nPlaylist vazia!\n");
                }
                pausar();
                break;
                
            case 4:
                printf("\n");
                exibirPlaylist(playlist);
                pausar();
                break;
                
            case 5:
                printf("\n📊 Total de músicas: %d\n", totalMusicas(playlist));
                pausar();
                break;
                
            case 6:
                if (atual != NULL) {
                    printf("\n♪ Música atual: %s\n", atual->musica);
                } else {
                    printf("\nNenhuma música selecionada!\n");
                }
                pausar();
                break;
                
            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;
                
            default:
                printf("\nOpção inválida!\n");
                pausar();
        }
    } while (opcao != 0);
    
    liberarPlaylist(&playlist);
}

int main() {
    int opcao;
    
    do {
        menuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                testarInsercao();
                break;
            case 2:
                testarBusca();
                break;
            case 3:
                testarInversao();
                break;
            case 4:
                testarDivisao();
                break;
            case 5:
                gerenciarPlaylist();
                break;
            case 0:
                printf("\n✓ Encerrando programa...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
                pausar();
        }
    } while (opcao != 0);
    
    return 0;
}