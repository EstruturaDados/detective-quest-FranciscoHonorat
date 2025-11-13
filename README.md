# 🕵️ Detective Quest - Mistério na Mansão

**Desenvolvido por:** Enigma Studios  
**Linguagem:** C  
**Conceitos:** Árvores Binárias, BST, Tabelas Hash, Alocação Dinâmica

---

## 📖 Sobre o Jogo

Detective Quest é um jogo educativo que ensina estruturas de dados através de uma investigação interativa. O jogador explora uma mansão representada como uma árvore binária, coleta pistas armazenadas em uma BST e usa tabelas hash para relacionar pistas a suspeitos.

---

## 🎮 Modos de Jogo

### 🟢 Modo Novato
- **Objetivo:** Familiarizar-se com a estrutura da mansão
- **Conceitos:** Árvore binária básica, navegação por nós
- **Funcionalidades:**
  - Exploração interativa sala por sala
  - Escolha entre caminhos esquerdo e direito
  - Identificação de cômodos sem saída (folhas)

### 🟡 Modo Aventureiro
- **Objetivo:** Coletar e organizar pistas
- **Conceitos:** BST (Binary Search Tree), ordenação
- **Funcionalidades:**
  - Coleta de pistas em cada cômodo
  - Armazenamento ordenado em BST
  - Exibição de pistas em ordem alfabética

### 🔴 Modo Mestre
- **Objetivo:** Resolver o mistério completo
- **Conceitos:** Tabela Hash, associação chave-valor
- **Funcionalidades:**
  - Coleta de pistas com associação automática a suspeitos
  - Tabela hash para mapear pistas → suspeitos
  - Sistema de acusação com verificação de evidências
  - Mínimo de 2 pistas necessárias para acusar

---

## 🏗️ Estrutura do Projeto

```
mapQuest/
├── include/
│   └── detective_quest.h      # Definições de structs e funções
├── src/
│   ├── main.c                 # Função main e controle de menus
│   ├── arvore.c               # Funções de árvore binária
│   ├── pistas.c               # Funções de BST de pistas
│   ├── hash.c                 # Funções de tabela hash
│   └── jogo.c                 # Lógica de exploração completa
├── obj/                       # Arquivos objeto (gerado)
├── bin/                       # Executável (gerado)
├── Makefile                   # Script de compilação
└── README.md                  # Este arquivo
```

---

## 🛠️ Compilação e Execução

### Pré-requisitos
- GCC (MinGW no Windows)
- Make (opcional, mas recomendado)

### Opção 1: Usando Make (Recomendado)

```bash
# Compilar o projeto
make

# Compilar e executar
make run

# Limpar arquivos compilados
make clean

# Recompilar tudo
make rebuild

# Ver comandos disponíveis
make help
```

### Opção 2: Compilação Manual

```bash
# Criar diretórios
mkdir obj bin

# Compilar cada arquivo
gcc -Wall -Wextra -Iinclude -c src/main.c -o obj/main.o
gcc -Wall -Wextra -Iinclude -c src/arvore.c -o obj/arvore.o
gcc -Wall -Wextra -Iinclude -c src/pistas.c -o obj/pistas.o
gcc -Wall -Wextra -Iinclude -c src/hash.c -o obj/hash.o
gcc -Wall -Wextra -Iinclude -c src/jogo.c -o obj/jogo.o

# Linkar tudo
gcc obj/main.o obj/arvore.o obj/pistas.o obj/hash.o obj/jogo.o -o bin/detective_quest.exe

# Executar
bin\detective_quest.exe
```

---

## 🗺️ Mapa da Mansão

```
                    Hall de Entrada
                    /            \
            Biblioteca        Sala de Jantar
            /        \         /           \
     Escritorio  Sala de    Cozinha       Adega
                  Estar     /      \
                        Jardim  Quarto Principal
```

---

## 🔍 Pistas e Suspeitos

### Coronel Mostarda
- Faca com manchas de sangue (Cozinha)
- Cinzas de cigarro raro (Sala de Estar)

### Senhorita Violeta
- Livro sobre venenos encontrado aberto (Biblioteca)
- Lenco bordado com iniciais (Quarto Principal)

### Professor Marinho
- Carta anonima ameacadora (Escritório)
- Pegadas recentes na terra (Jardim)

