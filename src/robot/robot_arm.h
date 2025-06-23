#ifndef ROBOT_ARM_H
#define ROBOT_ARM_H

#include "joint.h"
#include "gripper.h"

// Estrutura principal do braço robótico
typedef struct {
    Joint base;
    Joint shoulder;
    Joint elbow;
    Joint wrist;
    Gripper gripper;
    int solid_mode;
    int animation_mode;
} RobotArm;

// Funções principais
void robot_arm_init(RobotArm* arm);
void robot_arm_render(RobotArm* arm);
void robot_arm_update(RobotArm* arm);
void robot_arm_set_solid_mode(RobotArm* arm, int solid);
void robot_arm_toggle_animation(RobotArm* arm);

// Controles de movimento
void robot_arm_move_base(RobotArm* arm, float delta);
void robot_arm_move_shoulder(RobotArm* arm, float delta);
void robot_arm_move_elbow(RobotArm* arm, float delta);
void robot_arm_move_wrist(RobotArm* arm, float delta);
void robot_arm_move_gripper(RobotArm* arm, float delta);

// Função principal de renderização (substitui BrazoRobot)
void BrazoRobot(void);

// Variável global
extern RobotArm robot_arm;

#endif // ROBOT_ARM_H 