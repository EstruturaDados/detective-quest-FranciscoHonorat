#include "../include/detective_quest.h"

/**
 * Monta o mapa completo da mansão
 * Estrutura fixa em árvore binária com todos os cômodos
 */
Sala* montarMapaMansao() {
    // Criação do Hall de Entrada (raiz)
    Sala* hall = criarSala("Hall de Entrada", "");
    
    // Nível 1 - Esquerda e Direita do Hall
    hall->esquerda = criarSala("Biblioteca", "");
    hall->direita = criarSala("Sala de Jantar", "");
    
    // Nível 2 - Ramificações da Biblioteca
    hall->esquerda->esquerda = criarSala("Escritorio", "");
    hall->esquerda->direita = criarSala("Sala de Estar", "");
    
    // Nível 2 - Ramificações da Sala de Jantar
    hall->direita->esquerda = criarSala("Cozinha", "");
    hall->direita->direita = criarSala("Adega", "");
    
    // Nível 3 - Ramificações da Cozinha
    hall->direita->esquerda->esquerda = criarSala("Jardim", "");
    hall->direita->esquerda->direita = criarSala("Quarto Principal", "");
    
    return hall;
}

/**
 * Exibe o menu principal e retorna a escolha do jogador
 */
int exibirMenuPrincipal() {
    int escolha;
    
    printf("\n\n");
    printf("╔═══════════════════════════════════════════╗\n");
    printf("║        🕵️  DETECTIVE QUEST  🕵️           ║\n");
    printf("║      Mistério na Mansão Abandonada       ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha o modo de jogo:\n");
    printf("\n");
    printf("  [1] NOVATO - Exploração Básica\n");
    printf("      Explore a mansão e familiarize-se com o mapa\n");
    printf("\n");
    printf("  [2] AVENTUREIRO - Coleta de Pistas\n");
    printf("      Explore e colete pistas organizadas\n");
    printf("\n");
    printf("  [3] MESTRE - Investigação Completa\n");
    printf("      Colete pistas, relacione suspeitos e resolva o caso\n");
    printf("\n");
    printf("  [0] Sair\n");
    printf("\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    
    return escolha;
}

/**
 * Modo Novato: Exploração básica da mansão
 */
void modoNovato() {
    printf("\n\n╔═══════════════════════════════════════════╗\n");
    printf("║          MODO NOVATO ATIVADO             ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    printf("\nExplore a mansão e familiarize-se com sua estrutura.\n");
    printf("Use 'e' para ir à esquerda, 'd' para direita, 's' para sair.\n");
    
    // Monta o mapa
    Sala* mansao = montarMapaMansao();
    
    // Inicia exploração
    explorarSalas(mansao);
    
    // Libera memória
    liberarArvore(mansao);
    
    printf("\nExploração concluída!\n");
}

/**
 * Modo Aventureiro: Coleta de pistas com BST
 */
void modoAventureiro() {
    printf("\n\n╔═══════════════════════════════════════════╗\n");
    printf("║        MODO AVENTUREIRO ATIVADO          ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    printf("\nExplore a mansão e colete pistas importantes.\n");
    printf("As pistas serão organizadas em ordem alfabética.\n");
    
    // Monta o mapa com pistas
    Sala* mansao = montarMapaMansao();
    
    // Define pistas para cada sala
    strcpy(mansao->esquerda->pista, obterPistaDaSala("Biblioteca"));
    strcpy(mansao->direita->pista, obterPistaDaSala("Sala de Jantar"));
    strcpy(mansao->esquerda->esquerda->pista, obterPistaDaSala("Escritorio"));
    strcpy(mansao->esquerda->direita->pista, obterPistaDaSala("Sala de Estar"));
    strcpy(mansao->direita->esquerda->pista, obterPistaDaSala("Cozinha"));
    strcpy(mansao->direita->direita->pista, obterPistaDaSala("Adega"));
    strcpy(mansao->direita->esquerda->esquerda->pista, obterPistaDaSala("Jardim"));
    strcpy(mansao->direita->esquerda->direita->pista, obterPistaDaSala("Quarto Principal"));
    
    // Inicializa árvore de pistas
    PistaNode* arvore_pistas = NULL;
    
    // Inicia exploração com coleta de pistas
    explorarSalasComPistas(mansao, &arvore_pistas);
    
    // Libera memória
    liberarArvore(mansao);
    liberarPistas(arvore_pistas);
    
    printf("\nInvestigação concluída!\n");
}

/**
 * Modo Mestre: Investigação completa com acusação
 */
void modoMestre() {
    printf("\n\n╔═══════════════════════════════════════════╗\n");
    printf("║          MODO MESTRE ATIVADO             ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    printf("\nColete pistas, relacione aos suspeitos e resolva o mistério!\n");
    printf("Você precisará de pelo menos 2 pistas para acusar alguém.\n");
    
    // Monta o mapa
    Sala* mansao = montarMapaMansao();
    
    // Inicializa estruturas de dados
    PistaNode* arvore_pistas = NULL;
    TabelaHash* tabela = criarTabelaHash();
    
    // Inicia exploração completa
    explorarSalasCompleto(mansao, &arvore_pistas, tabela);
    
    // Fase de acusação
    if (arvore_pistas != NULL) {
        verificarSuspeitoFinal(arvore_pistas, tabela);
    } else {
        printf("\nVocê não coletou nenhuma pista. Não é possível fazer uma acusação.\n");
    }
    
    // Libera memória
    liberarArvore(mansao);
    liberarPistas(arvore_pistas);
    liberarTabelaHash(tabela);
    
    printf("\nObrigado por jogar Detective Quest!\n");
}

/**
 * Função principal do programa
 * Controla o menu e inicia os diferentes modos de jogo
 */
int main() {
    int escolha;
    
    do {
        escolha = exibirMenuPrincipal();
        
        switch (escolha) {
            case 1:
                modoNovato();
                break;
            
            case 2:
                modoAventureiro();
                break;
            
            case 3:
                modoMestre();
                break;
            
            case 0:
                printf("\n\nObrigado por jogar Detective Quest!\n");
                printf("Até a próxima investigação! 🕵️\n\n");
                break;
            
            default:
                printf("\nOpção inválida! Escolha 0, 1, 2 ou 3.\n");
        }
        
    } while (escolha != 0);
    
    return 0;
}
