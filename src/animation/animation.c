#include <GL/glut.h>
#include "animation.h"

// Variáveis de estado específicas da animação podem ser movidas para cá se necessário
extern float Base;
extern int SW;

void Animacao(void)
{
    //Base+=0.1f;
    if (SW==0)
    {
        Base+=0.55;
        if (Base>=360)
        {
            SW=1;
        }
    }
    else
    {
        Base-=3;
        if (Base<=0)
        {
            SW=0;
        }
    }
    glutPostRedisplay();
} 