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

void copiarString(char *destino, char *origem, int limite) {
    int i = 0;

    while (origem[i] != '\0' && i < limite - 1) {
        destino[i] = origem[i];
        i++;
    }

    destino[i] = '\0';
}

void inserirFim(No **head, int valor) {
    No *novo = (No*)malloc(sizeof(No));
    No *atual;

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    novo->valor = valor;
    novo->prox = NULL;

    if (*head == NULL) {
        *head = novo;
        return;
    }

    atual = *head;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = novo;
}

void inserirPosicao(No **head, int valor, int posicao) {
    No *novo;
    No *atual;
    int i;

    if (posicao < 0) {
        printf("Erro: posicao invalida.\n");
        return;
    }

    novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    novo->valor = valor;

    if (posicao == 0) {
        novo->prox = *head;
        *head = novo;
        return;
    }

    atual = *head;
    for (i = 0; atual != NULL && i < posicao - 1; i++) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Erro: posicao invalida.\n");
        free(novo);
        return;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

int buscarValor(No *head, int valor) {
    int posicao = 0;

    while (head != NULL) {
        if (head->valor == valor) {
            return posicao;
        }

        head = head->prox;
        posicao++;
    }

    return -1;
}

void inverterLista(No **head) {
    No *anterior = NULL;
    No *atual = *head;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    *head = anterior;
}

void dividirLista(No *head, No **lista1, No **lista2) {
    No *lento;
    No *rapido;

    if (head == NULL) {
        *lista1 = NULL;
        *lista2 = NULL;
        return;
    }

    lento = head;
    rapido = head->prox;

    while (rapido != NULL && rapido->prox != NULL) {
        lento = lento->prox;
        rapido = rapido->prox->prox;
    }

    *lista1 = head;
    *lista2 = lento->prox;
    lento->prox = NULL;
}

void exibirLista(No *head) {
    while (head != NULL) {
        printf("%d -> ", head->valor);
        head = head->prox;
    }

    printf("NULL\n");
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
    NoMusica *ultimo;

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    copiarString(novo->musica, nome, 100);

    if (*head == NULL) {
        novo->prox = novo;
        novo->ant = novo;
        *head = novo;
        return;
    }

    ultimo = (*head)->ant;
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
    NoMusica *atual;

    if (head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    atual = head;
    do {
        printf("[%s] <-> ", atual->musica);
        atual = atual->prox;
    } while (atual != head);

    printf("(volta ao inicio)\n");
}

int totalMusicas(NoMusica *head) {
    NoMusica *atual;
    int total = 0;

    if (head == NULL) {
        return 0;
    }

    atual = head;
    do {
        total++;
        atual = atual->prox;
    } while (atual != head);

    return total;
}

void tocarPlaylistUmaVez(NoMusica *head) {
    NoMusica *atual = head;
    int i;
    int total = totalMusicas(head);

    for (i = 0; i < total; i++) {
        printf("Tocando: %s\n", atual->musica);
        atual = atual->prox;
    }
}

void liberarPlaylist(NoMusica **head) {
    NoMusica *atual;
    NoMusica *proximo;
    NoMusica *ultimo;

    if (*head == NULL) {
        return;
    }

    atual = *head;
    ultimo = (*head)->ant;
    ultimo->prox = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    *head = NULL;
}

int main() {
    No *lista = NULL;
    No *lista1 = NULL;
    No *lista2 = NULL;
    NoMusica *playlist = NULL;
    NoMusica *atual = NULL;

    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);
    printf("Lista original: ");
    exibirLista(lista);

    inserirPosicao(&lista, 99, 1);
    printf("Apos inserir 99 na posicao 1: ");
    exibirLista(lista);

    printf("Posicao do valor 20: %d\n", buscarValor(lista, 20));

    inverterLista(&lista);
    printf("Lista invertida: ");
    exibirLista(lista);

    inserirFim(&lista, 40);
    inserirFim(&lista, 50);
    dividirLista(lista, &lista1, &lista2);
    printf("Lista 1: ");
    exibirLista(lista1);
    printf("Lista 2: ");
    exibirLista(lista2);

    adicionarMusica(&playlist, "Rock");
    adicionarMusica(&playlist, "Jazz");
    adicionarMusica(&playlist, "Pop");
    atual = playlist;

    printf("\nPlaylist: ");
    exibirPlaylist(playlist);
    printf("Total de musicas: %d\n", totalMusicas(playlist));

    printf("Atual: %s\n", atual->musica);
    proximaMusica(&atual);
    printf("Proxima: %s\n", atual->musica);
    musicaAnterior(&atual);
    printf("Anterior: %s\n", atual->musica);

    tocarPlaylistUmaVez(playlist);

    liberarLista(lista1);
    liberarLista(lista2);
    liberarPlaylist(&playlist);

    return 0;
}
