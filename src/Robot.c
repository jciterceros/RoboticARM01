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
