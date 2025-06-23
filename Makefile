# Makefile para RoboticARM01 - Versão Modular
# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lopengl32 -lglu32 -lfreeglut

# Diretórios
SRCDIR = src
ROBOTDIR = $(SRCDIR)/robot
BINDIR = bin
OBJDIR = obj

# Arquivos fonte
SOURCES = $(SRCDIR)/Robot.c \
          $(ROBOTDIR)/robot_arm.c \
          $(ROBOTDIR)/joint.c \
          $(ROBOTDIR)/gripper.c

# Arquivos objeto
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Executável
TARGET = $(BINDIR)/Robot.exe

# Regra principal
all: $(TARGET)

# Compilar executável
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compilar arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Criar diretórios
$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Limpar
clean:
	rm -rf $(OBJDIR) $(BINDIR)

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