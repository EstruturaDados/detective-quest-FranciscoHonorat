#include "../include/detective_quest.h"

// ==================== IMPLEMENTAÇÃO DE BST (ÁRVORE DE PISTAS) ====================

/**
 * Insere uma pista na árvore BST de forma ordenada alfabeticamente
 * Usa recursão para encontrar a posição correta
 */
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    // Caso base: posição encontrada para inserir
    if (raiz == NULL) {
        PistaNode* novoNode = (PistaNode*)malloc(sizeof(PistaNode));
        if (novoNode == NULL) {
            printf("Erro: Falha na alocação de memória para pista!\n");
            return NULL;
        }
        
        strcpy(novoNode->pista, pista);
        novoNode->esquerda = NULL;
        novoNode->direita = NULL;
        return novoNode;
    }
    
    // Compara a pista com a raiz atual para decidir o lado
    int comparacao = strcmp(pista, raiz->pista);
    
    if (comparacao < 0) {
        // Pista vem antes alfabeticamente -> vai para a esquerda
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (comparacao > 0) {
        // Pista vem depois alfabeticamente -> vai para a direita
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    // Se comparacao == 0, a pista já existe, não insere duplicata
    
    return raiz;
}

/**
 * Exibe todas as pistas em ordem alfabética (percurso in-order)
 * Usa recursão para percorrer a árvore
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Percurso in-order: esquerda -> raiz -> direita
    exibirPistas(raiz->esquerda);
    printf("  - %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

/**
 * Libera toda a memória alocada para a árvore de pistas
 * Usa recursão pós-ordem
 */
void liberarPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Libera recursivamente as subárvores
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    
    // Libera o nó atual
    free(raiz);
}

/**
 * Explora a mansão coletando pistas (nível aventureiro)
 * Versão expandida que adiciona pistas à BST quando encontradas
 */
void explorarSalasComPistas(Sala* salaAtual, PistaNode** arvore_pistas) {
    char escolha;
    
    while (salaAtual != NULL) {
        // Exibe o nome da sala atual
        printf("\n===========================================\n");
        printf("Você está em: %s\n", salaAtual->nome);
        printf("===========================================\n");
        
        // Verifica se há pista nesta sala
        if (strlen(salaAtual->pista) > 0) {
            printf("\n🔍 PISTA ENCONTRADA: %s\n", salaAtual->pista);
            
            // Adiciona a pista à árvore BST
            *arvore_pistas = inserirPista(*arvore_pistas, salaAtual->pista);
            printf("✓ Pista adicionada ao seu caderno!\n");
        } else {
            printf("\nNenhuma pista encontrada neste cômodo.\n");
        }
        
        // Verifica se há caminhos disponíveis
        int temEsquerda = (salaAtual->esquerda != NULL);
        int temDireita = (salaAtual->direita != NULL);
        
        // Mostra as opções disponíveis
        printf("\nPara onde deseja ir?\n");
        if (temEsquerda) {
            printf("  [e] Esquerda -> %s\n", salaAtual->esquerda->nome);
        }
        if (temDireita) {
            printf("  [d] Direita -> %s\n", salaAtual->direita->nome);
        }
        printf("  [s] Sair e revisar pistas\n");
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
            printf("\nVocê decidiu encerrar a exploração.\n");
            break;
        } else {
            printf("\nOpção inválida! Use 'e', 'd' ou 's'.\n");
        }
    }
    
    // Exibe todas as pistas coletadas em ordem alfabética
    printf("\n===========================================\n");
    printf("       PISTAS COLETADAS (em ordem)        \n");
    printf("===========================================\n");
    
    if (*arvore_pistas != NULL) {
        exibirPistas(*arvore_pistas);
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
}
