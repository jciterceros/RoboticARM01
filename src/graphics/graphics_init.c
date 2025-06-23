#include <GL/glut.h>
#include "graphics_init.h"

void graphics_init(void) {
    glClearColor(0.0f, 0.25f, 0.25f, 1.0f); // fundo atualmente cinza
    
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};    // "cor" 
    GLfloat luzEspecular[4]={-0.5, -0.5, -0.5, 1.0}; // "brilho" 
    GLfloat posicaoLuz[4]={0.0, 150.0, 50.0, 1.0};
    GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
    GLint especMaterial = 60;

    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
} 