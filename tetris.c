#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACIDADE_FILA 5

typedef struct
{
    char nome;
    int id;
} Peca;

typedef struct
{
    Peca pecas[CAPACIDADE_FILA];
    int frente;
    int tras;
    int tamanho;
} FilaPecas;

int proximoId = 0;

void inicializarFila(FilaPecas *fila)
{
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

int filaVazia(FilaPecas *fila)
{
    return fila->tamanho == 0;
}

int filaCheia(FilaPecas *fila)
{
    return fila->tamanho == CAPACIDADE_FILA;
}

Peca gerarPeca()
{
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    novaPeca.nome = tipos[rand() % 4];
    novaPeca.id = proximoId++;
    return novaPeca;
}

int enqueue(FilaPecas *fila, Peca peca)
{
    if (filaCheia(fila))
    {
        return 0;
    }

    fila->tras = (fila->tras + 1) % CAPACIDADE_FILA;
    fila->pecas[fila->tras] = peca;
    fila->tamanho++;
    return 1;
}

int dequeue(FilaPecas *fila, Peca *pecaRemovida)
{
    if (filaVazia(fila))
    {
        return 0;
    }

    *pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % CAPACIDADE_FILA;
    fila->tamanho--;
    return 1;
}

void mostrarFila(FilaPecas *fila)
{
    printf("\nFila de pecas\n");

    if (filaVazia(fila))
    {
        printf("[Vazia]\n");
        return;
    }

    int i;
    int indice = fila->frente;
    for (i = 0; i < fila->tamanho; i++)
    {
        printf("[%c %d] ", fila->pecas[indice].nome, fila->pecas[indice].id);
        indice = (indice + 1) % CAPACIDADE_FILA;
    }
    printf("\n");
}

void mostrarMenu()
{
    printf("\n=== TETRIS STACK ===\n");
    printf("1 - Jogar peca (dequeue)\n");
    printf("2 - Inserir nova peca (enqueue)\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    FilaPecas fila;
    int opcao;
    Peca pecaRemovida;

    srand(time(NULL));

    inicializarFila(&fila);

    for (int i = 0; i < CAPACIDADE_FILA; i++)
    {
        enqueue(&fila, gerarPeca());
    }

    do
    {
        mostrarFila(&fila);
        mostrarMenu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (dequeue(&fila, &pecaRemovida))
            {
                printf("\nPeca jogada: [%c %d]\n", pecaRemovida.nome, pecaRemovida.id);
                enqueue(&fila, gerarPeca());
                printf("Nova peca adicionada automaticamente.\n");
            }
            else
            {
                printf("\nErro: Fila vazia!\n");
            }
            break;

        case 2:
            if (enqueue(&fila, gerarPeca()))
            {
                printf("\nNova peca inserida com sucesso!\n");
            }
            else
            {
                printf("\nErro: Fila cheia!\n");
            }
            break;

        case 0:
            printf("\nEncerrando o jogo. Ate logo!\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
