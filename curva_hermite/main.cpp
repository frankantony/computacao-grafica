#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>

using namespace std;

unsigned int numero_pontos = 4; /// Numero de pontos definidos na curva

float geometria[4][3] =
{
    { 10,10,0 }, //	Ponto 1
    {-10,5,0 },	 //	Ponto 2
    { 5,-5,0  }, //	Tangente 1
    { 5,-10,0  } //	Tangente 2
};

void exibe()
{

    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // Seta as posicoes da camera
    gluLookAt(	1,10,30,	// posicao do olho
                0,5,0,	//	ponto de mira
                0,1,0);	//	Direção ascendente

    glColor3f(0.5,0.5,1);
    glBegin(GL_LINE_STRIP);

    // Use o valor do tempo paramétrico de 0 a 1.
    for(int i=0; i!=numero_pontos; ++i)
    {

        float t = (float)i/(numero_pontos-1);

        // Calcular funções de mistura
        float b0 =  2*t*t*t - 3*t*t + 1;
        float b1 = -2*t*t*t + 3*t*t;
        float b2 = t*t*t - 2*t*t + t;
        float b3 = t*t*t - t*t;

        // Calcule o x, y e z do ponto da curva
        float x = b0*geometria[0][0] +
                  b1*geometria[1][0] +
                  b2*geometria[2][0] +
                  b3*geometria[3][0] ;

        float y = b0*geometria[0][1] +
                  b1*geometria[1][1] +
                  b2*geometria[2][1] +
                  b3*geometria[3][1] ;

        float z = b0*geometria[0][2] +
                  b1*geometria[1][2] +
                  b2*geometria[2][2] +
                  b3*geometria[3][2] ;

        glVertex3f( x,y,z );
    }
    glEnd();


    glColor3f(0,1,0.5);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex3fv(geometria[0]);
    glVertex3fv(geometria[1]);
    glEnd();

    glColor3f(0.5,1,0.5);
    glPushMatrix();
    glTranslatef(geometria[0][0],geometria[0][1],geometria[0][2]);
    glBegin(GL_LINES);
    glVertex3f( 0,0,0 );
    glVertex3fv( geometria[2] );
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(geometria[1][0],geometria[1][1],geometria[1][2]);
    glBegin(GL_LINES);
    glVertex3f( 0,0,0 );
    glVertex3fv( geometria[3] );
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void mouse (int botao, int estado, int x, int y)
{
    if ((botao == GLUT_LEFT_BUTTON) && (estado == GLUT_DOWN))
    {
        numero_pontos++;
        glutPostRedisplay();
    }

    else if ((botao == GLUT_RIGHT_BUTTON) && (estado == GLUT_DOWN))
    {
        if (numero_pontos >= 5)
        {
            numero_pontos--;
        }
        glutPostRedisplay();
    }
}

void reshape (int w, int h)
{
	if (h==0)
		h=1;

	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45,(float)w/h,0.1,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutCreateWindow("Desenhando uma Curva de Hermite");
    glutDisplayFunc(exibe);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
