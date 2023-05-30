/* 
 * Beschiu Dana 221/2 - Robot
 */

#include "glos.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <math.h>

GLfloat pozSursa[] = {150, 200, -50.0, 1 };
GLUquadricObj* quadric;
int alfa = 0, beta1 = 0, beta2 = 0, beta3 = 0, gama = 0;
int umbra = 0;

void calcCoeficientiPlan(float P[3][3], float coef[4])
{ 
	float v1[3], v2[3];
	float length;
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;
//calculeazã doi vectori din trei puncte
	v1[x] = P[0][x]- P[1][x];
	v1[y] = P[0][y]- P[1][y];
	v1[z] = P[0][z]- P[1][z];

	v2[x] = P[1][x]- P[2][x];
	v2[y] = P[1][y]- P[2][y];
	v2[z] = P[1][z]- P[2][z];

//se cacluleazã produsul vectorial al celor doi vectori
// care reprezintã un al treilea vector perpendicular pe plan 
// ale cãrui componente sunt chiar coeficienþii A, B, C din ecuaþia planului
	coef[x] = v1[y]*v2[z] - v1[z]*v2[y];
	coef[y] = v1[z]*v2[x] - v1[x]*v2[z];
	coef[z] = v1[x]*v2[y] - v1[y]*v2[x];
//normalizeazã vectorul
	length = (float)sqrt((coef[x]*coef[x])+(coef[y]*coef[y])+(coef[z]*coef[z]));
	coef[x] /= length;
	coef[y] /= length;
	coef[z] /= length;
}
//creazã matricea care dã umbra cunoscându-se coeficienþii planului ºi 
//poziþia sursei. În mat se salveazã matricea.

void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4],
				  GLfloat mat[4][4])
{

    umbra = 1;
	GLfloat coefPlan[4];
	GLfloat temp;
//determinã coeficienþii planului
	calcCoeficientiPlan(puncte, coefPlan);
//determinã si pe D
	coefPlan[3] = -(
				(coefPlan[0]*puncte[2][0])+
				(coefPlan[1]*puncte[2][1])+	
				(coefPlan[2]*puncte[2][2]));
//temp=A*xL+B*yL+C*zL+D*w
	temp = coefPlan[0]*pozSursa[0]+
				coefPlan[1]*pozSursa[1]+
				coefPlan[2]*pozSursa[2]+
				coefPlan[3]*pozSursa[3];
//prima coloanã
	mat[0][0] = temp - pozSursa[0] * coefPlan[0];
	mat[1][0] = 0.0f - pozSursa[0] * coefPlan[1];
	mat[2][0] = 0.0f - pozSursa[0] * coefPlan[2];
	mat[3][0] = 0.0f - pozSursa[0] * coefPlan[3];
//a doua coloana
	mat[0][1] = 0.0f - pozSursa[1] * coefPlan[0];
	mat[1][1] = temp - pozSursa[1] * coefPlan[1];
	mat[2][1] = 0.0f - pozSursa[1] * coefPlan[2];
	mat[3][1] = 0.0f - pozSursa[1] * coefPlan[3];
//a treia coloana
	mat[0][2] = 0.0f - pozSursa[2] * coefPlan[0];
	mat[1][2] = 0.0f - pozSursa[2] * coefPlan[1];
	mat[2][2] = temp - pozSursa[2] * coefPlan[2];
	mat[3][2] = 0.0f - pozSursa[2] * coefPlan[3];
//a patra coloana
	mat[0][3] = 0.0f - pozSursa[3] * coefPlan[0];
	mat[1][3] = 0.0f - pozSursa[3] * coefPlan[1];
	mat[2][3] = 0.0f - pozSursa[3] * coefPlan[2];
	mat[3][3] = temp - pozSursa[3] * coefPlan[3];
}

void plan(void)
{
	glBegin(GL_QUADS);
		glVertex3f(1000.0f, -165.0f, -500.0f);
		glVertex3f(-1000.0f, -165.0f, -500.0f);
		glVertex3f(-1000.0f, -165.0f, 500.0f);
		glVertex3f(1000.0f, -165.0f, 500.0f);
	glEnd();
}

void CALLBACK rotate_right_head(void)
{
    alfa = (alfa + 5) % 360;
}

void CALLBACK rotate_left_head(void)
{
    alfa = (alfa - 5) % 360;
}

void CALLBACK rotate_front_hands(void)
{
    gama = (gama - 5) % 60;
}

void CALLBACK rotate_back_hands(void)
{
    gama = (gama + 5) % 60;
}



void CALLBACK rotateX_right_robot(void)
{
    beta1 = (beta1 + 5) % 360;
}

void CALLBACK rotateY_right_robot(void)
{
    beta2 = (beta2 + 5) % 360;
}

void CALLBACK rotateY_left_robot(void)
{
    beta2 = (beta2 - 5) % 360;
}

void CALLBACK rotateZ_right_robot(void)
{
    beta3 = (beta3 + 5) % 360;
}

