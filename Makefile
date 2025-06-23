# Makefile para RoboticARM01 - Versão Modular
# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lopengl32 -lglu32 -lfreeglut

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Fontes
# Adiciona automaticamente todos os arquivos .c dos subdiretórios
SOURCES = $(wildcard $(SRC_DIR)/*.c) \
          $(wildcard $(SRC_DIR)/robot/*.c) \
          $(wildcard $(SRC_DIR)/input/*.c) \
          $(wildcard $(SRC_DIR)/graphics/*.c) \
          $(wildcard $(SRC_DIR)/animation/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Executável
TARGET = $(BIN_DIR)/Robot.exe

# Regra principal
all: $(TARGET)

# Compilar executável
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Criar diretórios
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Cria diretórios de objeto para cada subdiretório de fonte
$(shell mkdir -p $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(dir $(SOURCES))))

# Limpar
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Executar
run: $(TARGET)
	./$(TARGET)

# Instalar dependências (Windows)
install-deps:
	@echo "Instalando dependências..."
	@echo "Certifique-se de ter o MinGW-w64 instalado com OpenGL e GLUT"
	@echo "Ou use o Dev-C++ com as bibliotecas OpenGL"

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make        - Compilar o projeto"
	@echo "  make clean  - Limpar arquivos compilados"
	@echo "  make run    - Compilar e executar"
	@echo "  make help   - Mostrar esta ajuda"

.PHONY: all clean run install-deps help 