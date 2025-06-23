#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "robot/robot_arm.h"
#include "input/input_handler.h"
#include "graphics/graphics_init.h"
#include "animation/animation.h"

// Variáveis globais para compatibilidade
static int anim_flags[3] = {0, 0, 0}; // AW, ASW, APW
int SW=0, SWB=0, SWBR=0, SWABR=0, SWMA=0;
int i=0,j=0,k=0;
static int Xmouse=0,Ymouse=0;
static float rotAngle = 0., rotAngle2 = 0.;

// Variáveis globais do braço (mantidas para compatibilidade)
float Base = 0, Pinza=0.70, Brazo = 0, AnteBrazo = 0, Mano = 0;
static float LimBase = 135, LimBrazo = 180, LimAnteBrazo = 145, LimMano = 125, LimPinza=0.40;
static int Solido = 0;

GLfloat angle, fAspect;
GLUquadricObj *quadratic;

void Animacao1();
void Animacao3();

// Inicializa parâmetros de rendering
void Inicializa (void)
{ 
    graphics_init();
    angle=45; // Distancia el Objeto
    robot_arm_init(&robot_arm);
    Animacao1();
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,0.1,400);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	//gluLookAt(0.5,5,0.5, 0,0,0, 0,10,0);
//	gluLookAt (7.5, 7.5, -12.5, 2.5, 2.5, -5.0, 0.0, 1.0, 0.0);
//	gluLookAt (5, 10, -5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//  FunçãoGLUT(Observador(x,y,z), Objeto(x,y,z), Plano(x,y,z))
//  gluLookAt (5, 10, -5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//                     * 
	gluLookAt (15, 10, -5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void Animacao3()
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
        
      //   if (gripper_opening >= 1.0f && robot_arm.shoulder.angle <= 30.0f) {
        if (gripper_opening >= 1.10f && robot_arm.shoulder.angle <= 30.0f) {
            phase = 3;
        }
    }
    // Fase 3: Fechar pinça (pegar objeto)
    else if (phase == 3) {
        gripper_opening -= VELOCIDADE_PINCA_FECHAR;
        
        if (gripper_opening <= 0.65f) {//0.4f) {
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

static GLfloat view_rotx = 20.0, view_roty = 30.0, view_rotz = 0.0;

void Desenha(void)
{ 
   	// Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLineWidth (1.5);

    // A lógica de rotação da câmera foi movida para o input handler
    // e precisa ser refatorada para atualizar a matriz de visão aqui.

    if (anim_flags[0]==1) {Animacao0();} // Animação de movimiento 
    if (anim_flags[1]==1) {Animacao2();}  // Animação de um planta de fabrica
    if (anim_flags[2]==1) {Animacao3();}  // Animação Pick and Place com Física

    // Sempre renderizar o braço robótico
    BrazoRobot();
    
	// Executa os comandos OpenGL
	glutSwapBuffers();
}

/* As funções de input (special, GerenciaMouse, keyboard) foram completamente
   movidas para o módulo src/input/input_handler.c */

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 720);
	glutCreateWindow("Brazo Robotico");
	Inicializa();
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
    
    // Configura o input handler
    InputData input_data = {
        .robot_arm = &robot_arm,
        .animation_flags = anim_flags,
        .view_angle = &angle,
        .view_spec_func = EspecificaParametrosVisualizacao
    };
    init_input_handler(input_data);

	glutMouseFunc(handle_mouse);
	glutSpecialFunc(handle_special_keys);
	glutKeyboardFunc(handle_keyboard);
	glutMainLoop();
   return 0;
}