void CALLBACK body()
{
    glPushMatrix();
    if(umbra==0)
       glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0, 10, 0);
    auxSolidBox(70, 80, 50);
    glTranslatef(0, -42, 0);
    if(umbra==0)
      glColor3f(0.1, 0.1, 0);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidBox(56, 4, 45);
    glPopMatrix();
}

void CALLBACK neck()
{
    glPushMatrix();
    if(umbra==0)
      glColor3f(0.1, 0.1, 0);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0, 54, 0);
    auxSolidBox(20, 8, 20);
    glPopMatrix();
}

void CALLBACK right_ear()
{
    glPushMatrix();
    if(umbra==0)
       glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(24, 78, 0);
    auxSolidBox(8, 20, 20);
    if(umbra==0)
      glColor3f(1, 0, 1);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(7, 0, 0);
    auxSolidBox(6, 15, 15);
    if(umbra==0)
      glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(5, 0, 0);
    auxSolidBox(4, 10, 10);
    glPopMatrix();
}

void CALLBACK left_ear()
{
    glPushMatrix();
    if(umbra==0)
      glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(-24, 78, 0);
    auxSolidBox(8, 20, 20);
    if(umbra==0)
      glColor3f(1, 0, 1);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(-7, 0, 0);
    auxSolidBox(6, 15, 15);
    if(umbra==0)
      glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(-5, 0, 0);
    auxSolidBox(4, 10, 10);
    glPopMatrix();
}

void CALLBACK hat()
{
    glPushMatrix();
    if (umbra == 0)
       glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0, 101, 0);
    auxSolidBox(30, 6, 30);
    glPushMatrix();
    glRotatef(-25, 0, 0, 1);
    glTranslatef(0, 21, 7);
    auxSolidCylinder(1, 20);
    glPopMatrix();
    glPushMatrix();
    glRotatef(25, 0, 0, 1);
    glTranslatef(0, 21, 7);
    auxSolidCylinder(1, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(10, 21, 7);
    auxSolidSphere(4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-10, 21, 7);
    auxSolidSphere(4);
    glPopMatrix();
    glPopMatrix();
}

