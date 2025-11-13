#include "../include/detective_quest.h"

// ==================== IMPLEMENTAÇÃO DE ÁRVORE BINÁRIA (MAPA DA MANSÃO) ====================

/**
 * Cria uma nova sala dinamicamente com nome e pista
 * Aloca memória para um novo nó da árvore que representa um cômodo
 */
Sala* criarSala(const char* nome, const char* pista) {
    // Aloca memória dinamicamente para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("Erro: Falha na alocação de memória para sala!\n");
        return NULL;
    }
    
    // Copia o nome do cômodo
    strcpy(novaSala->nome, nome);
    
    // Copia a pista (pode ser string vazia)
    if (pista != NULL && strlen(pista) > 0) {
        strcpy(novaSala->pista, pista);
    } else {
        strcpy(novaSala->pista, "");
    }
    
    // Inicializa os ponteiros para as salas adjacentes como NULL
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * Permite exploração interativa da mansão (nível novato)
 * O jogador navega pela árvore binária escolhendo esquerda ou direita
 */
void explorarSalas(Sala* salaAtual) {
    char escolha;
    
    while (salaAtual != NULL) {
        // Exibe o nome da sala atual
        printf("\n===========================================\n");
        printf("Você está em: %s\n", salaAtual->nome);
        printf("===========================================\n");
        
        // Verifica se há caminhos disponíveis
        int temEsquerda = (salaAtual->esquerda != NULL);
        int temDireita = (salaAtual->direita != NULL);
        
        // Se não há caminhos, é um cômodo final (folha)
        if (!temEsquerda && !temDireita) {
            printf("\nEste cômodo não possui mais saídas.\n");
            printf("Fim da exploração!\n");
            break;
        }
        
        // Mostra as opções disponíveis
        printf("\nPara onde deseja ir?\n");
        if (temEsquerda) {
            printf("  [e] Esquerda -> %s\n", salaAtual->esquerda->nome);
        }
        if (temDireita) {
            printf("  [d] Direita -> %s\n", salaAtual->direita->nome);
        }
        printf("  [s] Sair da exploração\n");
        printf("\nEscolha: ");
        
        // Lê a escolha do usuário
        scanf(" %c", &escolha);
        
        // Processa a escolha
        if (escolha == 'e' || escolha == 'E') {
            if (temEsquerda) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("\nNão há caminho à esquerda!\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (temDireita) {
                salaAtual = salaAtual->direita;
            } else {
                printf("\nNão há caminho à direita!\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("\nVocê decidiu sair da exploração.\n");
            break;
        } else {
            printf("\nOpção inválida! Use 'e', 'd' ou 's'.\n");
        }
    }
}

/**
 * Libera toda a memória alocada para a árvore de salas
 * Usa recursão para percorrer e liberar todos os nós
 */
void liberarArvore(Sala* sala) {
    if (sala == NULL) {
        return;
    }
    
    // Libera recursivamente as subárvores
    liberarArvore(sala->esquerda);
    liberarArvore(sala->direita);
    
    // Libera o nó atual
    free(sala);
}
