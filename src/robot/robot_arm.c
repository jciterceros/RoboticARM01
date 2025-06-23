#include "robot_arm.h"
#include <GL/glut.h>
#include <GL/glu.h>

RobotArm robot_arm;

void robot_arm_init(RobotArm* arm) {
    // Inicializar articulações
    joint_init(&arm->base, JOINT_BASE);
    joint_init(&arm->shoulder, JOINT_SHOULDER);
    joint_init(&arm->elbow, JOINT_ELBOW);
    joint_init(&arm->wrist, JOINT_WRIST);
    
    // Inicializar pinça
    gripper_init(&arm->gripper);
    
    // Configurações iniciais
    arm->solid_mode = 0;
    arm->animation_mode = 0;
}

void robot_arm_render(RobotArm* arm) {
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        
        // Renderizar grade de referência
        render_reference_grid();
        
        // Renderizar base
        joint_render_base(&arm->base, arm->solid_mode);
        glTranslatef(-0.35, 0.0, 0.0);
        glRotatef((GLfloat)arm->base.angle, 0.0, 1.0, 0.0);
        
        // Renderizar braço
        joint_render_shoulder(&arm->shoulder, arm->solid_mode);
        
        // Renderizar antebraço
        joint_render_elbow(&arm->elbow, arm->solid_mode);
        
        // Renderizar mão
        glTranslatef(-0.45, 0.0, 0.0);
        // glRotatef((GLfloat)arm->wrist.angle, 0.0, 0.0, 1.0);
        joint_render_wrist(&arm->wrist, arm->solid_mode);
        
        // Renderizar pinça
        gripper_render(&arm->gripper, arm->solid_mode);
        
    glPopMatrix();
}

void robot_arm_update(RobotArm* arm) {
    // Atualizações de animação podem ser adicionadas aqui
}

void robot_arm_set_solid_mode(RobotArm* arm, int solid) {
    arm->solid_mode = solid;
}

void robot_arm_toggle_animation(RobotArm* arm) {
    arm->animation_mode = !arm->animation_mode;
}

// Controles de movimento
void robot_arm_move_base(RobotArm* arm, float delta) {
    joint_rotate(&arm->base, delta);
}

void robot_arm_move_shoulder(RobotArm* arm, float delta) {
    joint_rotate(&arm->shoulder, delta);
}

void robot_arm_move_elbow(RobotArm* arm, float delta) {
    joint_rotate(&arm->elbow, delta);
}

void robot_arm_move_wrist(RobotArm* arm, float delta) {
    joint_rotate(&arm->wrist, delta);
}

void robot_arm_move_gripper(RobotArm* arm, float delta) {
    if (delta > 0) {
        gripper_open(&arm->gripper, delta);
    } else {
        gripper_close(&arm->gripper, -delta);
    }
}

// Função principal de renderização (substitui BrazoRobot)
void BrazoRobot(void) {
    robot_arm_render(&robot_arm);
} 