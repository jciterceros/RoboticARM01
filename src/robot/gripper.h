#ifndef GRIPPER_H
#define GRIPPER_H

#include <GL/glut.h>

// Estrutura da pinça
typedef struct {
    float opening;
    float min_opening;
    float max_opening;
    float speed;
} Gripper;

// Funções da pinça
void gripper_init(Gripper* gripper);
void gripper_set_opening(Gripper* gripper, float opening);
float gripper_get_opening(Gripper* gripper);
void gripper_open(Gripper* gripper, float delta);
void gripper_close(Gripper* gripper, float delta);
void gripper_render(Gripper* gripper, int solid_mode);

// Variável global
extern Gripper robot_gripper;

#endif // GRIPPER_H 