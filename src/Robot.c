#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "robot/robot_arm.h"

// Variáveis globais para compatibilidade
static int AW=0,ASW=0,APW=0;
static int SW=0, SWB=0, SWBR=0, SWABR=0, SWMA=0;
static int i=0,j=0,k=0;
static int Xmouse=0,Ymouse=0;
static float rotAngle = 0., rotAngle2 = 0.;

// Variáveis globais do braço (mantidas para compatibilidade)
static float Base = 0, Pinza=0.70, Brazo = 0, AnteBrazo = 0, Mano = 0;
static float LimBase = 135, LimBrazo = 180, LimAnteBrazo = 145, LimMano = 125, LimPinza=0.40;
static int Solido = 0;

GLfloat angle, fAspect;
GLUquadricObj *quadratic;

void Animacao1();
void Animacao3();

// Inicializa parâmetros de rendering
void Inicializa (void)
{ 
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
   GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
//	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat luzEspecular[4]={-0.5, -0.5, -0.5, 1.0};// "brilho" 

	
//	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
	GLfloat posicaoLuz[4]={0.0, 150.0, 50.0, 1.0};
//	GLfloat posicaoLuz[4]={00.0, 253.0, 150.0, 15.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;


 	// Especifica que a cor de fundo da janela será preta
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClearColor(0.0f, 0.25f, 0.25f, 1.0f); // fundo atualmente cinza
	
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    angle=45; // Distancia el Objeto
    //Base = 0;
    //Brazo = 157.5; 
    //AnteBrazo = -157.5; 
    //Mano = 0;

    // Inicializar o braço robótico
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

void Animacao(void)
{
	//Base+=0.1f;
	if (SW==0)
	   {
         Base+=0.55;
         if (Base>=360)
            {SW=1;}
       }
	else
       {
         Base-=3;
         if (Base<=0)
            {SW=0;}         
       }
	glutPostRedisplay();
}

void Animacao0()
{
   // float T1 = 0.52;
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

void Animacao2()
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

    // Aplicar rotações de câmera
   //  glRotatef((GLfloat)rotAngle, 0.0, 0.0, 1.0);  // Rotação no eixo Z
   //  glRotatef((GLfloat)rotAngle2, 0.0, 1.0, 0.0); // Rotação no eixo Y

    if (AW==1) {Animacao0();} // Animação de movimiento 
    if (ASW==1) {Animacao2();}  // Animação de um planta de fabrica
    if (APW==1) {Animacao3();}  // Animação Pick and Place com Física

    // Sempre renderizar o braço robótico
    BrazoRobot();
    
	// Executa os comandos OpenGL
	glutSwapBuffers();
}

/* change view angle */
/* ARGSUSED1 */
static void special(int k, int x, int y)
{
  switch (k) {
  case GLUT_KEY_UP:
    view_rotx += 5.0;
    break;
  case GLUT_KEY_DOWN:
    view_rotx -= 5.0;
    break;
  case GLUT_KEY_LEFT:
    view_roty += 5.0;
    break;
  case GLUT_KEY_RIGHT:
    view_roty -= 5.0;
    break;
  default:
    return;
  }
  glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	if (button == GLUT_MIDDLE_BUTTON)
		if (state == GLUT_DOWN) {  // Toggle modo sólido
			robot_arm_set_solid_mode(&robot_arm, !robot_arm.solid_mode);
		}
		
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case '/':
         rotAngle = rotAngle + 5.0;
         glRotatef((GLfloat)rotAngle, 0.0, 0.0, 0.1);
         glutPostRedisplay();	
         break;
      case '*':
         rotAngle = rotAngle - 5.0;
         glRotatef((GLfloat)rotAngle, 0.0, 0.0, 0.1);
         glutPostRedisplay();	
         break;
      case '+':
         rotAngle2 = rotAngle2 + 5.0;
         glRotatef((GLfloat)rotAngle2, 0, 1.0, 0.0);
         glutPostRedisplay();	
         break;
      case '-':
         rotAngle2 = rotAngle2 - 5.0;
         glRotatef((GLfloat)rotAngle2, 0, 1.0, 0.0);
         glutPostRedisplay();	
         break;         
      case '1':
         robot_arm_move_base(&robot_arm, -5.0f);
         glutPostRedisplay();
         break;
      case '3':
         robot_arm_move_base(&robot_arm, 5.0f);
         glutPostRedisplay();
         break;
                  
      case '2':
         robot_arm_move_shoulder(&robot_arm, -5.0f);
         glutPostRedisplay();
         break;
      case '8':
         robot_arm_move_shoulder(&robot_arm, 5.0f);
         glutPostRedisplay();
         break;
                  
      case '4':
         robot_arm_move_elbow(&robot_arm, -5.0f);
         glutPostRedisplay();
         break;
      case '6':
         robot_arm_move_elbow(&robot_arm, 5.0f);
         glutPostRedisplay();
         break;
         
      case '7':
         robot_arm_move_wrist(&robot_arm, -5.0f);
         glutPostRedisplay();
         break;         
      case '9':
         robot_arm_move_wrist(&robot_arm, 5.0f);
         glutPostRedisplay();
         break;

      case '0':
         robot_arm_move_gripper(&robot_arm, 0.05f);
         glutPostRedisplay();
         break;
                  
      case ',':
         robot_arm_move_gripper(&robot_arm, -0.05f);
         glutPostRedisplay();
         break;
         
      case 'a':
      case 'A':
         if (AW==0)
            {AW=1;}
         else
            {AW=0;}
         glutPostRedisplay();
         break;         
      case 's':
      case 'S':
         if (ASW==0)
            {ASW=1;}
         else
            {ASW=0;}
         glutPostRedisplay();
         break;
         
      case 'r':
      case 'R':
         // Reset das posições
         robot_arm_init(&robot_arm);
         glutPostRedisplay();
         break;
                  
      case 'p':
         if (APW==0)
            {APW=1;}
         else
            {APW=0;}
         glutPostRedisplay();
         break;
                  
      case 27: // ESC
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (350, 250);
   glutCreateWindow ("Robotic ARM EDGE Visualizacao 3D... JciTech");
   glutDisplayFunc(Desenha); 
   glutReshapeFunc(AlteraTamanhoJanela);
   glutMouseFunc(GerenciaMouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   Inicializa();
   glutMainLoop();
//   return 0;
}
