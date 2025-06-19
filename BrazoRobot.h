
//static int Brazo = 0, AnteBrazo = 0, Mano = 0;
static float Base = 0, Pinza=0.70, Brazo = 0, AnteBrazo = 0, Mano = 0;

static float LimBase = 135, LimBrazo = 180, LimAnteBrazo = 145, LimMano = 125, LimPinza=0.40;//, Brazo = 0, AnteBrazo = 0, Mano = 0;

static int Solido = 0, SW = 0, SWB = 0, SWBR = 0, SWABR = 0, SWMA = 0;


static int i=0,j=0,k=0;

static int Xmouse=0,Ymouse=0;
static float rotAngle = 0., rotAngle2 = 0.;

//GLUquadricObj *pObj; // Quadric Object

GLfloat angle, fAspect;
GLUquadricObj *quadratic; //Novo tipo de dado para criação do Objeto cilindro

void BrazoRobot(void)
{
glPushMatrix();
   glColor3f (1.0, 1.0, 1.0);
   //glTranslatef (10.5, 0.0, 0.0);
   
   glPushMatrix();
        glBegin (GL_LINE_LOOP);
                glVertex3f (-5, 0, -5);glVertex3f (5, 0, -5);
                glVertex3f (5, 0, 5);glVertex3f (-5, 0, 5);
        glEnd ();

        glBegin (GL_LINES);
         //Linhas do Eixo Z
               glColor3f (0.0, 1.0, 0.0);
               glVertex3f (-5, 0,-4.5);glVertex3f (5, 0,-4.5);
               glVertex3f (-5, 0,-4);glVertex3f (5, 0,-4);
               glVertex3f (-5, 0,-3.5);glVertex3f (5, 0,-3.5);
               glVertex3f (-5, 0,-3);glVertex3f (5, 0,-3);
               glVertex3f (-5, 0,-2.5);glVertex3f (5, 0,-2.5);
               glVertex3f (-5, 0,-2);glVertex3f (5, 0,-2);
               glVertex3f (-5, 0,-1.5);glVertex3f (5, 0,-1.5);
               glVertex3f (-5, 0,-1);glVertex3f (5, 0,-1);
               glVertex3f (-5, 0,-0.5);glVertex3f (5, 0,-0.5);
               glColor3f (0.0, 0.0, 1.0);
               glVertex3f (-5, 0,0);glVertex3f (5, 0,0); // Centro do Eixo Passando por Cero
               glColor3f (0.0, 1.0, 0.0);
               glVertex3f (-5, 0,0.5);glVertex3f (5, 0,0.5);
               glVertex3f (-5, 0,1);glVertex3f (5, 0,1);
               glVertex3f (-5, 0,1.5);glVertex3f (5, 0,1.5);
               glVertex3f (-5, 0,2);glVertex3f (5, 0,2);
               glVertex3f (-5, 0,2.5);glVertex3f (5, 0,2.5);
               glVertex3f (-5, 0,3);glVertex3f (5, 0,3);
               glVertex3f (-5, 0,3.5);glVertex3f (5, 0,3.5);
               glVertex3f (-5, 0,4);glVertex3f (5, 0,4);
               glVertex3f (-5, 0,4.5);glVertex3f (5, 0,4.5);
         //Linhas do Eixo X
               glColor3f (0.0, 1.0, 0.0);
               glVertex3f (-4.5, 0,-5);glVertex3f (-4.5, 0,5);
               glVertex3f (-4, 0,-5);glVertex3f (-4, 0,5);
               glVertex3f (-3.5, 0,-5);glVertex3f (-3.5, 0,5);
               glVertex3f (-3, 0,-5);glVertex3f (-3, 0,5);
               glVertex3f (-2.5, 0,-5);glVertex3f (-2.5, 0,5);
               glVertex3f (-2, 0,-5);glVertex3f (-2, 0,5);
               glVertex3f (-1.5, 0,-5);glVertex3f (-1.5, 0,5);
               glVertex3f (-1, 0,-5);glVertex3f (-1, 0,5);
               glVertex3f (-0.5, 0,-5);glVertex3f (-0.5, 0,5);
               glColor3f (0.0, 1.0, 1.0);
               glVertex3f (0, 0,-5);glVertex3f (0, 0,5); // Centro do Eixo Passando por Cero
               glColor3f (0.0, 1.0, 0.0);
               glVertex3f (0.5, 0,-5);glVertex3f (0.5, 0,5);
               glVertex3f (1, 0,-5);glVertex3f (1, 0,5);
               glVertex3f (1.5, 0,-5);glVertex3f (1.5, 0,5);
               glVertex3f (2, 0,-5);glVertex3f (2, 0,5);
               glVertex3f (2.5, 0,-5);glVertex3f (2.5, 0,5);
               glVertex3f (3, 0,-5);glVertex3f (3, 0,5);
               glVertex3f (3.5, 0,-5);glVertex3f (3.5, 0,5);
               glVertex3f (4, 0,-5);glVertex3f (4, 0,5);
               glVertex3f (4.5, 0,-5);glVertex3f (4.5, 0,5);
         glEnd ();
   glPopMatrix();

//****************************  BASE *******************************************
   glPushMatrix();
         glColor3f (1.0, 1.0, 1.0);

         glColor3f (1, 1, 1);
         glTranslatef (-3, 0.25, 0.0);
         glPushMatrix();
               glScalef (2, 0.2, 1.0);
               if (Solido==1)
                  {glutSolidCube (2.0);}
               else
                  {glutWireCube (2.0);}                  
         glPopMatrix();

         glColor3f (1, 1, 1);
         glTranslatef (2.7, -0.35, 0.0);
         glRotatef ((GLfloat) Base, 0.0, 1.0, 0.0);
         glPushMatrix();

               glScalef (0.7, 0.3, 0.7);
               glRotatef (90.0, 1.0, 0.0, 0.0);

               glPushMatrix();              
                     glColor3f (1, 1, 0);
                     glTranslatef (0, 0, -3);
                     glScalef (1, 0.8, 2);
                     if (Solido==1)
                        {glutSolidCube (1.0);}
                     else
                        {glutWireCube (1.0);}
               glPopMatrix();
               
               glColor3f (0, 0, 0);
               glTranslatef (0, 0, -2.2);
               if (Solido==1)
                   {glutSolidTorus (0.285, 0.85, 3, 25);}
               else
                   {glutWireTorus (0.285, 0.85, 3, 25);}
                   
               glColor3f (1, 1, 0);
               glTranslatef (0, 0, 0);
               if (Solido==1)
                  {glutSolidTorus (0.285, 0.85, 3, 25);}
               else
                  {glutWireTorus (0.285, 0.85, 3, 25);}

               glColor3f (1, 1, 0);
               glTranslatef (0, 0, 0.5);
               if (Solido==1)
                  {glutSolidTorus (0.285, 0.85, 3, 25);}
               else
                  {glutWireTorus (0.285, 0.85, 3, 25);}
               
               glColor3f (1, 1, 0);
               glTranslatef (0, 0, 0.5);
               if (Solido==1)
                  {glutSolidTorus (0.285, 0.85, 3, 25);}
               else
                  {glutWireTorus (0.285, 0.85, 3, 25);}
               glColor3f (0, 0, 0);
               glTranslatef (0, 0, 0.5);
               if (Solido==1)
                  {glutSolidTorus (0.285, 0.85, 3, 25);}
               else
                  {glutWireTorus (0.285, 0.85, 3, 25);}
         glPopMatrix();

//****************************  Brazo ******************************************         
         glColor3f (1.0, 1.0, 1.0);
         
         glTranslatef (0.0, 1.0, 0.0);//0.6, 0);
         glRotatef ((GLfloat) Brazo, 0.0, 0.0, 1.0);
         glTranslatef (1.0, 0.0, 0.0);
         glPushMatrix();
               glColor3f (0, 0, 0);

               glPushMatrix(); // Barras Prolongadoras
                     glScalef (2.0, 0.5, 0.2);
                     glTranslatef (0, 0, -2);
                     if (Solido==1)
                        {glutSolidCube (1.0);}
                     else
                        {glutWireCube (1.0);}
                     glTranslatef (0, 0, 4);
                     if (Solido==1)
                        {glutSolidCube (1.0);}
                     else
                        {glutWireCube (1.0);}
               glPopMatrix();
               
               glPushMatrix();//Borda na base
                     glScalef (0.25, 0.25, 0.5);
                     glRotatef (90.0, 0.0, 0.0, 1.0);

                     glTranslatef (0, 3.8, 0.8);
                     if (Solido==1)
                        {glutSolidTorus (0.285, 0.85, 15, 25);}
                     else
                        {glutWireTorus (0.285, 0.85, 15, 25);}
                     glTranslatef (0, 0, -1.6);
                     if (Solido==1)
                        {glutSolidTorus (0.285, 0.85, 15, 25);}
                     else
                        {glutWireTorus (0.285, 0.85, 15, 25);}
               glPopMatrix();

               glPushMatrix();//Borda na frente
                     glScalef (0.25, 0.25, 0.5);
                     glTranslatef (3.8, 0, 0.8);
                     if (Solido==1)
                        {glutSolidTorus (0.285, 0.85, 15, 25);}
                     else
                        {glutWireTorus (0.285, 0.85, 15, 25);}
                     glTranslatef (0, 0, -1.6);
                     if (Solido==1)
                        {glutSolidTorus (0.285, 0.85, 15, 25);}
                     else
                        {glutWireTorus (0.285, 0.85, 15, 25);}
               glPopMatrix();
               
         glColor3f (1.0, 1.0, 1.0);
         glPopMatrix();

//****************************  AnteBrazo **************************************
         glColor3f (1.0, 1.0, 1.0);

         glTranslatef (1.0, 0.0, 0.0);
         glRotatef ((GLfloat) AnteBrazo, 0.0, 0.0, 1.0);
         glTranslatef (1.0, 0.0, 0.0);
         glPushMatrix();
               glColor3f (0, 0, 0);
               glRotatef (90.0, 1.0, 0.0, 0.0);
                                       
               glPushMatrix(); // Barras Prolongadoras
                     glScalef (2.0, 0.5, 0.2);
                     glTranslatef (0, 0, -1.6);
                     if (Solido==1)
                        {glutSolidCube (1.0);}
                     else
                        {glutWireCube (1.0);}
                     glTranslatef (0, 0, 3.4);
                     if (Solido==1)
                        {glutSolidCube (1.0);}
                     else
                        {glutWireCube (1.0);}
               glPopMatrix();

               glPushMatrix(); //Borda na base
                     glScalef (0.25, 0.25, 0.4);
                     glRotatef (90.0, 0.0, 0.0, 1.0);

                     glTranslatef (0, 3.8, 0.85);
                     if (Solido==1)
                        {glutSolidTorus (0.285, 0.85, 15, 25);}
                     else
                        {glutWireTorus (0.285, 0.85, 15, 25);}
                     glTranslatef (0, 0, -1.55);
                     if (Solido==1)
                        {glutSolidTorus (0.285, 0.85, 15, 25);}
                     else
                        {glutWireTorus (0.285, 0.85, 15, 25);}

               glPopMatrix();

               glPushMatrix(); //Borda na Frente Horizontal
                     glScalef (0.25, 0.25, 0.4);
                     glRotatef (90.0, 0.0, 0.0, 1.0);


                     glTranslatef (0, -3.5, 0.85);
                     if (Solido==1)
                        {glutSolidTorus (0.285, 0.85, 15, 25);}
                     else
                        {glutWireTorus (0.285, 0.85, 15, 25);}
                     glTranslatef (0, 0, -1.55);
                     if (Solido==1)
                        {glutSolidTorus (0.285, 0.85, 15, 25);}
                     else
                        {glutWireTorus (0.285, 0.85, 15, 25);}

                     glPushMatrix(); //Borda na Frente Pos Vertical
                           glRotatef (90.0, 0.0, 1.0, 0.0);
                           glScalef (0.95, 0.95, 0.4);
                           glTranslatef (-0.8, -0.5, 2.40);
                           if (Solido==1)
                              {glutSolidTorus (0.285, 0.85, 15, 25);}
                           else
                              {glutWireTorus (0.285, 0.85, 15, 25);}
                           glTranslatef (0, 0, -5);
                           if (Solido==1)
                              {glutSolidTorus (0.285, 0.85, 15, 25);}
                           else
                              {glutWireTorus (0.285, 0.85, 15, 25);}
                     glPopMatrix();
                     

                     glPushMatrix(); //Tampa da Borda da Frente Pos Vertical & Cicindro
                           if (Solido==1)
                              {glColor4f(0.0, 0.0, 0.0, 0.75);}
                           glRotatef (90.0, 0.0, 1.0, 0.0);
                           glTranslatef (-0.7, -0.9, 1.0);
                           glBegin (GL_TRIANGLES);
                          //     glColor4f(0.0, 0.0, 0.0, 0.75);
                          //glVertex3f(Altura, Largua, Desvio) todo aplicado no angulo de rotação 90° em Y
                                glVertex3f(1.0, 0.0, 0.0);
                                glVertex3f(0.0, -2.5, 0.0);
                                glVertex3f(-1.0, 0.0, 0.0);
                           glEnd();

                           glTranslatef (0.0, 0.0, -2.0);
                           glBegin (GL_TRIANGLES);
                           //     glColor4f(0.0, 0.0, 1.0, 0.75);
                          //glVertex3f(Altura, Largua, Desvio) todo aplicado no angulo de rotação 90° em Y
                                glVertex3f(1.0, 0.0, 0.0);
                                glVertex3f(0.0, -2.5, 0.0);
                                glVertex3f(-1.0, 0.0, 0.0);
                           glEnd();
                           
                           glPushMatrix();
                           //    glColor4f(1.0, 1.0, 1.0, 0.75);
                                 quadratic=gluNewQuadric();
                                 glTranslatef(0.0f,-2.0f,0.0f);
                                 gluCylinder(quadratic,0.5f,0.5f,2.0f,20,15);	// desenha o Cilindro
                                 gluDisk(quadratic,0.0f,0.5f,32,32);		    // Draw A Disc (CD Shape)
                           //    glColor4f(0.0, 0.0, 1.0, 0.75);
                                 glTranslatef(0.0f,0.0f,2.0f);
                                 gluDisk(quadratic,0.0f,0.5f,32,32);		    // Draw A Disc (CD Shape)
                                 
//*******************************
///Rotar com Mouse apostila 48
//*******************************
                           glPopMatrix();

                     glPopMatrix();
                                          
               glPopMatrix();

               glPushMatrix(); // Caixa de engrenagens na Base
                     glColor3f (1.0, 1.0, 0.0);
                     glTranslatef (-0.8, 0, 0);
                     glScalef (0.8, 0.5, 0.5);
                     if (Solido==1)
                        {glutSolidCube (1.0);}
                     else
                        {glutWireCube (1.0);}
               glPopMatrix();

               glPushMatrix(); // Caixa de engrenagens na Frente
                     glColor3f (1.0, 1.0, 0.0);
                     glTranslatef (0.8, 0, 0);
                     glScalef (0.8, 0.5, 0.5);
                     if (Solido==1)
                        {glutSolidCube (1.0);}
                     else
                        {glutWireCube (1.0);}
               glPopMatrix();
         glColor3f (1.0, 1.0, 1.0);
         glPopMatrix();

//****************************  Mano *******************************************
         glTranslatef (1.7, 0.0, 0.0);
         glRotatef ((GLfloat) Mano, 0.0, 0.0, 1.0);
         glPushMatrix();
               //glTranslatef (-0.5, 0.0, 0.0);
               glColor3f (0.0, 0.0, 0.0);
               glPushMatrix();
//                     glColor4f(1.0, 1.0, 1.0, 0.75);
                     quadratic=gluNewQuadric();
                     glTranslatef(0.0f,0.0f,-0.32f);
                     gluCylinder(quadratic,0.2f,0.2f,0.05f,20,15);	// desenha o Cilindro con tampas Direita
                     gluDisk(quadratic,0.0f,0.2f,20,20);
                     glTranslatef(0.0f,0.0f,0.05f);
                     gluDisk(quadratic,0.0f,0.2f,20,20);

                     glTranslatef(0.0f,0.0f,0.53f);
                     gluCylinder(quadratic,0.2f,0.2f,0.05f,20,15);	// desenha o Cilindro con tampas Izquierda
                     gluDisk(quadratic,0.0f,0.2f,20,20);
                     glTranslatef(0.0f,0.0f,0.05f);
                     gluDisk(quadratic,0.0f,0.2f,20,20);
               glPopMatrix();

               glPushMatrix();
                     glTranslatef (0.4, 0.0, 0.0);  // Desenha a caixa de engrenagens  do atuador
                     glPushMatrix();
                           glColor3f (1.0, 1.0, 0.0);
                           glRotatef (90.0, 1.0, 0.0, 0.0);
                           glTranslatef (-0.25, 0.0, -0.15);  // Desenha a capa Superior da caixa de engrenagens  do atuador
                           glBegin(GL_TRIANGLE_STRIP);	
                                glVertex3f( 0.0f, -0.3f, -0.01f ); //vertex 1
                                glVertex3f( 0.0f, 0.3f, -0.01f ); //vertex 2
                                glVertex3f( 0.5f, -0.1f, -0.01f ); //vertex 3
                                glVertex3f( 0.5f, 0.1f, -0.01f ); //vertex 4
                           glEnd();

                           glTranslatef (0.0, 0.0, 0.31);  // Desenha a capa inferior da caixa de engrenagens  do atuador
                           glBegin(GL_TRIANGLE_STRIP);	
                                glVertex3f( 0.0f, -0.3f, -0.01f ); //vertex 1
                                glVertex3f( 0.0f, 0.3f, -0.01f ); //vertex 2
                                glVertex3f( 0.5f, -0.1f, -0.01f ); //vertex 3
                                glVertex3f( 0.5f, 0.1f, -0.01f ); //vertex 4
                           glEnd();

                           glColor3f (0.0, 0.0, 0.0);
                     glPopMatrix();
                     
                     glScalef (0.5, 0.3, 0.6);
                     if (Solido==1)
                        {glutSolidCube (1);}
                     else
                        {glutWireCube (1);}

                     glPushMatrix();
                           glPushMatrix();
                                 glTranslatef (1.0, 0.0, (0.6-Pinza));
                                 glScalef (1, 0.4, 0.15);
                                 if (Solido==1)
                                    {glutSolidCube (1);}
                                 else
                                    {glutWireCube (1);}
                           glPopMatrix();
                           
                           glPushMatrix();
                                 glTranslatef (1.0, 0.0, (-0.6+Pinza));
                                 glScalef (1, 0.4, 0.15);
                                 if (Solido==1)
                                    {glutSolidCube (1);}
                                 else
                                    {glutWireCube (1);}
                           glPopMatrix();
                           
                     glPopMatrix();
               glPopMatrix();
         glPopMatrix();// Fechamento da Função Mano
         
    glPopMatrix(); // Fechamento da Função Base
    
glPopMatrix(); // Fechamento da Função BrazoRobot
}
