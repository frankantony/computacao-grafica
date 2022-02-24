#include <iostream>
#include<GL/glut.h>
#include<vector>

using namespace std;

vector<float> points;
float vet[] = {0.0,0.0,10.0,0.0,5,8.666};


void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    glMatrixMode(GL_POSITION);
    gluOrtho2D(-1.0,11.0,-1.0,11.0);
    glMatrixMode(GL_MODELVIEW);
}

void subdivide(float ax,float ay,float bx,float by,float cx,float cy, int k)
{

    if(k > 0)
    {
        float acX = (ax+cx)/2;
        float abX = (ax+bx)/2;
        float bcX = (bx+cx)/2;

        float abY = (ay+by)/2;
        float acY = (ay+cy)/2;
        float bcY = (by+cy)/2;

        subdivide(ax,ay,acX,acY,abX,abY,k-1);
        subdivide(acX,acY,cx,cy,bcX,bcY,k-1);
        subdivide(abX,abY,bcX,bcY,bx,by,k-1);

    }
    else
    {
        points.push_back(ax);
        points.push_back(ay);
        points.push_back(bx);
        points.push_back(by);
        points.push_back(cx);
        points.push_back(cy);
    }
}

void display()
{
    points.clear();
    subdivide(vet[0],vet[1],vet[2],vet[3],vet[4],vet[5],5);
    glBegin(GL_TRIANGLES);

    for(uint i = 0; i < points.size(); i +=2)
        glVertex2f(points[i],points[i+1]);

    glEnd();

    glFlush();
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Window Title");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}

