#include <iostream>
#include<GL/glut.h>
#include<algorithm>
#include<GL/gl.h>
#include<vector>
#include<math.h>

using namespace std;

GLfloat angleX = 0.0f,angleZ = 0.0f;

void spkeyboard(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_UP:
        angleX += 10;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        angleX -= 10;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        angleZ += 5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        angleZ -= 5;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}


void myinit()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-8.0f,8.0f,-8.0f,8.0f);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-8.0f, 8.0f, -8.0f,8.0);

}

void drawHalfSphere (int scaley, int scalex, GLfloat r,GLfloat valor,GLfloat valor1)
{
    glPushMatrix();
    glTranslatef(valor,0.5,1);
    glRotatef(valor1,1.0,0.0,0.0);
    if (valor1 != 0)
    {
        glTranslatef(0.0f,-1.,0.0);
    }

    int i, j;
    GLfloat v [scalex*scaley] [3];

    for (i = 0; i <scalex; ++ i)
    {
        for (j = 0; j <scaley; ++ j)
        {
            v [i * 24 + j] [0] = r * cos (j * 2 * M_PI / 24) * cos (i * M_PI / (2 * 24));
            v [i * 24 + j] [1] = r * sin (i * M_PI / (2 * 24));
            v [i * 24 + j] [2] = r * sin (j * 2 * M_PI / 24) * cos (i * M_PI / (2 * 24));
        }
    }

    glBegin (GL_QUADS);
    for (i = 0; i <scalex-1; ++ i)
    {
        for (j = 0; j <scaley; ++ j)
        {
            glVertex3fv (v [i * 24 + j]);
            glVertex3fv (v [i * 24 + (j + 1)% 24]);
            glVertex3fv (v [(i + 1) * 24 + (j + 1)% 24]);
            glVertex3fv (v [(i + 1) * 24 + j]);
        }
    }
    glEnd ();
    glPopMatrix();
}


void paralelepipedo (GLfloat v,int flag)
{

    glPushMatrix();
    glRotatef(v,0.0,0.0,1.0);
    if (v != 0 && !flag)
    {
        glScalef(.5,1.1,1);
        glTranslatef(4.0f,-.5f,0.0f);
    }
    if (flag == 1)
    {
        glScalef(.5,1.1,1);
        glTranslatef(4.0f,.7,0.0f);
    }
    glBegin(GL_QUADS);
    // Face posterior
    glNormal3f(0.0, 0.0, 1.0);	// Normal da face
    glVertex3f(5.0, .5, .5);
    glVertex3f(-5.0, .5, .5);
    glVertex3f(-5.0, -.5, .5);
    glVertex3f(5.0, -.5, .5);

    // Face frontal
    glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
    glVertex3f(5.0, .5, -.5);
    glVertex3f(5.0, -.5, -.5);
    glVertex3f(-5.0, -.5, -.5);
    glVertex3f(-5.0, .5, -.5);

    // Face lateral esquerda
    glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
    glVertex3f(-5.0, .5, 0.5);
    glVertex3f(-5.0, .5, -0.5);
    glVertex3f(-5.0, -.5, -0.5);
    glVertex3f(-5.0, -0.5, .5);

    // Face lateral direita
    glNormal3f(1.0, 0.0, 0.0);	// Normal da face
    glVertex3f(5.0, .5, .5);
    glVertex3f(5.0, -.5, .5);
    glVertex3f(5.0, -.5, -.5);
    glVertex3f(5.0, .5, -.5);

    // Face superior
    glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
    glVertex3f(-5.0, .5, -.5);
    glVertex3f(-5.0, .5, .5);
    glVertex3f(5.0, .5, .5);
    glVertex3f(5.0, .5, -.5);

    // Face inferior
    glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
    glVertex3f(-5.0, -.5, -.5);
    glVertex3f(5.0, -.5, -.5);
    glVertex3f(5.0, -.5, .5);
    glVertex3f(-5.0, -.5, .5);

    glEnd();
    glPopMatrix();
}


void palacio ()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0,0.0);
    glPushMatrix();

    //criacao das semiesferas..

    glRotatef(angleX,1.0f,0.0f,0.0f);
    glRotatef(angleZ,0.0f,1.0f,0.0f);

    drawHalfSphere(24,24,1,2.8,180);
    drawHalfSphere(24,24,1,-2.8,0);

    //cracao dos paralelepipedos...

    paralelepipedo(0,0);
    paralelepipedo(90,0);
    paralelepipedo(90,1);

    glEnd();



    glPopMatrix();



    glFlush();
}


int main(int argc,char**argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("PALÁCIO DO PLANALTO");
    myinit();
    glutDisplayFunc(palacio);
    glutReshapeFunc(reshape);
    glutSpecialFunc(spkeyboard);

    glutMainLoop();
    return 0;
}

