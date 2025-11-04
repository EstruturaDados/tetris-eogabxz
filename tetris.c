// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5 //numero fixo de peças na fila

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

//-------------funções para controle da fila-------------//

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

// --------Função para gerar uma nova peça aleatória --------//
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4]; //gera um tipo aleatório
    p.id = id;
    return p;
}

//--------Função Principal--------//
int main() {
    Fila fila;
    int opcao, idAtual = 0;
    srand(time(NULL)); //semente para gerar peças aleatórias

    inicializarFila(&fila);

    //inicializa a fila com 5 peças
    for (int i = 0; i <TAMANHO_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    printf("--------TETRIS STACK - Simulador de fila de peças--------\n");

    do {
        exibirFila(&fila);
        
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
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
                Peca nova = gerarPeca(idAtual++);
                enqueue(&fila, nova);
                if (!filaCheia(&fila))
                    printf("\n✅ Nova peça inserida: [%c %d]\n", nova.tipo, nova.id);
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


    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


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


