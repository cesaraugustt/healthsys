# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -g

# Nome do executável
TARGET = healthsys

# Diretórios
SRC_DIR = src
DATA_DIR = data
OBJ_DIR = obj
BIN_DIR = bin

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto (gerados a partir dos arquivos fonte)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Regra padrão: compila o programa
all: $(BIN_DIR)/$(TARGET)

# Regra para compilar o executável
$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)  # Cria o diretório bin se não existir
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regra para compilar cada arquivo objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)  # Cria o diretório obj se não existir
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Regra para rodar o programa
run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

# Regra para depuração (usando gdb)
debug: $(BIN_DIR)/$(TARGET)
	gdb ./$(BIN_DIR)/$(TARGET)

# Indica que 'clean', 'run' e 'debug' não são arquivos
.PHONY: all clean run debug