#include <iostream>
#include<GL/glut.h>

using namespace std;

GLfloat angle = 0.0;
GLfloat v[6] = {0.0,0.0,10.0,0.0,5.0,8.66666};

void triangle(void)
{
    glPushMatrix();
    glTranslatef((GLfloat)(v[0]+v[2]+v[4]) / 3,(GLfloat)(v[1]+v[3]+v[5]) / 3 ,0);
    glRotatef(angle,0,0,1);
    glTranslatef((GLfloat) -(v[0]+v[2]+v[4]) / 3,(GLfloat) -(v[1]+v[3]+v[5]) / 3 ,0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(v[0],v[1]);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(v[2],v[3]);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(v[4],v[5]);
    glEnd();
    glPopMatrix();
}

void init () {
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);

}

void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    triangle();
    glPushMatrix();
    glRotatef(120,0,0,1);

    triangle();
    glRotatef(120,0,0,1);
    triangle();

    glPopMatrix();

    glFlush();
}

void reshape (int w,int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


void mouse (int bottom,int state,int x,int y){
    switch(bottom) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                angle -= 5;
            glutPostRedisplay();
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                angle += 5;
            glutPostRedisplay();
            break;
        default:
        break;
    }

}


int main(int argc,char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250,250);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Spin Tri");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;

}

