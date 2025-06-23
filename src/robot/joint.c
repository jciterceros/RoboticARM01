#include "joint.h"
#include <GL/glu.h>

// Variáveis globais das articulações
Joint base_joint;
Joint shoulder_joint;
Joint elbow_joint;
Joint wrist_joint;

// Inicialização das articulações
void joint_init(Joint* joint, JointType type) {
    joint->type = type;
    joint->angle = 0.0f;
    joint->is_animated = 0;
    
    switch(type) {
        case JOINT_BASE:
            joint->min_angle = -135.0f;
            joint->max_angle = 135.0f;
            joint->speed = 5.0f;
            break;
        case JOINT_SHOULDER:
            joint->min_angle = 0.0f;
            joint->max_angle = 180.0f;
            joint->speed = 5.0f;
            break;
        case JOINT_ELBOW:
            joint->min_angle = -145.0f;
            joint->max_angle = 145.0f;
            joint->speed = 5.0f;
            break;
        case JOINT_WRIST:
            joint->min_angle = -125.0f;
            joint->max_angle = 125.0f;
            joint->speed = 5.0f;
            break;
    }
}

void joint_set_angle(Joint* joint, float angle) {
    if (joint_is_within_limits(joint, angle)) {
        joint->angle = angle;
    }
}

float joint_get_angle(Joint* joint) {
    return joint->angle;
}

void joint_rotate(Joint* joint, float delta) {
    float new_angle = joint->angle + delta;
    joint_set_angle(joint, new_angle);
}

int joint_is_within_limits(Joint* joint, float angle) {
    return (angle >= joint->min_angle && angle <= joint->max_angle);
}

// Função auxiliar para renderizar grade de referência
void render_reference_grid(void) {
    glPushMatrix();
        glBegin(GL_LINE_LOOP);
            glVertex3f(-5, 0, -5);
            glVertex3f(5, 0, -5);
            glVertex3f(5, 0, 5);
            glVertex3f(-5, 0, 5);
        glEnd();

        glBegin(GL_LINES);
            // Linhas do Eixo Z
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-5, 0, -4.5); glVertex3f(5, 0, -4.5);
            glVertex3f(-5, 0, -4); glVertex3f(5, 0, -4);
            glVertex3f(-5, 0, -3.5); glVertex3f(5, 0, -3.5);
            glVertex3f(-5, 0, -3); glVertex3f(5, 0, -3);
            glVertex3f(-5, 0, -2.5); glVertex3f(5, 0, -2.5);
            glVertex3f(-5, 0, -2); glVertex3f(5, 0, -2);
            glVertex3f(-5, 0, -1.5); glVertex3f(5, 0, -1.5);
            glVertex3f(-5, 0, -1); glVertex3f(5, 0, -1);
            glVertex3f(-5, 0, -0.5); glVertex3f(5, 0, -0.5);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(-5, 0, 0); glVertex3f(5, 0, 0); // Centro do Eixo
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-5, 0, 0.5); glVertex3f(5, 0, 0.5);
            glVertex3f(-5, 0, 1); glVertex3f(5, 0, 1);
            glVertex3f(-5, 0, 1.5); glVertex3f(5, 0, 1.5);
            glVertex3f(-5, 0, 2); glVertex3f(5, 0, 2);
            glVertex3f(-5, 0, 2.5); glVertex3f(5, 0, 2.5);
            glVertex3f(-5, 0, 3); glVertex3f(5, 0, 3);
            glVertex3f(-5, 0, 3.5); glVertex3f(5, 0, 3.5);
            glVertex3f(-5, 0, 4); glVertex3f(5, 0, 4);
            glVertex3f(-5, 0, 4.5); glVertex3f(5, 0, 4.5);
            
            // Linhas do Eixo X
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(-4.5, 0, -5); glVertex3f(-4.5, 0, 5);
            glVertex3f(-4, 0, -5); glVertex3f(-4, 0, 5);
            glVertex3f(-3.5, 0, -5); glVertex3f(-3.5, 0, 5);
            glVertex3f(-3, 0, -5); glVertex3f(-3, 0, 5);
            glVertex3f(-2.5, 0, -5); glVertex3f(-2.5, 0, 5);
            glVertex3f(-2, 0, -5); glVertex3f(-2, 0, 5);
            glVertex3f(-1.5, 0, -5); glVertex3f(-1.5, 0, 5);
            glVertex3f(-1, 0, -5); glVertex3f(-1, 0, 5);
            glVertex3f(-0.5, 0, -5); glVertex3f(-0.5, 0, 5);
            glColor3f(0.0, 1.0, 1.0);
            glVertex3f(0, 0, -5); glVertex3f(0, 0, 5); // Centro do Eixo
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(0.5, 0, -5); glVertex3f(0.5, 0, 5);
            glVertex3f(1, 0, -5); glVertex3f(1, 0, 5);
            glVertex3f(1.5, 0, -5); glVertex3f(1.5, 0, 5);
            glVertex3f(2, 0, -5); glVertex3f(2, 0, 5);
            glVertex3f(2.5, 0, -5); glVertex3f(2.5, 0, 5);
            glVertex3f(3, 0, -5); glVertex3f(3, 0, 5);
            glVertex3f(3.5, 0, -5); glVertex3f(3.5, 0, 5);
            glVertex3f(4, 0, -5); glVertex3f(4, 0, 5);
            glVertex3f(4.5, 0, -5); glVertex3f(4.5, 0, 5);
        glEnd();
    glPopMatrix();
}

