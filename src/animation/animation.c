#include <GL/glut.h>
#include "animation.h"
#include "../robot/robot_arm.h"

// Variáveis de estado específicas da animação podem ser movidas para cá se necessário
extern float Base;
extern int SW;
extern int SWB, SWBR, SWABR, SWMA;
extern RobotArm robot_arm;
extern float Brazo, AnteBrazo, Mano;

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

void Animacao0(void)
{
   float T1 = 0.02;
   if (SWB==0)
   {
      robot_arm_move_base(&robot_arm, T1);
      if (robot_arm.base.angle >= robot_arm.base.max_angle)
         {SWB=1;}
   }
   else
   {
      robot_arm_move_base(&robot_arm, -T1);
      if (robot_arm.base.angle <= robot_arm.base.min_angle)
         {SWB=0;}
   }
   if (SWBR==0)
   {
      robot_arm_move_shoulder(&robot_arm, T1);
      if (robot_arm.shoulder.angle >= robot_arm.shoulder.max_angle)
         {SWBR=1;}
   }
   else
   {
      robot_arm_move_shoulder(&robot_arm, -T1);
      if (robot_arm.shoulder.angle <= robot_arm.shoulder.min_angle)
         {SWBR=0;}
   }
   if (SWABR==0)
   {
      robot_arm_move_elbow(&robot_arm, T1);
      if (robot_arm.elbow.angle >= robot_arm.elbow.max_angle)
         {SWABR=1;}
   }
   else
   {
      robot_arm_move_elbow(&robot_arm, -T1);
      if (robot_arm.elbow.angle <= robot_arm.elbow.min_angle)
         {SWABR=0;}
   }
   if (SWMA==0)
   {
      robot_arm_move_wrist(&robot_arm, T1);
      if (robot_arm.wrist.angle >= robot_arm.wrist.max_angle)
         {SWMA=1;}
   }
   else
   {
      robot_arm_move_wrist(&robot_arm, -T1);
      if (robot_arm.wrist.angle <= robot_arm.wrist.min_angle)
         {SWMA=0;}
   }
   glutPostRedisplay();
}

void Animacao1(void)
{
    Base = 0;
    Brazo = 0;
    AnteBrazo = 0;
    Mano = 0;
    glutPostRedisplay();
} 