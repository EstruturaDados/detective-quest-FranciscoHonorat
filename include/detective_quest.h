#ifndef DETECTIVE_QUEST_H
#define DETECTIVE_QUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 20

// Estrutura para representar um cômodo da mansão (nó da árvore binária)
typedef struct Sala {
    char nome[100];                // Nome do cômodo
    char pista[200];              // Pista encontrada neste cômodo (se houver)
    struct Sala* esquerda;        // Ponteiro para a sala à esquerda
    struct Sala* direita;         // Ponteiro para a sala à direita
} Sala;

// Estrutura para representar um nó da árvore BST de pistas
typedef struct PistaNode {
    char pista[200];              // Conteúdo da pista
    struct PistaNode* esquerda;   // Subárvore esquerda
    struct PistaNode* direita;    // Subárvore direita
} PistaNode;

// Estrutura para um item da tabela hash (pista -> suspeito)
typedef struct ItemHash {
    char pista[200];              // Chave: pista coletada
    char suspeito[100];           // Valor: nome do suspeito
    struct ItemHash* proximo;     // Ponteiro para o próximo item (encadeamento)
} ItemHash;

// Estrutura da Tabela Hash
typedef struct TabelaHash {
    ItemHash* itens[TAMANHO_HASH]; // Array de ponteiros para itens
} TabelaHash;

// ==================== FUNÇÕES DE ÁRVORE BINÁRIA (MAPA DA MANSÃO) ====================

/**
 * Cria uma nova sala com o nome e pista especificados
 * @param nome Nome do cômodo
 * @param pista Pista encontrada no cômodo (ou string vazia)
 * @return Ponteiro para a sala criada
 */
Sala* criarSala(const char* nome, const char* pista);

/**
 * Explora a mansão de forma interativa (nível novato - sem pistas)
 * @param salaAtual Sala onde o jogador está atualmente
 */
void explorarSalas(Sala* salaAtual);

/**
 * Libera a memória alocada para a árvore de salas
 * @param sala Raiz da árvore a ser liberada
 */
void liberarArvore(Sala* sala);

// ==================== FUNÇÕES DE BST (PISTAS COLETADAS) ====================

/**
 * Insere uma pista na árvore BST de forma ordenada
 * @param raiz Raiz da árvore de pistas
 * @param pista Pista a ser inserida
 * @return Nova raiz da árvore
 */
PistaNode* inserirPista(PistaNode* raiz, const char* pista);

/**
 * Exibe todas as pistas em ordem alfabética (percurso in-order)
 * @param raiz Raiz da árvore de pistas
 */
void exibirPistas(PistaNode* raiz);

/**
 * Libera a memória alocada para a árvore de pistas
 * @param raiz Raiz da árvore de pistas
 */
void liberarPistas(PistaNode* raiz);

/**
 * Explora a mansão coletando pistas (nível aventureiro)
 * @param salaAtual Sala onde o jogador está
 * @param arvore_pistas Ponteiro para a raiz da árvore de pistas
 */
void explorarSalasComPistas(Sala* salaAtual, PistaNode** arvore_pistas);

// ==================== FUNÇÕES DE TABELA HASH (PISTAS -> SUSPEITOS) ====================

/**
 * Cria e inicializa uma nova tabela hash
 * @return Ponteiro para a tabela hash criada
 */
TabelaHash* criarTabelaHash();

/**
 * Função hash simples para calcular o índice da pista
 * @param pista String da pista
 * @return Índice na tabela hash
 */
int funcaoHash(const char* pista);

/**
 * Insere uma associação pista-suspeito na tabela hash
 * @param tabela Tabela hash
 * @param pista Chave (pista)
 * @param suspeito Valor (nome do suspeito)
 */
void inserirNaHash(TabelaHash* tabela, const char* pista, const char* suspeito);

/**
 * Busca o suspeito associado a uma pista
 * @param tabela Tabela hash
 * @param pista Pista a ser buscada
 * @return Nome do suspeito ou NULL se não encontrado
 */
char* encontrarSuspeito(TabelaHash* tabela, const char* pista);

/**
 * Libera a memória da tabela hash
 * @param tabela Tabela hash a ser liberada
 */
void liberarTabelaHash(TabelaHash* tabela);

/**
 * Conta quantas pistas estão associadas a um suspeito específico
 * @param raiz Raiz da árvore de pistas
 * @param tabela Tabela hash de pistas->suspeitos
 * @param suspeito Nome do suspeito a ser verificado
 * @return Número de pistas que apontam para o suspeito
 */
int contarPistasPorSuspeito(PistaNode* raiz, TabelaHash* tabela, const char* suspeito);

/**
 * Verifica se há pistas suficientes para acusar o suspeito
 * @param arvore_pistas Árvore de pistas coletadas
 * @param tabela Tabela hash de associações
 */
void verificarSuspeitoFinal(PistaNode* arvore_pistas, TabelaHash* tabela);

// ==================== FUNÇÕES DE EXPLORAÇÃO COMPLETA (NÍVEL MESTRE) ====================

/**
 * Explora a mansão coletando pistas e associando a suspeitos (nível mestre)
 * @param salaAtual Sala atual
 * @param arvore_pistas Ponteiro para a árvore de pistas
 * @param tabela Tabela hash de associações pista->suspeito
 */
void explorarSalasCompleto(Sala* salaAtual, PistaNode** arvore_pistas, TabelaHash* tabela);

/**
 * Obtém a pista associada a uma sala específica baseada em seu nome
 * @param nomeSala Nome da sala
 * @return String com a pista ou string vazia
 */
const char* obterPistaDaSala(const char* nomeSala);

/**
 * Obtém o suspeito associado a uma pista específica
 * @param pista Pista coletada
 * @return Nome do suspeito
 */
const char* obterSuspeitoDaPista(const char* pista);

#endif // DETECTIVE_QUEST_H