// Renderização da Base (extraída do código original)
void joint_render_base(Joint* joint, int solid_mode) {
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);

        // Base fixa
        glColor3f(1, 1, 1);
        glTranslatef(-3, 0.25, 0.0);
        glPushMatrix();
            glScalef(2, 0.2, 1.0);
            if (solid_mode)
                glutSolidCube(2.0);
            else
                glutWireCube(2.0);
        glPopMatrix();

        // Base rotativa
        glColor3f(1, 1, 1);
        glTranslatef(2.7, -0.35, 0.0);
        glRotatef((GLfloat)joint->angle, 0.0, 1.0, 0.0);
        glPushMatrix();

            glScalef(0.7, 0.3, 0.7);
            glRotatef(90.0, 1.0, 0.0, 0.0);

            glPushMatrix();
                glColor3f(1, 1, 0);
                glTranslatef(0, 0, -3);
                glScalef(1, 0.8, 2);
                if (solid_mode)
                    glutSolidCube(1.0);
                else
                    glutWireCube(1.0);
            glPopMatrix();

            glColor3f(0, 0, 0);
            glTranslatef(0, 0, -2.2);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 3, 25);
            else
                glutWireTorus(0.285, 0.85, 3, 25);

            glColor3f(1, 1, 0);
            glTranslatef(0, 0, 0);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 3, 25);
            else
                glutWireTorus(0.285, 0.85, 3, 25);

            glColor3f(1, 1, 0);
            glTranslatef(0, 0, 0.5);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 3, 25);
            else
                glutWireTorus(0.285, 0.85, 3, 25);

            glColor3f(1, 1, 0);
            glTranslatef(0, 0, 0.5);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 3, 25);
            else
                glutWireTorus(0.285, 0.85, 3, 25);
            glColor3f(0, 0, 0);
            glTranslatef(0, 0, 0.5);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 3, 25);
            else
                glutWireTorus(0.285, 0.85, 3, 25);
        glPopMatrix();
    glPopMatrix();
}

