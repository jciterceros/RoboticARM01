#include <GL/glut.h>
#include <stdlib.h>
#include "BrazoRobot.h"
/*
static int Brazo = 0, AnteBrazo = 0, Mano = 0;
static float Base = 0;//, Brazo = 0, AnteBrazo = 0, Mano = 0;
static int Solido = 0, SW = 0;
static int i=0,j=0,k=0;
static int Xmouse=0,Ymouse=0;
static float rotAngle = 0., rotAngle2 = 0.;

//GLUquadricObj *pObj; // Quadric Object

GLfloat angle, fAspect;
GLUquadricObj *quadratic; //Novo tipo de dado para cria��o do Objeto cilindro
*/
// Inicializa par�metros de rendering

static int AW=0,ASW=0;

void Animacao1();

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


 	// Especifica que a cor de fundo da janela ser� preta
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClearColor(0.0f, 0.25f, 0.25f, 1.0f); // fundo atualmente cinza
	
	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a reflet�ncia do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);  
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    angle=45; // Distancia el Objeto
    //Base = 0;
    //Brazo = 157.5; 
    //AnteBrazo = -157.5; 
    //Mano = 0;

    Animacao1();
    
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
	gluPerspective(angle,fAspect,0.1,400);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
	//gluLookAt(0.5,5,0.5, 0,0,0, 0,10,0);
//	gluLookAt (7.5, 7.5, -12.5, 2.5, 2.5, -5.0, 0.0, 1.0, 0.0);
//	gluLookAt (5, 10, -5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//  Fun��oGLUT(Observador(x,y,z), Objeto(x,y,z), Plano(x,y,z))
//  gluLookAt (5, 10, -5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//                     * 
	gluLookAt (15, 10, -5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a corre��o de aspecto
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
    float T1 = 0.52;
	if (SWB==0)
	   {
         Base+=T1;
         if (Base>=LimBase)
            {SWB=1;}
       }
	else
       {
         Base-=T1;
         if (Base<=(-LimBase))
            {SWB=0;}         
       }
	if (SWBR==0)
	   {
         Brazo+=T1;
         if (Brazo>=LimBrazo)
            {SWBR=1;}
       }
	else
       {
         Brazo-=T1;
         if (Brazo<=(180-LimBrazo))
            {SWBR=0;}         
       }
	if (SWABR==0)
	   {
         AnteBrazo+=T1;
         if (AnteBrazo>=LimAnteBrazo)
            {SWABR=1;}
       }
	else
       {
         AnteBrazo-=T1;
         if (AnteBrazo<=(-LimAnteBrazo))
            {SWABR=0;}         
       }
	if (SWMA==0)
	   {
         Mano+=T1;
         if (Mano>=LimMano)
            {SWMA=1;}
       }
	else
       {
         Mano-=T1;
         if (Mano<=(-LimMano))
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



static GLfloat view_rotx = 20.0, view_roty = 30.0, view_rotz = 0.0;

void Desenha(void)
{ 
   	// Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glLineWidth (1.5);

    if (AW==1) {Animacao0();} // Anima��o de movimiento 
    if (ASW==1)
       {Animacao2();}  // Anima��o de um planta de fabrica
    else
       {BrazoRobot();}
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
		if (state == GLUT_DOWN) {  // Zoom-out
			if(Solido==0)
			  {
                Solido=1;
              }
            else
              {
                Solido=0;
              }
		}
		
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case '/':
//         rotAngle += 0.05;
         rotAngle = rotAngle + 0.05;
         glRotatef((GLfloat)rotAngle, 0.0, 0.0, 0.1);
         glutPostRedisplay();	
         break;
      case '*':
//         rotAngle -= 0.05;
         rotAngle = rotAngle - 0.05;
         glRotatef((GLfloat)rotAngle, 0.0, 0.0, 0.1);
         //if (rotAngle >= 360.) rotAngle = 0.;
         glutPostRedisplay();	
         break;
      case '+':
//         rotAngle += 0.05;
         rotAngle2 = rotAngle2 + 0.05;
         glRotatef((GLfloat)rotAngle2, 0, 1.0, 0.0);
         glutPostRedisplay();	
         break;
      case '-':
//         rotAngle -= 0.05;
         rotAngle2 = rotAngle2 - 0.05;
         glRotatef((GLfloat)rotAngle2, 0, 1.0, 0.0);
         //if (rotAngle >= 360.) rotAngle = 0.;
         glutPostRedisplay();	
         break;         
      case '1':
         if (Base>=-(LimBase))
            {Base = Base-5;}//cint(Base - 5) % 360;
         glutPostRedisplay();
         break;
      case '3':
         if (Base<=(LimBase))
            {Base = Base+5;}//cint(Base + 5) % 360;
         glutPostRedisplay();
         break;
                  
      case '2':
         if (Brazo>=(180-LimBrazo))
            {Brazo = (Brazo - 5);}// % 360;}
         glutPostRedisplay();
         break;
      case '5':
         if (Brazo<=(LimBrazo))
            {Brazo = (Brazo + 5);}// % 360;}
         glutPostRedisplay();
         break;
                  
      case '4':
         //AnteBrazo = (AnteBrazo - 5) % 360;
         if (AnteBrazo>=-(LimAnteBrazo))
            {AnteBrazo = (AnteBrazo - 5);}// % 360;}
         glutPostRedisplay();
         break;
      case '6':
         //AnteBrazo = (AnteBrazo + 5) % 360;
         if (AnteBrazo<=(LimAnteBrazo))
            {AnteBrazo = (AnteBrazo + 5);}// % 360;}
         glutPostRedisplay();
         break;
         
      case '7':
         //Mano = (Mano - 5) % 360;
         if (Mano>=-(LimMano))
            {Mano = (Mano - 5);}// % 360;}
         glutPostRedisplay();
         break;         
      case '9':
         //Mano = (Mano + 5) % 360;
         if (Mano<=(LimMano))
            {Mano = (Mano + 5);}// % 360;}
         glutPostRedisplay();
         break;

      case ',':
         if (Pinza>=0.70)
            {Pinza = (Pinza - 0.05);}// % 360;
         glutPostRedisplay();
         break;         
      case '0':
         if (Pinza<=1.1)
            {Pinza = (Pinza + 0.05);}// % 360;
         glutPostRedisplay();
         break;
         
      case 'a':
         if (AW==0)
            {AW=1;}
         else
            {AW=0;}
         glutPostRedisplay();
         break;         
      case 's':
         if (ASW==0)
            {ASW=1;}
         else
            {ASW=0;}         glutPostRedisplay();
         break;         
                  
      case 27:
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
