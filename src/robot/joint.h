#ifndef JOINT_H
#define JOINT_H

#include <GL/glut.h>

// Tipos de articulação
typedef enum {
    JOINT_BASE,
    JOINT_SHOULDER,
    JOINT_ELBOW,
    JOINT_WRIST
} JointType;

// Estrutura da articulação
typedef struct {
    JointType type;
    float angle;
    float min_angle;
    float max_angle;
    float speed;
    int is_animated;
} Joint;

// Funções das articulações
void joint_init(Joint* joint, JointType type);
void joint_set_angle(Joint* joint, float angle);
float joint_get_angle(Joint* joint);
void joint_rotate(Joint* joint, float delta);
int joint_is_within_limits(Joint* joint, float angle);

// Renderização específica de cada articulação
void joint_render_base(Joint* joint, int solid_mode);
void joint_render_shoulder(Joint* joint, int solid_mode);
void joint_render_elbow(Joint* joint, int solid_mode);
void joint_render_wrist(Joint* joint, int solid_mode);

// Função auxiliar para renderizar grade de referência
void render_reference_grid(void);

// Variáveis globais (serão movidas para uma estrutura)
extern Joint base_joint;
extern Joint shoulder_joint;
extern Joint elbow_joint;
extern Joint wrist_joint;

#endif // JOINT_H 