#include "../include/detective_quest.h"

// ==================== IMPLEMENTAÇÃO DE TABELA HASH ====================

/**
 * Cria e inicializa uma nova tabela hash
 * Todos os slots começam como NULL
 */
TabelaHash* criarTabelaHash() {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    
    if (tabela == NULL) {
        printf("Erro: Falha na alocação de memória para tabela hash!\n");
        return NULL;
    }
    
    // Inicializa todos os slots como NULL
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabela->itens[i] = NULL;
    }
    
    return tabela;
}

/**
 * Função hash simples que calcula o índice baseado na soma dos caracteres
 * Usa módulo para garantir que o índice esteja dentro do tamanho da tabela
 */
int funcaoHash(const char* pista) {
    int soma = 0;
    int tamanho = strlen(pista);
    
    for (int i = 0; i < tamanho; i++) {
        soma += (unsigned char)pista[i];
    }
    
    return soma % TAMANHO_HASH;
}

/**
 * Insere uma associação pista->suspeito na tabela hash
 * Usa encadeamento para resolver colisões
 */
void inserirNaHash(TabelaHash* tabela, const char* pista, const char* suspeito) {
    if (tabela == NULL) {
        return;
    }
    
    // Calcula o índice usando a função hash
    int indice = funcaoHash(pista);
    
    // Cria um novo item
    ItemHash* novoItem = (ItemHash*)malloc(sizeof(ItemHash));
    if (novoItem == NULL) {
        printf("Erro: Falha na alocação de memória para item hash!\n");
        return;
    }
    
    strcpy(novoItem->pista, pista);
    strcpy(novoItem->suspeito, suspeito);
    
    // Insere no início da lista encadeada (tratamento de colisões)
    novoItem->proximo = tabela->itens[indice];
    tabela->itens[indice] = novoItem;
}

/**
 * Busca o suspeito associado a uma pista na tabela hash
 * Retorna o nome do suspeito ou NULL se não encontrado
 */
char* encontrarSuspeito(TabelaHash* tabela, const char* pista) {
    if (tabela == NULL) {
        return NULL;
    }
    
    // Calcula o índice
    int indice = funcaoHash(pista);
    
    // Percorre a lista encadeada naquele índice
    ItemHash* atual = tabela->itens[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    
    return NULL; // Não encontrado
}

/**
 * Libera toda a memória alocada para a tabela hash
 * Percorre cada lista encadeada e libera todos os itens
 */
void liberarTabelaHash(TabelaHash* tabela) {
    if (tabela == NULL) {
        return;
    }
    
    // Percorre cada slot da tabela
    for (int i = 0; i < TAMANHO_HASH; i++) {
        ItemHash* atual = tabela->itens[i];
        
        // Libera a lista encadeada neste slot
        while (atual != NULL) {
            ItemHash* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    
    // Libera a própria tabela
    free(tabela);
}

/**
 * Conta quantas pistas na árvore apontam para um suspeito específico
 * Usa recursão in-order para percorrer todas as pistas
 */
int contarPistasPorSuspeito(PistaNode* raiz, TabelaHash* tabela, const char* suspeito) {
    if (raiz == NULL) {
        return 0;
    }
    
    int contador = 0;
    
    // Percorre a subárvore esquerda
    contador += contarPistasPorSuspeito(raiz->esquerda, tabela, suspeito);
    
    // Verifica a pista atual
    char* suspeitoEncontrado = encontrarSuspeito(tabela, raiz->pista);
    if (suspeitoEncontrado != NULL && strcmp(suspeitoEncontrado, suspeito) == 0) {
        contador++;
    }
    
    // Percorre a subárvore direita
    contador += contarPistasPorSuspeito(raiz->direita, tabela, suspeito);
    
    return contador;
}

/**
 * Exibe todas as pistas com seus respectivos suspeitos
 * Usa recursão in-order
 */
void exibirPistasComSuspeitos(PistaNode* raiz, TabelaHash* tabela) {
    if (raiz == NULL) {
        return;
    }
    
    exibirPistasComSuspeitos(raiz->esquerda, tabela);
    
    char* suspeito = encontrarSuspeito(tabela, raiz->pista);
    if (suspeito != NULL) {
        printf("  - %s [Suspeito: %s]\n", raiz->pista, suspeito);
    } else {
        printf("  - %s [Suspeito: Desconhecido]\n", raiz->pista);
    }
    
    exibirPistasComSuspeitos(raiz->direita, tabela);
}

/**
 * Conduz a fase final do jogo: acusação e verificação
 * O jogador escolhe um suspeito e o sistema verifica se há pistas suficientes
 */
void verificarSuspeitoFinal(PistaNode* arvore_pistas, TabelaHash* tabela) {
    char suspeitoAcusado[100];
    
    printf("\n\n===========================================\n");
    printf("     HORA DE FAZER SUA ACUSAÇÃO!          \n");
    printf("===========================================\n");
    
    // Exibe todas as pistas com os suspeitos associados
    printf("\nPistas coletadas e suspeitos relacionados:\n");
    exibirPistasComSuspeitos(arvore_pistas, tabela);
    
    printf("\n\nSuspeitos possíveis:\n");
    printf("  - Coronel Mostarda\n");
    printf("  - Senhorita Violeta\n");
    printf("  - Professor Marinho\n");
    printf("  - Senhora Branca\n");
    printf("  - Senhor Marinho\n");
    
    printf("\nQuem você acusa? (digite o nome completo): ");
    scanf(" %[^\n]", suspeitoAcusado);
    
    // Conta quantas pistas apontam para o suspeito acusado
    int numeroDePistas = contarPistasPorSuspeito(arvore_pistas, tabela, suspeitoAcusado);
    
    printf("\n===========================================\n");
    printf("           RESULTADO DA ACUSAÇÃO          \n");
    printf("===========================================\n");
    
    printf("\nVocê acusou: %s\n", suspeitoAcusado);
    printf("Pistas que apontam para este suspeito: %d\n", numeroDePistas);
    
    // Verifica se há pistas suficientes (mínimo 2)
    if (numeroDePistas >= 2) {
        printf("\n✓ CASO RESOLVIDO!\n");
        printf("Há evidências suficientes para acusar %s.\n", suspeitoAcusado);
        printf("Parabéns, Detetive! Você solucionou o mistério da mansão!\n");
    } else {
        printf("\n✗ ACUSAÇÃO INSUFICIENTE!\n");
        printf("Não há pistas suficientes para acusar %s.\n", suspeitoAcusado);
        printf("São necessárias pelo menos 2 pistas apontando para o suspeito.\n");
        printf("O caso permanece sem solução...\n");
    }
}
