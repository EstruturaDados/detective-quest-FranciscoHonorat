#include "../include/detective_quest.h"

// ==================== MAPEAMENTO DE PISTAS E SUSPEITOS ====================

/**
 * Retorna a pista associada a uma sala específica
 * As pistas são definidas estaticamente baseadas no nome da sala
 */
const char* obterPistaDaSala(const char* nomeSala) {
    // Biblioteca
    if (strcmp(nomeSala, "Biblioteca") == 0) {
        return "Livro sobre venenos encontrado aberto";
    }
    // Sala de Jantar
    else if (strcmp(nomeSala, "Sala de Jantar") == 0) {
        return "Copo com residuo suspeito";
    }
    // Escritorio
    else if (strcmp(nomeSala, "Escritorio") == 0) {
        return "Carta anonima ameacadora";
    }
    // Cozinha
    else if (strcmp(nomeSala, "Cozinha") == 0) {
        return "Faca com manchas de sangue";
    }
    // Jardim
    else if (strcmp(nomeSala, "Jardim") == 0) {
        return "Pegadas recentes na terra";
    }
    // Quarto Principal
    else if (strcmp(nomeSala, "Quarto Principal") == 0) {
        return "Lenco bordado com iniciais";
    }
    // Sala de Estar
    else if (strcmp(nomeSala, "Sala de Estar") == 0) {
        return "Cinzas de cigarro raro";
    }
    // Adega
    else if (strcmp(nomeSala, "Adega") == 0) {
        return "Garrafa de vinho adulterada";
    }
    
    // Sem pista para esta sala
    return "";
}

/**
 * Retorna o suspeito associado a uma pista específica
 * Mapeia cada pista para um suspeito
 */
const char* obterSuspeitoDaPista(const char* pista) {
    // Pistas do Coronel Mostarda
    if (strcmp(pista, "Faca com manchas de sangue") == 0) {
        return "Coronel Mostarda";
    }
    else if (strcmp(pista, "Cinzas de cigarro raro") == 0) {
        return "Coronel Mostarda";
    }
    
    // Pistas da Senhorita Violeta
    else if (strcmp(pista, "Livro sobre venenos encontrado aberto") == 0) {
        return "Senhorita Violeta";
    }
    else if (strcmp(pista, "Lenco bordado com iniciais") == 0) {
        return "Senhorita Violeta";
    }
    
    // Pistas do Professor Marinho
    else if (strcmp(pista, "Carta anonima ameacadora") == 0) {
        return "Professor Marinho";
    }
    else if (strcmp(pista, "Pegadas recentes na terra") == 0) {
        return "Professor Marinho";
    }
    
    // Pistas da Senhora Branca
    else if (strcmp(pista, "Copo com residuo suspeito") == 0) {
        return "Senhora Branca";
    }
    else if (strcmp(pista, "Garrafa de vinho adulterada") == 0) {
        return "Senhora Branca";
    }
    
    // Pista desconhecida
    return "Desconhecido";
}

/**
 * Explora a mansão no modo completo (nível mestre)
 * Coleta pistas e associa automaticamente aos suspeitos usando tabela hash
 */
void explorarSalasCompleto(Sala* salaAtual, PistaNode** arvore_pistas, TabelaHash* tabela) {
    char escolha;
    
    while (salaAtual != NULL) {
        // Exibe o nome da sala atual
        printf("\n===========================================\n");
        printf("Você está em: %s\n", salaAtual->nome);
        printf("===========================================\n");
        
        // Obtém a pista para esta sala
        const char* pista = obterPistaDaSala(salaAtual->nome);
        
        // Verifica se há pista nesta sala
        if (strlen(pista) > 0) {
            printf("\n🔍 PISTA ENCONTRADA: %s\n", pista);
            
            // Adiciona a pista à árvore BST
            *arvore_pistas = inserirPista(*arvore_pistas, pista);
            
            // Obtém o suspeito associado à pista
            const char* suspeito = obterSuspeitoDaPista(pista);
            
            // Adiciona à tabela hash
            inserirNaHash(tabela, pista, suspeito);
            
            printf("✓ Pista adicionada ao caderno!\n");
            printf("→ Esta pista aponta para: %s\n", suspeito);
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
        printf("  [s] Sair e fazer acusação\n");
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
}
