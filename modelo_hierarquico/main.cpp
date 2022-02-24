#include <GL/glut.h>

//Declaração de variáveis
float angle0=0, angle1=0 , angle2=0 ,vy=-1, ty=1;

//Cria um ponteiro para a es
GLUquadricObj  *planet;

void exibe(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    ///define a base do braco
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex2f(-12,-2);
    glVertex2f(-12,0);
    glVertex2f(12,0);
    glVertex2f(12,-2);
    glEnd();

    ///objeto da primeira de junta.
    glPushMatrix();
    glRotatef(angle0, 0.0, 0.0, 1.0);
    glColor3f(1.0,1.0,0.0);
    ///define a junta
    gluDisk(planet, 0, 2, 16, 1);
    glBegin(GL_QUADS);
    glVertex2f(0,-0.5);
    glVertex2f(0,0.5);
    glVertex2f(6,0.5);
    glVertex2f(6,-0.5);
    glEnd();

    ///objeto da segunda junta

    glTranslatef(6.0, 0.0, 0.0);
    glRotatef(angle1, 0.0, 0.0, 1.0);
    glColor3f(1.0,0.0,0.0);
    gluDisk(planet, 0, 0.8, 16, 1);
    glBegin(GL_QUADS);
    glVertex2f(0,-0.3);
    glVertex2f(0,0.3);
    glVertex2f(3,0.3);
    glVertex2f(3,-0.3);
    glEnd();

    ///objeto da terceira junta

    glTranslatef(3.0, 0.0, 0.0);
    glRotatef(angle2, 0.0, 0.0, 1.0);
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex2f(0,-0.3);
    glVertex2f(0,0.3);
    glVertex2f(2,0.3);
    glVertex2f(2,-0.3);
    glEnd();


    gluDisk(planet, 0, 0.8, 10, 1);
    glTranslatef(1.0, 0.0, 0.0);
    glColor3f(0.0,0.0,1.0);
    ///define o pulso.
    glBegin(GL_QUADS);
    glVertex2f(1,-1);
    glVertex2f(1,1);
    glVertex2f(1.5,1);
    glVertex2f(1.5,-1);
    glEnd();

    ///definicao da mao do robo.

    glBegin(GL_QUADS);
    glVertex2f(1.5,ty-0.5);
    glVertex2f(1.5,ty);
    glVertex2f(3,ty);
    glVertex2f(3,ty-0.5);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(1.5,vy);
    glVertex2f(1.5,vy+0.5);
    glVertex2f(3,vy+0.5);
    glVertex2f(3,vy);
    glEnd();

    glPopMatrix();
    glFlush();
}

void TeclasEspeciais(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        if (vy>=-0.9 & vy<=-0.4) vy=vy-0.1;
        if (ty>=0.4 & ty<=0.9)ty=ty+0.1;
        break;

    case GLUT_KEY_UP:
        if (vy>=-1.1 & vy<=-0.5) vy=vy+0.1;
        if (ty>=0.5 & ty<=1.1)ty=ty-0.1;
        break;

    case GLUT_KEY_HOME:
        angle0=angle0+5.0;
        break;
    case GLUT_KEY_END:
        angle0=angle0-5.0;
        break;

    case GLUT_KEY_PAGE_UP:
        angle1=angle1+7.0;
        break;
    case GLUT_KEY_PAGE_DOWN:
        angle1=angle1-7.0;
        break;
    case GLUT_KEY_LEFT:
        angle2=angle2+9.0;
        break;
    case GLUT_KEY_RIGHT:
        angle2=angle2-9.0;
        break;

    }
    glutPostRedisplay();
}

void Inicializa (void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(-13.0,13.0,-13.0,13.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Modelo Hierarquico");
    planet = gluNewQuadric();
    Inicializa();
    glutDisplayFunc(exibe);
    glutSpecialFunc(TeclasEspeciais);
    glutMainLoop();
}


