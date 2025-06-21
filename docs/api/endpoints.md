# API de Controles - RoboticARM01

## 📋 Visão Geral

Este documento descreve a interface de controle do RoboticARM01, que funciona através de comandos de teclado e mouse. Embora não seja uma API REST tradicional, a interface de entrada do usuário pode ser considerada como a "API" do sistema.

## 🎮 Controles de Movimento

### Controle da Base (Rotação)
| Tecla | Ação | Limite | Descrição |
|-------|------|--------|-----------|
| `1` | Rotação Negativa | -135° | Gira a base no sentido anti-horário |
| `3` | Rotação Positiva | +135° | Gira a base no sentido horário |

### Controle do Braço (Elevação)
| Tecla | Ação | Limite | Descrição |
|-------|------|--------|-----------|
| `2` | Elevação Negativa | 0° | Abaixa o braço |
| `5` | Elevação Positiva | +180° | Eleva o braço |

### Controle do Antebraço
| Tecla | Ação | Limite | Descrição |
|-------|------|--------|-----------|
| `4` | Rotação Negativa | -145° | Rotaciona o antebraço para baixo |
| `6` | Rotação Positiva | +145° | Rotaciona o antebraço para cima |

### Controle da Mão
| Tecla | Ação | Limite | Descrição |
|-------|------|--------|-----------|
| `7` | Rotação Negativa | -125° | Rotaciona a mão para a esquerda |
| `9` | Rotação Positiva | +125° | Rotaciona a mão para a direita |

### Controle da Pinça
| Tecla | Ação | Limite | Descrição |
|-------|------|--------|-----------|
| `,` | Fechar | 0.40 | Fecha a pinça |
| `0` | Abrir | 1.10 | Abre a pinça |

## 🎬 Controles de Animação

### Animações Automáticas
| Tecla | Ação | Descrição |
|-------|------|-----------|
| `A` | Toggle Animação Coordenada | Ativa/desativa animação automática de todos os componentes |
| `S` | Toggle Simulação de Fábrica | Ativa/desativa animação de múltiplos braços robóticos |

### Controles de Rotação Global
| Tecla | Ação | Descrição |
|-------|------|-----------|
| `/` | Rotação Z Negativa | Rotaciona toda a cena no eixo Z |
| `*` | Rotação Z Positiva | Rotaciona toda a cena no eixo Z |
| `+` | Rotação Y Negativa | Rotaciona toda a cena no eixo Y |
| `-` | Rotação Y Positiva | Rotaciona toda a cena no eixo Y |

## 📷 Controles de Câmera

### Navegação com Setas
| Tecla | Ação | Descrição |
|-------|------|-----------|
| `↑` | Rotação X Positiva | Rotaciona a câmera para cima |
| `↓` | Rotação X Negativa | Rotaciona a câmera para baixo |
| `←` | Rotação Y Positiva | Rotaciona a câmera para a esquerda |
| `→` | Rotação Y Negativa | Rotaciona a câmera para a direita |

### Controles de Zoom
| Botão do Mouse | Ação | Limite | Descrição |
|----------------|------|--------|-----------|
| Esquerdo | Zoom In | 10° | Aproxima a câmera |
| Direito | Zoom Out | 130° | Afasta a câmera |

### Modo de Visualização
| Botão do Mouse | Ação | Descrição |
|----------------|------|-----------|
| Meio | Toggle Wireframe/Sólido | Alterna entre modo wireframe e sólido |

## 🚪 Controles do Sistema

### Controles de Saída
| Tecla | Ação | Descrição |
|-------|------|-----------|
| `ESC` | Sair | Encerra a aplicação |

## 📊 Estados do Sistema

### Variáveis de Estado
```c
// Ângulos das articulações
static float Base = 0;           // Rotação da base
static float Brazo = 0;          // Rotação do braço
static float AnteBrazo = 0;      // Rotação do antebraço
static float Mano = 0;           // Rotação da mão
static float Pinza = 0.70;       // Abertura da pinça

// Limites de movimento
static float LimBase = 135;      // Limite da base
static float LimBrazo = 180;     // Limite do braço
static float LimAnteBrazo = 145; // Limite do antebraço
static float LimMano = 125;      // Limite da mão
static float LimPinza = 0.40;    // Limite da pinça

// Estados de animação
static int AW = 0;    // Auto animation
static int ASW = 0;   // Auto animation switch
static int Solido = 0; // Modo de visualização
```

### Valores de Incremento
- **Movimento de Articulações**: 5° por tecla pressionada
- **Movimento da Pinça**: 0.05 por tecla pressionada
- **Zoom da Câmera**: 5° por clique do mouse
- **Rotação da Câmera**: 5° por tecla de seta

## 🔄 Fluxo de Controle

### Processamento de Entrada
1. **Captura de Evento**: GLUT captura tecla pressionada ou clique do mouse
2. **Validação de Limites**: Verifica se o movimento está dentro dos limites permitidos
3. **Atualização de Estado**: Modifica as variáveis de estado correspondentes
4. **Redesenho**: Solicita redesenho da cena via `glutPostRedisplay()`

### Exemplo de Fluxo
```
Usuário pressiona '1' 
    ↓
Handler de teclado é chamado
    ↓
Verifica se Base >= -LimBase
    ↓
Se válido: Base = Base - 5
    ↓
glutPostRedisplay()
    ↓
Função de renderização é chamada
    ↓
Braço robótico é redesenhado com nova posição
```

## 🎯 Casos de Uso

### Caso de Uso 1: Movimento Manual
1. Usuário pressiona `3` para girar a base
2. Usuário pressiona `5` para elevar o braço
3. Usuário pressiona `6` para rotacionar o antebraço
4. Usuário pressiona `9` para rotacionar a mão
5. Usuário pressiona `0` para abrir a pinça

### Caso de Uso 2: Animação Automática
1. Usuário pressiona `A` para ativar animação coordenada
2. Sistema executa animação automática de todos os componentes
3. Usuário pressiona `A` novamente para desativar

### Caso de Uso 3: Ajuste de Câmera
1. Usuário usa setas para posicionar a câmera
2. Usuário usa mouse esquerdo para zoom in
3. Usuário usa mouse direito para zoom out
4. Usuário usa mouse meio para alternar modo de visualização

## ⚠️ Limitações e Considerações

### Limitações de Performance
- Movimento contínuo requer pressionar tecla repetidamente
- Não há suporte a movimento suave automático
- Limitações de FPS dependem do hardware

### Limitações de Controle
- Controles discretos (não analógicos)
- Sem suporte a múltiplas teclas simultâneas
- Sem configuração personalizável de controles

### Melhorias Futuras
- Suporte a joystick/gamepad
- Configuração de controles via arquivo
- Movimento suave automático
- Suporte a múltiplas teclas simultâneas
- Interface gráfica para configuração

## 📝 Exemplos de Código

### Handler de Teclado (Exemplo)
```c
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            if (Base >= -(LimBase)) {
                Base = Base - 5;
            }
            glutPostRedisplay();
            break;
        case '3':
            if (Base <= (LimBase)) {
                Base = Base + 5;
            }
            glutPostRedisplay();
            break;
        // ... outros casos
    }
}
```

### Handler de Mouse (Exemplo)
```c
void GerenciaMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (angle >= 10) angle -= 5;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (angle <= 130) angle += 5;
    }
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        Solido = (Solido == 0) ? 1 : 0;
    }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}
```

---

**Versão da API**: 1.0  
**Última atualização**: 2010  
**Compatibilidade**: Todas as versões do RoboticARM01 