// Renderização do Braço (Shoulder)
void joint_render_shoulder(Joint* joint, int solid_mode) {
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef((GLfloat)joint->angle, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
        glColor3f(0, 0, 0);

        glPushMatrix(); // Barras Prolongadoras
            glScalef(2.0, 0.5, 0.2);
            glTranslatef(0, 0, -2);
            if (solid_mode)
                glutSolidCube(1.0);
            else
                glutWireCube(1.0);
            glTranslatef(0, 0, 4);
            if (solid_mode)
                glutSolidCube(1.0);
            else
                glutWireCube(1.0);
        glPopMatrix();

        glPushMatrix(); // Borda na base
            glScalef(0.25, 0.25, 0.5);
            glRotatef(90.0, 0.0, 0.0, 1.0);

            glTranslatef(0, 3.8, 0.8);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 15, 25);
            else
                glutWireTorus(0.285, 0.85, 15, 25);
            glTranslatef(0, 0, -1.6);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 15, 25);
            else
                glutWireTorus(0.285, 0.85, 15, 25);
        glPopMatrix();

        glPushMatrix(); // Borda na frente
            glScalef(0.25, 0.25, 0.5);
            glTranslatef(3.8, 0, 0.8);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 15, 25);
            else
                glutWireTorus(0.285, 0.85, 15, 25);
            glTranslatef(0, 0, -1.6);
            if (solid_mode)
                glutSolidTorus(0.285, 0.85, 15, 25);
            else
                glutWireTorus(0.285, 0.85, 15, 25);
        glPopMatrix();

        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();
}

// Renderização do Antebraço (Elbow)
void joint_render_elbow(Joint* joint, int solid_mode) {
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)joint->angle, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
        glColor3f(0, 0, 0);
        glRotatef(90.0, 1.0, 0.0, 0.0);

        glPushMatrix(); // Barras Prolongadoras
            glScalef(2.0, 0.5, 0.2);
            glTranslatef(0, 0, -1.6);
            if (solid_mode)
                glutSolidCube(1.0);
            else
                glutWireCube(1.0);
            glTranslatef(0, 0, 3.4);
            if (solid_mode)
                glutSolidCube(1.0);
            else
                glutWireCube(1.0);
        glPopMatrix();

        // Bordas e engrenagens (código simplificado)
        glPushMatrix(); // Caixa de engrenagens na Base
            glColor3f(1.0, 1.0, 0.0);
            glTranslatef(-0.8, 0, 0);
            glScalef(0.8, 0.5, 0.5);
            if (solid_mode)
                glutSolidCube(1.0);
            else
                glutWireCube(1.0);
        glPopMatrix();

        glPushMatrix(); // Caixa de engrenagens na Frente
            glColor3f(1.0, 1.0, 0.0);
            glTranslatef(0.8, 0, 0);
            glScalef(0.8, 0.5, 0.5);
            if (solid_mode)
                glutSolidCube(1.0);
            else
                glutWireCube(1.0);
        glPopMatrix();

        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();
}

// Renderização da Mão (Wrist)
void joint_render_wrist(Joint* joint, int solid_mode) {
    glTranslatef(1.7, 0.0, 0.0);
    glRotatef((GLfloat)joint->angle, 0.0, 0.0, 1.0);
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        
        glPushMatrix();
            GLUquadric* quadratic = gluNewQuadric();
            if(quadratic) {
                glTranslatef(0.0f,0.0f,-0.32f);
                gluCylinder(quadratic,0.2f,0.2f,0.05f,20,15);
                gluDisk(quadratic,0.0f,0.2f,20,20);
                glTranslatef(0.0f,0.0f,0.05f);
                gluDisk(quadratic,0.0f,0.2f,20,20);

                glTranslatef(0.0f,0.0f,0.53f);
                gluCylinder(quadratic,0.2f,0.2f,0.05f,20,15);
                gluDisk(quadratic,0.0f,0.2f,20,20);
                glTranslatef(0.0f,0.0f,0.05f);
                gluDisk(quadratic,0.0f,0.2f,20,20);
                
                gluDeleteQuadric(quadratic);
            }
        glPopMatrix();

        glColor3f(1.0, 1.0, 1.0);
    // I am removing the final glPopMatrix to ensure the kinematic chain is not broken.
}