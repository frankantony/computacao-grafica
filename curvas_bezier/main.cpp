#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define LARGURA 500
#define ALTURA 500

unsigned int numero_pontos = 4; /// Numero de pontos definidos na curva

float p[4][2] =
{
    { -1.0f,0.0f},// Ponto 1
    {-0.5f,-0.5f},//Ponto 2
    { 0.5f,0.5f}, // Ponto 3
    {1.0f,0.0f} //	Ponto 4
};

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

float fatorial(int n)
{
    int i;
    float f = 1.0f;
    for (i = 2; i <= n; i++)
        f *= i;
    return f;
}

float combinacao(int a, int b)
{
    return fatorial(b)/(fatorial(a)*fatorial(b-a));
}


void exibe(void)
{
    GLint i;
    GLfloat t,x,y;
    glClear(GL_COLOR_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < 4; i++)
        glVertex2f(p[i][0],p[i][1]);
    glEnd();

    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i!=numero_pontos; ++i)
    {
        float t = (float)i/(numero_pontos-1);
        x = 0.0f;
        y = 0.0f;
        for (int j=0; j<4; j++)
        {
            x += combinacao(j,3)*pow(t,j)*pow(1.0f-t,3-j)*p[j][0];
            y += combinacao(j,3)*pow(t,j)*pow(1.0f-t,3-j)*p[j][1];
        }
        glVertex2f(x,y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ALTURA,LARGURA);
    glutInitWindowPosition(20,20);
    glutCreateWindow("Desenhando uma curva de Bézier");
    glutDisplayFunc(exibe);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