void CALLBACK head()
{
    quadric = gluNewQuadric();
    glPushMatrix();
    if (umbra == 0)
       glColor3f(1, 0.5, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0, 78, 0);
    auxSolidBox(40, 40, 30);
    if (umbra == 0)
       glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslatef(-10, 5, 16);
    gluDisk(quadric, 0, 6, 10, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(9, 5, 16);
    gluDisk(quadric, 0, 6, 10, 1);
    glPopMatrix();
    if (umbra == 0)
       glColor3f(1, 0, 1);
    else
        glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslatef(-10, 5, 17);
    gluDisk(quadric, 0, 4, 10, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(9, 5, 17);
    gluDisk(quadric, 0, 4, 10, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(9, 5, 17);
    gluDisk(quadric, 0, 4, 10, 1);
    glPopMatrix();
    if (umbra == 0)
       glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0, -11, 16);
    auxSolidBox(20, 4, 0);
    glPopMatrix();
}

void CALLBACK right_arm()
{
    glPushMatrix();
    if (umbra == 0)
       glColor3f(0.1, 0.1, 0);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(38, 35, 0);
    glPushMatrix();
    auxSolidBox(7, 14, 14);
    glPopMatrix();
    if (umbra == 0)
       glColor3f(1, 0.5, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslatef(8, -14, 0);
    auxSolidBox(10, 50, 20);
    glPopMatrix();
    glTranslatef(8, -51, 0);
    glRotatef(-15, 1, 0, 0);
    glPushMatrix();
    glTranslatef(0, 35, 0);
    glRotatef(gama, 1, 0, 0);
    glTranslatef(0, -35, 0);
    auxSolidBox(10, 50, 13);
    glPopMatrix();
    glPopMatrix();
}

void CALLBACK left_arm()
{
    glPushMatrix();
    if (umbra == 0)
       glColor3f(0.1, 0.1, 0);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(-38, 35, 0);
    glPushMatrix();
    auxSolidBox(7, 14, 14);
    glPopMatrix();
    if (umbra == 0)
       glColor3f(1, 0.5, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslatef(-8, -14, 0);
    auxSolidBox(10, 50, 20);
    glPopMatrix();
    glTranslatef(-8, -51, 0);
    glRotatef(-15, 1, 0, 0);
    glPushMatrix();
    glTranslatef(0, 35, 0);
    glRotatef(gama, 1, 0, 0);
    glTranslatef(0, -35, 0);
    auxSolidBox(10, 50, 13);
    glPopMatrix();
    glPopMatrix();
}

void CALLBACK right_leg()
{
    glPushMatrix();
    if (umbra == 0)
       glColor3f(1, 0.5, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(18, -41, 0);
    auxSolidBox(18, 15, 18);
    glTranslatef(0, -8, 0);
    if (umbra == 0)
       glColor3f(0.1, 0.1, 0);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidCylinder(5, 30);
    glTranslatef(0, -36, 0);
    if (umbra == 0)
       glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidBox(18, 15, 18);
    glTranslatef(0, -13, 0);
    if (umbra == 0)
       glColor3f(1, 0, 1);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidBox(24, 10, 24);
    glTranslatef(0, -8, 0);
    if (umbra == 0)
       glColor3f(1, 0.5, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidBox(28, 5, 28);
    glPopMatrix();
}

void CALLBACK left_leg()
{
    glPushMatrix();
    if (umbra == 0)
       glColor3f(1, 0.5, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    glTranslatef(-18, -41, 0);
    auxSolidBox(18, 15, 18);
    glTranslatef(0, -8, 0);
    if (umbra == 0)
       glColor3f(0.1, 0.1, 0);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidCylinder(5, 30);
    glTranslatef(0, -36, 0);
    if (umbra == 0)
       glColor3f(0.5, 0, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidBox(18, 15, 18);
    glTranslatef(0, -13, 0);
    if (umbra == 0)
        glColor3f(1, 0, 1);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidBox(24, 10, 24);
    glTranslatef(0, -8, 0);
    if (umbra == 0)
       glColor3f(1, 0.5, 0.5);
    else
        glColor3f(0.2, 0.2, 0.2);
    auxSolidBox(28, 5, 28);
    glPopMatrix();
}


void CALLBACK create_robot()
{
	glPushMatrix();
	glRotatef(beta1, 1, 0, 0);
	glRotatef(beta2, 0, 1, 0);
	glRotatef(beta3, 0, 0, 1);
	body();
	neck();
	glPushMatrix();
	glRotatef(alfa, 0, 1, 0);
	head();
	right_ear();
	left_ear();
	hat();
	glPopMatrix();
	right_arm();
	left_arm();
	right_leg();
	left_leg();
	glPopMatrix();
}

void myinit(void)
{
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    /*  rflectanta speculara si exponentul de reflexie speculara
    nu sunt la valorile implicite (0.0)   */
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 128.0 };
    // valori implicite pentru intensitatea sursei LIGHT0
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    /*  pozitia sursei nu are valori implicite */
    //GLfloat light_position[] = { 50.0, 50.0, 50.0, 1.0 };

    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	//permite urmãrirea culorilor
	glEnable(GL_COLOR_MATERIAL);
	//seteazã proprietãþile de material pentru a urma valorile glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//seteazã sursa		
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pozSursa);
//seteazã materialul	    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glClearColor(0.5,0.5,1,1);
	glEnable(GL_DEPTH_TEST);//ascunderea suprafeþelor
}

void CALLBACK display(void)
{	
    GLfloat matUmbra[4][4];
//oricare trei puncte din plan în sens CCW
	GLfloat puncte[3][3] = {{-50.0f, -164.0f, -50.0f},
							{-50.0, -164.0f, 50.0},
							{50.0f, -164.0f, 50.0f}};
//sterge ecranul
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//determinã matricea pentru calcularea umbrei	
//salveaza starea matricei de modelare-vizualizare si reprezintã cubul rotit
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, pozSursa);
    create_robot();
	glPopMatrix(); //reface matricea initialã
//deseneazã umbra
//mai întâi se dezactiveazã iluminarea si se salveazã starea matricei de proiectie
    MatriceUmbra(puncte, pozSursa, matUmbra);
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glPushMatrix();
//apoi se înmulteste matricea curentã cu matricea de umbrire
	glMultMatrixf((GLfloat*)matUmbra);
//si cu cea de rotaþie
//se deseneazã cubul-umbrã cu gri
    create_robot();
    umbra = 0;
	glPopMatrix(); //reface matricea de proiecþie la normal

//deseneazã sursa de luminã ca o sferã micã galbenã în poziþia realã
	glPushMatrix();
	glTranslatef(pozSursa[0], pozSursa[1], pozSursa[2]);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidSphere(10);
	glPopMatrix();

//deseneazã planul
	glColor3f(0.5, 1, 0.5);
    glPushMatrix();
    //glScalef(2, 2, 2);
	plan();
    glPopMatrix();

//restaureazã starea variabilelor de iluminare
	glPopAttrib();
	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    glOrtho(-200.0, 200.0, -200.0*(GLfloat)h/(GLfloat)w, 
        200.0*(GLfloat)h/(GLfloat)w, -200.0, 200.0);
    else
    glOrtho(-200.0*(GLfloat)w/(GLfloat)h, 
        200.0*(GLfloat)w/(GLfloat)h, -200.0, 200.0, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glRotatef(-30, -1.0f, 1.0f, 1.0f); //transformarea de vizualizare
}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_DEPTH16 | AUX_RGB);
    auxInitPosition (10, 10, 400, 400);
    auxInitWindow ("Proiect Robot");
    myinit();

    auxKeyFunc(AUX_RIGHT, rotate_right_head);
    auxKeyFunc(AUX_LEFT, rotate_left_head);

    auxKeyFunc(AUX_UP, rotateY_right_robot);
    auxKeyFunc(AUX_DOWN, rotateY_left_robot);

    auxKeyFunc(AUX_x, rotateX_right_robot);

    auxKeyFunc(AUX_z, rotateZ_right_robot);

    auxKeyFunc(AUX_1, rotate_front_hands);
    auxKeyFunc(AUX_2, rotate_back_hands);

    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}
