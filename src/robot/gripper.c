#include "gripper.h"
#include <GL/glu.h>

Gripper robot_gripper;

void gripper_init(Gripper* gripper) {
    gripper->opening = 0.65f;//0.70f;
    gripper->min_opening = 0.65f;//0.40f;
    gripper->max_opening = 1.10f;
    gripper->speed = 0.05f;
}

void gripper_set_opening(Gripper* gripper, float opening) {
    if (opening >= gripper->min_opening && opening <= gripper->max_opening) {
        gripper->opening = opening;
    }
}

float gripper_get_opening(Gripper* gripper) {
    return gripper->opening;
}

void gripper_open(Gripper* gripper, float delta) {
    float new_opening = gripper->opening + delta;
    gripper_set_opening(gripper, new_opening);
}

void gripper_close(Gripper* gripper, float delta) {
    float new_opening = gripper->opening - delta;
    gripper_set_opening(gripper, new_opening);
}

void gripper_render(Gripper* gripper, int solid_mode) {
    glPushMatrix();
        glTranslatef(0.4, 0.0, 0.0);  // Desenha a caixa de engrenagens do atuador
        
        glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glRotatef(90.0, 1.0, 0.0, 0.0);
            glTranslatef(-0.25, 0.0, -0.15);  // Desenha a capa Superior da caixa de engrenagens do atuador
            glBegin(GL_TRIANGLE_STRIP);
                glVertex3f(0.0f, -0.3f, -0.01f); // vertex 1
                glVertex3f(0.0f, 0.3f, -0.01f);  // vertex 2
                glVertex3f(0.5f, -0.1f, -0.01f); // vertex 3
                glVertex3f(0.5f, 0.1f, -0.01f);  // vertex 4
            glEnd();

            glTranslatef(0.0, 0.0, 0.31);  // Desenha a capa inferior da caixa de engrenagens do atuador
            glBegin(GL_TRIANGLE_STRIP);
                glVertex3f(0.0f, -0.3f, -0.01f); // vertex 1
                glVertex3f(0.0f, 0.3f, -0.01f);  // vertex 2
                glVertex3f(0.5f, -0.1f, -0.01f); // vertex 3
                glVertex3f(0.5f, 0.1f, -0.01f);  // vertex 4
            glEnd();

            glColor3f(0.0, 0.0, 0.0);
        glPopMatrix();

        glScalef(0.5, 0.3, 0.6);
        if (solid_mode)
            glutSolidCube(1);
        else
            glutWireCube(1);

        glPushMatrix();
            glPushMatrix();
                glTranslatef(1.0, 0.0, (0.6 - gripper->opening));
                glScalef(1, 0.4, 0.15);
                if (solid_mode)
                    glutSolidCube(1);
                else
                    glutWireCube(1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(1.0, 0.0, (-0.6 + gripper->opening));
                glScalef(1, 0.4, 0.15);
                if (solid_mode)
                    glutSolidCube(1);
                else
                    glutWireCube(1);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
} 