CC = gcc
CFLAGS = -Wall -g -Iinclude
SRC_DIR = src
OBJ_DIR = obj
TARGET = healthsys

# Definindo arquivos fontes e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJS:.o=.d)

# Regra padrão para compilar o programa
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilação dos arquivos .c para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Geração das dependências
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -MM $(CFLAGS) $< > $@

# Incluir as dependências
-include $(DEP)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)

# Regra para limpar arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(DEP)
