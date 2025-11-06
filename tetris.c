// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5 //numero fixo de peças na fila
#define TAMANHO_FILA 3 //capacidade máxima da pilha de reserva

//Estrutura que representa uma peça
typedef struct {
    char tipo;
    int id;
} Peca;

//Estrutura da fila circular
typedef struct {
    Peca itens[TAMANHO_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

//-------------funções para controle da FILA-------------//

// inicializa a fila
void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

//verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->quantidade == TAMANHO_FILA;
}

//verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

//adiciona uma nova peça ao final da fila
void enqueue(Fila *fila, Peca novaPeca) {
    if (filaCheia(fila)) {
        printf("\n Fila cheia!\n");
        return;
    }

    fila->itens[fila->fim] = novaPeca;
    fila->fim = (fila->fim + 1) % TAMANHO_FILA;
    fila->quantidade++;
}

//remove uma peça do início da fila
Peca dequeue(Fila *fila) {
    Peca pecaRemovida = {' ', -1};

    if (filaVazia(fila)) {
        printf("\nFila vazia!\n");
        return pecaRemovida;
    }

    pecaRemovida = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
    fila->quantidade--;

    return pecaRemovida;
}

//exibe o estado atual da fila
void exibirFila(Fila *fila) {
    printf("\nFila de peças:\n");

    if(filaVazia(fila)) {
        printf("[vazia]\n");
        return;
    }

    int i, index;
    for (i = 0; i <fila->quantidade; i++) {
        index = (fila->inicio + i) % TAMANHO_FILA;
        printf("[%c %d] ", fila->itens[index].tipo, fila->itens[index].id);
    }
    printf("\n");
}

//FUNÇÕES DA PILHA
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAMANHO_PILHA - 1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

void push(Pilha *pilha, Peca nova) {
    if(pilhaCheia(pilha)) {
        printf("\nPilha cheia!\n");
        return;
    }
    pilha->itens[++pilha->topo] = nova;
}

Peca pop(Pilha *pilha) {
    Peca removida = {' ', -1};

    if (pilhaVazia(pilha)) {
        printf("\nPilha vazia!\n");
        return removida;
    }

    removida = pilha->itens[pilha->topo--];
    return removida;
}

void exibirPilha(Pilha *pilha) {
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(pilha)) {
        printf("[vazia]");
        return;
    }

    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%c %d] ", pilha->itens[i].tipo, pilha->itens[i].id);
    }
    printf("\n")
}

// --------Função para gerar uma nova peça aleatória --------//
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4]; //gera um tipo aleatório
    p.id = id;
    return p;
}

//EXIBIÇÃO COMPLETA
void exibirEstado(Fila *fila, Pilha *pilha) {
    printf("\n==================== ESTADO ATUAL ====================\n");
    exibirFila(fila);
    exibirPilha(pilha);
    printf("======================================================\n");
}

//--------Função Principal--------//
int main() {
    Fila fila;
    Pilha pilha;
    int opcao, idAtual = 0;

    srand(time(NULL)); //semente para gerar peças aleatórias
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    //inicializa a fila com 5 peças
    for (int i = 0; i <TAMANHO_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    printf("--------TETRIS STACK - Filha e Pilha de Peças--------\n");

    do {
        exibirEstado(&fila, &pilha);
        
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (remover da fila)\n");
        printf("2 - Reservar peça (mover para pilha)\n");
        printf("3 - Usar peça reservada (remover da pilha)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1)
                    printf("\n➡️  Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
                break;
            }

            case 2: {
                // Reservar peça (move da fila para a pilha)
                if (pilhaCheia(&pilha)) {
                    printf("\n⚠️  Pilha cheia! Não é possível reservar mais.\n");
                } else {
                    Peca reservada = dequeue(&fila);
                    if (reservada.id != -1) {
                        push(&pilha, reservada);
                        printf("\n📦  Peça reservada: [%c %d]\n", reservada.tipo, reservada.id);
                        enqueue(&fila, gerarPeca(idAtual++));
                    }
                }
                break;
            }

            case 3: {
                // Usar peça reservada (remove da pilha)
                Peca usada = pop(&pilha);
                if (usada.id != -1)
                    printf("\n✅  Peça usada da reserva: [%c %d]\n", usada.tipo, usada.id);
                break;
            }

            case 0:
                printf("\nSaindo do jogo... 👋\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


