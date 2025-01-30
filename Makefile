# Compilador e flags
CC=gcc
CFLAGS=-Wall -Wextra -g -std=c99

# Diretórios
SRC_DIR=src
OBJ_DIR=obj

# Lista de objetos com caminho correto
OBJS=$(OBJ_DIR)/main.o $(OBJ_DIR)/paciente.o $(OBJ_DIR)/lista.o $(OBJ_DIR)/bd_paciente.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/menu.o

# Nome do executável
TARGET=healthsys

# Regra principal
all: $(TARGET)

# Gera o executável
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regra genérica para compilar arquivos .c para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)  # Cria o diretório se não existir
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)
