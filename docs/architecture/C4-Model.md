# C4 – Modelo de Código

## Visão Geral

Este documento descreve a estrutura de código do projeto RoboticARM01, seguindo o modelo C4 de arquitetura. O projeto é uma simulação 3D de braço robótico desenvolvida em C com OpenGL.

## Estrutura de Arquivos

### Estrutura Atual (Legacy)
```
RoboticARM01/
├── src/
│   ├── Robot.c          # Arquivo principal (418 linhas)
│   └── BrazoRobot.h     # Header com funções do braço (420 linhas)
├── bin/
│   ├── Robot.exe        # Executável compilado
│   └── libfreeglut.dll  # DLL do FreeGLUT
├── docs/
│   └── images/          # Screenshots e GIFs
└── README.md
```

### Estrutura Proposta (Refatorada)
```
RoboticARM01/
├── src/
│   ├── core/
│   │   ├── application.c    # Inicialização da aplicação
│   │   ├── application.h
│   │   ├── window.c         # Gerenciamento de janela
│   │   └── window.h
│   ├── graphics/
│   │   ├── renderer.c       # Renderização OpenGL
│   │   ├── renderer.h
│   │   ├── shader.c         # Shaders modernos
│   │   ├── shader.h
│   │   ├── mesh.c           # Geometria 3D
│   │   └── mesh.h
│   ├── robot/
│   │   ├── robot_arm.c      # Lógica principal do braço
│   │   ├── robot_arm.h
│   │   ├── joint.c          # Articulações
│   │   ├── joint.h
│   │   ├── gripper.c        # Pinça
│   │   └── gripper.h
│   ├── input/
│   │   ├── input_handler.c  # Teclado e mouse
│   │   └── input_handler.h
│   ├── animation/
│   │   ├── animation_controller.c
│   │   └── animation_controller.h
│   ├── math/
│   │   ├── vector3.c        # Matemática 3D
│   │   ├── vector3.h
│   │   ├── matrix4.c
│   │   └── matrix4.h
│   └── utils/
│       ├── config.c         # Configurações
│       ├── config.h
│       ├── logger.c         # Sistema de log
│       └── logger.h
```

## Principais Funções

### Funções de Renderização (Graphics)
```c
// Renderização principal do braço robótico
void BrazoRobot(void);

// Inicialização de parâmetros gráficos
void Inicializa(void);

// Configuração de projeção e viewport
void EspecificaParametrosVisualizacao(void);

// Callback de redimensionamento
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
```

### Funções de Entrada (Input)
```c
// Handler de teclado
void keyboard(unsigned char key, int x, int y);

// Handler de mouse
void GerenciaMouse(int button, int state, int x, int y);

// Handler de teclas especiais (setas)
static void special(int k, int x, int y);
```

### Funções de Animação (Animation)
```c
// Animação automática básica
void Animacao(void);

// Animação coordenada de todos os componentes
void Animacao0(void);

// Reset de animação
void Animacao1(void);

// Animação de múltiplos braços
void Animacao2(void);
```

### Função Principal
```c
int main(int argc, char** argv);
```

## Variáveis Globais Principais

### Estado do Braço Robótico
```c
static float Base = 0;           // Rotação da base
static float Brazo = 0;          // Rotação do braço
static float AnteBrazo = 0;      // Rotação do antebraço
static float Mano = 0;           // Rotação da mão
static float Pinza = 0.70;       // Abertura da pinça
```

### Limites de Movimento
```c
static float LimBase = 135;      // Limite da base
static float LimBrazo = 180;     // Limite do braço
static float LimAnteBrazo = 145; // Limite do antebraço
static float LimMano = 125;      // Limite da mão
static float LimPinza = 0.40;    // Limite da pinça
```

### Controles de Animação
```c
static int SW = 0;    // Switch de animação básica
static int AW = 0;    // Auto animation
static int ASW = 0;   // Auto animation switch
```

### Configurações Gráficas
```c
static int Solido = 0;           // Modo wireframe/sólido
GLfloat angle, fAspect;          // Ângulo de projeção e aspect ratio
GLUquadricObj *quadratic;        // Objeto para cilindros
```

## Padrões de Código Identificados

### 1. Renderização Condicional
```c
if (Solido == 1) {
    glutSolidCube(1.0);
} else {
    glutWireCube(1.0);
}
```

### 2. Transformações Hierárquicas
```c
glPushMatrix();
glTranslatef(x, y, z);
glRotatef(angle, 0.0, 1.0, 0.0);
// Renderização do componente
glPopMatrix();
```

### 3. Controle de Limites
```c
if (Base >= -(LimBase)) {
    Base = Base - 5;
}
```

## Dependências Externas

### Bibliotecas OpenGL
- **GL**: Funções básicas do OpenGL
- **GLU**: Utilitários do OpenGL (gluPerspective, gluLookAt)
- **GLUT**: Toolkit de interface (glutInit, glutCreateWindow)

### Bibliotecas do Sistema
- **stdlib.h**: Funções padrão
- **math.h**: Funções matemáticas

## Pontos de Melhoria Identificados

1. **Modularização**: Separar responsabilidades em módulos
2. **Eliminação de Variáveis Globais**: Usar estruturas de dados
3. **Sistema de Configuração**: Arquivo de configuração externo
4. **Tratamento de Erros**: Sistema robusto de error handling
5. **Documentação de Código**: Comentários e documentação inline
6. **Testes Unitários**: Cobertura de testes
7. **Build System Moderno**: CMake ou Makefile estruturado

## Próximos Passos

1. Implementar estrutura modular proposta
2. Migrar para OpenGL moderno (Core Profile)
3. Implementar sistema de configuração
4. Adicionar testes unitários
5. Documentar APIs dos módulos 