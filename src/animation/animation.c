#include <GL/glut.h>
#include <math.h>
#include "animation.h"
#include "../robot/robot_arm.h"

// Variáveis de estado específicas da animação podem ser movidas para cá se necessário
extern float Base;
extern int SW;
extern int SWB, SWBR, SWABR, SWMA;
extern RobotArm robot_arm;
extern float Brazo, AnteBrazo, Mano;
extern void BrazoRobot(void);
extern int i, j;

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

void Animacao2(void)
{
    for(j=1;j<=3;j++)
    {
        for(i=1;i<=3;i++)
        {
            glPushMatrix();
            glTranslatef (15.0, 0.0, -15.0);
            glTranslatef (-10.5*i, 0.0,10.5*j);
            BrazoRobot();
            glPopMatrix();
        }
    }
}

void Animacao3(void)
{
    // ===== CONSTANTES DE VELOCIDADE - AJUSTE AQUI =====
    const float VELOCIDADE_INTERPOLACAO = 0.001f;    // Velocidade de transição entre posições (0.01-0.05)
    const float VELOCIDADE_OMBRO = 0.001f;            // Velocidade do movimento do ombro (0.1-0.5)
    const float VELOCIDADE_PINCA_ABRIR = 0.001f;     // Velocidade de abertura da pinça (0.005-0.02)
    const float VELOCIDADE_PINCA_FECHAR = 0.001f;   // Velocidade de fechamento da pinça (0.01-0.03)
    const float VELOCIDADE_DELTA_TIME = 0.0001f;      // Delta time para física (0.005-0.02)
    // =================================================
    
    static int phase = 0;
    static float time = 0.0f;
    static float target_x = 0.0f, target_y = 0.0f, target_z = 0.0f;
    static float gripper_opening = 0.65f;
    static int object_grabbed = 0;
    
    float dt = VELOCIDADE_DELTA_TIME;
    time += dt;
    
    // Fase 0: Posição inicial
    if (phase == 0) {
        // Reset para posição inicial
        robot_arm.base.angle = 0.0f;
        robot_arm.shoulder.angle = 45.0f;
        robot_arm.elbow.angle = -45.0f;
        robot_arm.wrist.angle = 0.0f;
        gripper_opening = 0.65f;
        object_grabbed = 0;
        phase = 1;
    }
    // Fase 1: Mover para posição de pegar objeto
    else if (phase == 1) {
        target_x = 2.0f;
        target_y = 1.5f;
        target_z = 0.0f;
        
        // Cinemática inversa simplificada para posição alvo
        float dx = target_x - 0.0f;
        float dy = target_y - 0.0f;
        float distance = sqrt(dx*dx + dy*dy);
        
        // Calcular ângulos usando trigonometria
        float base_angle = atan2(dy, dx) * 180.0f / 3.14159f;
        float shoulder_angle = 45.0f + (distance * 10.0f);
        float elbow_angle = -shoulder_angle * 0.8f;
        
        // Aplicar movimento suave com interpolação mais lenta
        robot_arm.base.angle += (base_angle - robot_arm.base.angle) * VELOCIDADE_INTERPOLACAO;
        robot_arm.shoulder.angle += (shoulder_angle - robot_arm.shoulder.angle) * VELOCIDADE_INTERPOLACAO;
        robot_arm.elbow.angle += (elbow_angle - robot_arm.elbow.angle) * VELOCIDADE_INTERPOLACAO;
        
        if (fabs(robot_arm.base.angle - base_angle) < 1.0f && 
            fabs(robot_arm.shoulder.angle - shoulder_angle) < 1.0f) {
            phase = 2;
        }
    }
    // Fase 2: Abrir pinça e descer
    else if (phase == 2) {
        gripper_opening += VELOCIDADE_PINCA_ABRIR;
        robot_arm.shoulder.angle -= VELOCIDADE_OMBRO;
        if (gripper_opening >= 1.10f && robot_arm.shoulder.angle <= 30.0f) {
            phase = 3;
        }
    }
    // Fase 3: Fechar pinça (pegar objeto)
    else if (phase == 3) {
        gripper_opening -= VELOCIDADE_PINCA_FECHAR;
        if (gripper_opening <= 0.65f) {
            object_grabbed = 1;
            phase = 4;
        }
    }
    // Fase 4: Levantar com objeto
    else if (phase == 4) {
        robot_arm.shoulder.angle += VELOCIDADE_OMBRO;
        if (robot_arm.shoulder.angle >= 60.0f) {
            phase = 5;
        }
    }
    // Fase 5: Mover para posição de soltar
    else if (phase == 5) {
        target_x = -2.0f;
        target_y = 1.5f;
        target_z = 0.0f;
        float dx = target_x - 0.0f;
        float dy = target_y - 0.0f;
        float distance = sqrt(dx*dx + dy*dy);
        float base_angle = atan2(dy, dx) * 180.0f / 3.14159f;
        float shoulder_angle = 45.0f + (distance * 10.0f);
        float elbow_angle = -shoulder_angle * 0.8f;
        // Interpolação mais lenta
        robot_arm.base.angle += (base_angle - robot_arm.base.angle) * VELOCIDADE_INTERPOLACAO;
        robot_arm.shoulder.angle += (shoulder_angle - robot_arm.shoulder.angle) * VELOCIDADE_INTERPOLACAO;
        robot_arm.elbow.angle += (elbow_angle - robot_arm.elbow.angle) * VELOCIDADE_INTERPOLACAO;
        if (fabs(robot_arm.base.angle - base_angle) < 1.0f && 
            fabs(robot_arm.shoulder.angle - shoulder_angle) < 1.0f) {
            phase = 6;
        }
    }
    // Fase 6: Descer e soltar objeto
    else if (phase == 6) {
        robot_arm.shoulder.angle -= VELOCIDADE_OMBRO;
        if (robot_arm.shoulder.angle <= 30.0f) {
            phase = 7;
        }
    }
    // Fase 7: Abrir pinça (soltar objeto)
    else if (phase == 7) {
        gripper_opening += VELOCIDADE_PINCA_FECHAR;
        if (gripper_opening >= 1.0f) {
            object_grabbed = 0;
            phase = 8;
        }
    }
    // Fase 8: Voltar à posição inicial
    else if (phase == 8) {
        // Interpolação mais lenta para retorno
        robot_arm.base.angle += (0.0f - robot_arm.base.angle) * VELOCIDADE_INTERPOLACAO;
        robot_arm.shoulder.angle += (45.0f - robot_arm.shoulder.angle) * VELOCIDADE_INTERPOLACAO;
        robot_arm.elbow.angle += (-45.0f - robot_arm.elbow.angle) * VELOCIDADE_INTERPOLACAO;
        robot_arm.wrist.angle += (0.0f - robot_arm.wrist.angle) * VELOCIDADE_INTERPOLACAO;
        gripper_opening += (0.65f - gripper_opening) * VELOCIDADE_INTERPOLACAO;
        if (fabs(robot_arm.base.angle) < 1.0f && 
            fabs(robot_arm.shoulder.angle - 45.0f) < 1.0f &&
            fabs(robot_arm.elbow.angle + 45.0f) < 1.0f) {
            phase = 0; // Reiniciar ciclo
        }
    }
    // Aplicar limites físicos
    if (robot_arm.base.angle > robot_arm.base.max_angle) robot_arm.base.angle = robot_arm.base.max_angle;
    if (robot_arm.base.angle < robot_arm.base.min_angle) robot_arm.base.angle = robot_arm.base.min_angle;
    if (robot_arm.shoulder.angle > robot_arm.shoulder.max_angle) robot_arm.shoulder.angle = robot_arm.shoulder.max_angle;
    if (robot_arm.shoulder.angle < robot_arm.shoulder.min_angle) robot_arm.shoulder.angle = robot_arm.shoulder.min_angle;
    if (robot_arm.elbow.angle > robot_arm.elbow.max_angle) robot_arm.elbow.angle = robot_arm.elbow.max_angle;
    if (robot_arm.elbow.angle < robot_arm.elbow.min_angle) robot_arm.elbow.angle = robot_arm.elbow.min_angle;
    if (robot_arm.wrist.angle > robot_arm.wrist.max_angle) robot_arm.wrist.angle = robot_arm.wrist.max_angle;
    if (robot_arm.wrist.angle < robot_arm.wrist.min_angle) robot_arm.wrist.angle = robot_arm.wrist.min_angle;
    // Aplicar abertura da pinça
    robot_arm.gripper.opening = gripper_opening;
    glutPostRedisplay();
} 