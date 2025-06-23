#include "input_handler.h"

static InputData input_data;

// Variáveis de estado que eram globais em Robot.c
// e são controladas apenas pelo input.
// As rotações de câmera são um bom exemplo.
static GLfloat view_rotx = 20.0, view_roty = 30.0;
static float rotAngle = 0., rotAngle2 = 0.;

void init_input_handler(InputData data) {
    input_data = data;
}

void handle_special_keys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            view_rotx += 5.0;
            break;
        case GLUT_KEY_DOWN:
            view_rotx -= 5.0;
            break;
        case GLUT_KEY_LEFT:
            view_roty += 5.0;
            break;
        case GLUT_KEY_RIGHT:
            view_roty -= 5.0;
            break;
        default:
            return;
    }
    // TODO: A lógica de rotação da câmera precisa ser refatorada para usar view_rotx/y
    glutPostRedisplay();
}

void handle_mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {  // Zoom-in
            if (*input_data.view_angle >= 10) *input_data.view_angle -= 5;
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {  // Zoom-out
            if (*input_data.view_angle <= 130) *input_data.view_angle += 5;
        }
    }
    if (button == GLUT_MIDDLE_BUTTON) {
        if (state == GLUT_DOWN) {  // Toggle modo sólido
            robot_arm_set_solid_mode(input_data.robot_arm, !input_data.robot_arm->solid_mode);
        }
    }

    if (input_data.view_spec_func) {
        input_data.view_spec_func();
    }
    glutPostRedisplay();
}

void handle_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Controles de câmera legados
        case '/':
            rotAngle += 5.0;
            glRotatef((GLfloat)rotAngle, 0.0, 0.0, 0.1);
            break;
        case '*':
            rotAngle -= 5.0;
            glRotatef((GLfloat)rotAngle, 0.0, 0.0, 0.1);
            break;
        case '+':
            rotAngle2 += 5.0;
            glRotatef((GLfloat)rotAngle2, 0, 1.0, 0.0);
            break;
        case '-':
            rotAngle2 -= 5.0;
            glRotatef((GLfloat)rotAngle2, 0, 1.0, 0.0);
            break;

        // Controles do braço
        case '1':
            robot_arm_move_base(input_data.robot_arm, -5.0f);
            break;
        case '3':
            robot_arm_move_base(input_data.robot_arm, 5.0f);
            break;
        case '2':
            robot_arm_move_shoulder(input_data.robot_arm, -5.0f);
            break;
        case '8':
            robot_arm_move_shoulder(input_data.robot_arm, 5.0f);
            break;
        case '4':
            robot_arm_move_elbow(input_data.robot_arm, -5.0f);
            break;
        case '6':
            robot_arm_move_elbow(input_data.robot_arm, 5.0f);
            break;
        case '7':
            robot_arm_move_wrist(input_data.robot_arm, -5.0f);
            break;
        case '9':
            robot_arm_move_wrist(input_data.robot_arm, 5.0f);
            break;
        case ',':
            robot_arm_move_gripper(input_data.robot_arm, -0.05f);
            break;
        case '0':
            robot_arm_move_gripper(input_data.robot_arm, 0.05f);
            break;
        
        // Controles de animação
        case 'a':
            input_data.animation_flags[0] = !input_data.animation_flags[0]; // AW
            break;
        case 's':
            input_data.animation_flags[1] = !input_data.animation_flags[1]; // ASW
            break;
        case 'd':
            input_data.animation_flags[2] = !input_data.animation_flags[2]; // APW
            break;
        case 'r':
            // Reset das posições
            robot_arm_init(input_data.robot_arm);
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            return;
    }
    glutPostRedisplay();
} 