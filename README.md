# Gerenciador de Inteiros e Playlist em C

Este projeto implementa exercícios de listas encadeadas em linguagem C.

O código possui duas partes principais:

1. Uma lista simplesmente encadeada de inteiros.
2. Uma playlist de músicas usando lista circular duplamente encadeada.

## Requisitos Atendidos

### Parte 1: Inserção em Posição Específica

Função implementada:

```c
void inserirPosicao(No **head, int valor, int posicao);
```

- A posição começa em `0`.
- Funciona com lista vazia, inserção no início, meio e fim.
- Exibe erro quando a posição é inválida.

### Parte 2: Busca por Valor

Função implementada:

```c
int buscarValor(No *head, int valor);
```

- Retorna a posição da primeira ocorrência do valor.
- Retorna `-1` caso o valor não seja encontrado.
- Não utiliza vetor auxiliar.

### Parte 3: Inverter Lista

Função implementada:

```c
void inverterLista(No **head);
```

- Inverte a lista usando apenas ponteiros.
- Não cria uma nova lista.
- Não utiliza vetor auxiliar.

### Parte 4: Dividir Lista em Duas

Função implementada:

```c
void dividirLista(No *head, No **lista1, No **lista2);
```

- Utiliza a técnica de ponteiro rápido e ponteiro lento.
- Não conta os elementos previamente.
- Se a quantidade de elementos for ímpar, a primeira lista recebe um elemento a mais.

### Parte 5: Playlist Circular Duplamente Encadeada

Estrutura usada:

```c
typedef struct NoMusica {
    char musica[100];
    struct NoMusica *prox;
    struct NoMusica *ant;
} NoMusica;
```

Funções implementadas:

```c
void adicionarMusica(NoMusica **head, char *nome);
void proximaMusica(NoMusica **atual);
void musicaAnterior(NoMusica **atual);
void exibirPlaylist(NoMusica *head);
int totalMusicas(NoMusica *head);
```

Também foi implementada a função:

```c
void tocarPlaylistUmaVez(NoMusica *head);
```

Ela percorre a playlist apenas uma vez, usando o total de músicas como controle para evitar loop infinito.
