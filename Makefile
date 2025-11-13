# Makefile para Detective Quest
# Compilador e flags

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
LDFLAGS = 

# Diretórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável
TARGET = $(BIN_DIR)/detective_quest.exe

# Arquivos fonte
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regra padrão
all: directories $(TARGET)

# Cria diretórios necessários
directories:
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# Compila o executável
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo.
	@echo Compilacao concluida! Execute: $(TARGET)

# Compila os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executa o programa
run: all
	@$(TARGET)

# Limpa os arquivos compilados
clean:
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
	@echo Arquivos limpos!

# Recompila tudo do zero
rebuild: clean all

# Ajuda
help:
	@echo Comandos disponiveis:
	@echo   make         - Compila o projeto
	@echo   make run     - Compila e executa o jogo
	@echo   make clean   - Remove arquivos compilados
	@echo   make rebuild - Limpa e recompila tudo
	@echo   make help    - Exibe esta ajuda

.PHONY: all directories run clean rebuild help
