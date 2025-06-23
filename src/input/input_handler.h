#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <GL/glut.h>
#include "../robot/robot_arm.h"

// Estrutura para manter o estado necessário para o input handler
typedef struct {
    RobotArm* robot_arm;
    int* animation_flags; // AW, ASW, APW
    GLfloat* view_angle;
    void (*view_spec_func)(void); // Ponteiro para EspecificaParametrosVisualizacao
} InputData;

// Funções de callback
void handle_special_keys(int key, int x, int y);
void handle_mouse(int button, int state, int x, int y);
void handle_keyboard(unsigned char key, int x, int y);

// Função de inicialização para passar os dados necessários
void init_input_handler(InputData data);

#endif // INPUT_HANDLER_H 