# Guia de Instalação - RoboticARM01

## 📋 Pré-requisitos

### Sistema Operacional
- **Windows**: 7, 8, 10, 11
- **Linux**: Ubuntu 18.04+, CentOS 7+, ou distribuições similares
- **macOS**: 10.14+ (Mojave ou superior)

### Ferramentas de Desenvolvimento
- **Compilador C**: GCC 7+, Clang 6+, ou MSVC 2017+
- **Make**: GNU Make ou NMake (Windows)
- **CMake**: 3.15+ (opcional, para build moderno)

### Bibliotecas Necessárias
- **OpenGL**: Suporte nativo ou Mesa3D (Linux)
- **GLUT**: FreeGLUT 3.0+
- **GLU**: Utilitários OpenGL (geralmente incluído)

## 🚀 Instalação Rápida

### Windows (Método Simples)
1. **Baixe o executável pré-compilado**:
   ```bash
   # Clone o repositório
   git clone https://github.com/jciterceros/RoboticARM01.git
   cd RoboticARM01
   
   # Execute diretamente
   .\bin\Robot.exe
   ```

### Windows (Compilação)
1. **Instale o MinGW-w64**:
   ```bash
   # Via MSYS2 (recomendado)
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-freeglut
   pacman -S mingw-w64-x86_64-glu
   ```

2. **Compile o projeto**:
   ```bash
   cd src
   gcc -o ../bin/Robot.exe Robot.c -lopengl32 -lfreeglut -lglu32
   ```

### Linux (Ubuntu/Debian)
```bash
# Instale as dependências
sudo apt update
sudo apt install build-essential freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev

# Clone e compile
git clone https://github.com/jciterceros/RoboticARM01.git
cd RoboticARM01/src
make
```

### macOS
```bash
# Instale o Xcode Command Line Tools
xcode-select --install

# Instale as dependências via Homebrew
brew install freeglut

# Clone e compile
git clone https://github.com/jciterceros/RoboticARM01.git
cd RoboticARM01/src
make
```

## 🔧 Configuração Detalhada

### Estrutura de Build

#### Makefile Básico
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lopengl32 -lfreeglut -lglu32

# Windows
ifeq ($(OS),Windows_NT)
    LIBS = -lopengl32 -lfreeglut -lglu32
    EXE = .exe
else
    # Linux/macOS
    LIBS = -lGL -lGLU -lglut
    EXE = 
endif

TARGET = ../bin/Robot$(EXE)
SOURCES = Robot.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
```

#### CMake (Recomendado para versão refatorada)
```cmake
cmake_minimum_required(VERSION 3.15)
project(RoboticARM01 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Encontrar OpenGL
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Arquivos fonte
set(SOURCES
    src/core/application.c
    src/graphics/renderer.c
    src/robot/robot_arm.c
    src/input/input_handler.c
    src/animation/animation_controller.c
    src/math/vector3.c
    src/math/matrix4.c
    src/utils/config.c
    src/utils/logger.c
)

# Executável
add_executable(RoboticARM01 ${SOURCES})

# Incluir diretórios
target_include_directories(RoboticARM01 PRIVATE
    src/
    include/
)

# Linkar bibliotecas
target_link_libraries(RoboticARM01
    OpenGL::GL
    GLUT::GLUT
)
```

### Variáveis de Ambiente

#### Windows
```batch
# Adicione ao PATH
set PATH=%PATH%;C:\MinGW\bin
set PATH=%PATH%;C:\freeglut\bin
```

#### Linux/macOS
```bash
# Adicione ao ~/.bashrc ou ~/.zshrc
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

## 🎮 Executando o Projeto

### Controles Básicos
- **Teclas 1-3**: Controle da base
- **Teclas 2-5**: Controle do braço
- **Teclas 4-6**: Controle do antebraço
- **Teclas 7-9**: Controle da mão
- **Teclas ,-0**: Controle da pinça
- **Tecla A**: Animação automática
- **Tecla S**: Simulação de fábrica
- **ESC**: Sair

### Controles de Câmera
- **Setas**: Rotação da câmera
- **Mouse Esquerdo**: Zoom in
- **Mouse Direito**: Zoom out
- **Mouse Meio**: Toggle wireframe/sólido

## 🐛 Solução de Problemas

### Erro: "freeglut.dll not found"
**Solução**: Copie `libfreeglut.dll` para o diretório do executável ou adicione ao PATH.

### Erro: "OpenGL not supported"
**Solução**: Atualize os drivers da placa de vídeo ou instale Mesa3D (Linux).

### Erro: "GLUT not found"
**Solução**: Instale o FreeGLUT:
```bash
# Ubuntu/Debian
sudo apt install freeglut3-dev

# macOS
brew install freeglut

# Windows
# Baixe de https://www.transmissionzero.co.uk/software/freeglut-devel/
```

### Erro de Compilação
**Solução**: Verifique se todas as dependências estão instaladas:
```bash
# Verificar versão do GCC
gcc --version

# Verificar se OpenGL está disponível
glxinfo | grep "OpenGL version"  # Linux
```

## 📦 Distribuição

### Criando um Pacote Executável

#### Windows
```batch
# Criar diretório de distribuição
mkdir dist
copy bin\Robot.exe dist\
copy bin\libfreeglut.dll dist\
copy README.md dist\
```

#### Linux/macOS
```bash
# Criar tarball
tar -czf RoboticARM01.tar.gz bin/ src/ docs/ README.md
```

### Dependências para Distribuição
- **Windows**: `Robot.exe`, `libfreeglut.dll`
- **Linux**: `Robot` (executável), bibliotecas do sistema
- **macOS**: `Robot` (executável), frameworks do sistema

## 🔄 Atualizações

### Atualizando o Código
```bash
# Atualizar repositório
git pull origin main

# Recompilar
cd src
make clean
make
```

### Atualizando Dependências
```bash
# Linux
sudo apt update && sudo apt upgrade

# macOS
brew update && brew upgrade

# Windows
# Baixe versões mais recentes das bibliotecas
```

## 📞 Suporte

### Logs de Debug
Para habilitar logs detalhados, compile com:
```bash
gcc -DDEBUG -o Robot.exe Robot.c -lopengl32 -lfreeglut -lglu32
```

### Relatórios de Bug
Ao reportar problemas, inclua:
- Sistema operacional e versão
- Versão do compilador
- Versão das bibliotecas OpenGL/GLUT
- Logs de erro completos
- Passos para reproduzir o problema

---

**Última atualização**: 2010  
**Versão**: 1.0  
**Compatibilidade**: Windows, Linux, macOS 