### Senhora Branca
- Copo com residuo suspeito (Sala de Jantar)
- Garrafa de vinho adulterada (Adega)

---

## 💡 Conceitos Implementados

### 1. Árvore Binária
```c
typedef struct Sala {
    char nome[100];
    char pista[200];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;
```
- Representa a estrutura hierárquica da mansão
- Cada nó é um cômodo com dois possíveis caminhos

### 2. Binary Search Tree (BST)
```c
typedef struct PistaNode {
    char pista[200];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;
```
- Armazena pistas em ordem alfabética
- Inserção e exibição ordenadas automaticamente

### 3. Tabela Hash
```c
typedef struct TabelaHash {
    ItemHash* itens[TAMANHO_HASH];
} TabelaHash;
```
- Mapeia pistas para suspeitos eficientemente
- Usa encadeamento para resolver colisões
- Função hash baseada na soma dos caracteres

---

## 🎯 Como Jogar

1. **Inicie o jogo** e escolha um modo
2. **Navegue pela mansão:**
   - `e` = ir para a esquerda
   - `d` = ir para a direita
   - `s` = sair/finalizar
3. **Colete pistas** (modos Aventureiro e Mestre)
4. **Faça sua acusação** (modo Mestre)
   - Digite o nome completo do suspeito
   - São necessárias pelo menos 2 pistas

---

## 📚 Funções Principais

### Árvore Binária
- `criarSala()` - Cria um novo cômodo dinamicamente
- `explorarSalas()` - Navegação interativa básica
- `liberarArvore()` - Libera memória da árvore

### BST de Pistas
- `inserirPista()` - Insere pista ordenadamente
- `exibirPistas()` - Mostra pistas em ordem alfabética
- `explorarSalasComPistas()` - Exploração com coleta

### Tabela Hash
- `criarTabelaHash()` - Inicializa tabela
- `funcaoHash()` - Calcula índice
- `inserirNaHash()` - Adiciona associação pista→suspeito
- `encontrarSuspeito()` - Busca suspeito por pista
- `contarPistasPorSuspeito()` - Conta evidências

### Jogo Completo
- `explorarSalasCompleto()` - Exploração com hash
- `verificarSuspeitoFinal()` - Sistema de acusação
- `obterPistaDaSala()` - Mapeia sala→pista
- `obterSuspeitoDaPista()` - Mapeia pista→suspeito

---

## 🧪 Testando o Jogo

### Cenário 1: Acusar Coronel Mostarda
1. Vá para Sala de Jantar → Cozinha (pista 1)
2. Volte e vá para Biblioteca → Sala de Estar (pista 2)
3. Acuse "Coronel Mostarda" ✓

### Cenário 2: Acusar Senhorita Violeta
1. Vá para Biblioteca (pista 1)
2. Continue para Sala de Jantar → Cozinha → Quarto Principal (pista 2)
3. Acuse "Senhorita Violeta" ✓

---

## 🔧 Requisitos Técnicos

### Funcionais
✅ Árvore binária representando a mansão  
✅ Exploração interativa com escolhas  
✅ BST para armazenar pistas ordenadas  
✅ Tabela hash para associações pista-suspeito  
✅ Verificação de evidências suficientes (mín. 2 pistas)

### Não Funcionais
✅ Código modular e bem organizado  
✅ Comentários explicativos detalhados  
✅ Nomes de variáveis intuitivos  
✅ Mensagens claras para o usuário  
✅ Indentação apropriada

---

## 📝 Notas Importantes

- O mapa é **fixo e pré-definido** - não há inserção dinâmica de salas
- As pistas são **associadas estaticamente** às salas
- A exploração continua até o jogador escolher sair (`s`)
- No modo Mestre, **mínimo de 2 pistas** para acusação válida
- Toda memória é **liberada adequadamente** ao final

---

## 🎓 Aprendizado

Este projeto ensina:
- Implementação de árvores binárias em C
- Diferença entre árvore binária simples e BST
- Uso de tabelas hash com encadeamento
- Alocação e liberação dinâmica de memória
- Modularização de código em múltiplos arquivos
- Uso de structs e ponteiros
- Recursividade em estruturas de dados

---

## 👨‍💻 Autor

Desenvolvido para fins educacionais pela Enigma Studios.

**Boa investigação, Detetive!** 🕵️🔍

---

## 📄 Licença

Este é um projeto educacional livre para uso acadêmico.
