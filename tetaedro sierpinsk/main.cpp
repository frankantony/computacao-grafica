#include <iostream>
#include<GL/glut.h>
#include<GL/gl.h>
#include<vector>

using namespace std;

vector<float> points,colors;
int countK = 0,angleZ = 0,angleX = 0;

GLfloat v0[] = {0.0f,0.0f,1.4*1.0f};
GLfloat v1[] = {0.0f,1.4*0.628539f,1.4*(-0.222222f)};
GLfloat v2[] = {1.4*(-0.544331f),1.4*(-0.310427f),1.4*(-0.222222f)};
GLfloat v3[] = {1.4*(0.544331f),1.4*(-0.310427f),1.4*(-0.222222f)};


void subdivide(float v0x,float v0y,float v0z , float v1x , float v1y , float v1z , float v2x, float v2y , float v2z ,  float v3x , float v3y , float v3z
               ,float cv0X , float cv0Y , float cv0Z , float cv1X , float cv1Y , float cv1Z ,float cv2X , float cv2Y , float cv2Z ,float cv3X,float
               cv3Y,float cv3Z, int k)
{

    if(k > 0)
    {
        float v01X = (v0x+v1x)/2;
        float v02X = (v0x+v2x)/2;
        float v12X = (v1x+v2x)/2;

        float v13X = (v1x+v3x)/2;

        float v03X = (v0x+v3x)/2;
        float v23X = (v2x+v3x)/2;

        float v01Y = (v0y+v1y)/2;
        float v02Y = (v0y+v2y)/2;
        float v13Y = (v1y+v3y)/2;
        float v03Y = (v0y+v3y)/2;
        float v23Y = (v2y+v3y)/2;
        float v12Z = (v1z+v2z)/2;
        float v12Y = (v1y+v2y)/2;

        float v01Z = (v0z+v1z)/2;
        float v02Z = (v0z+v2z)/2;
        float v13Z = (v1z+v3z)/2;
        float v03Z = (v0z+v3z)/2;
        float v23Z = (v2z+v3z)/2;

subdivide(v0x,v0y,v0z,v01X,v01Y,v01Z,v02X,v02Y,v02Z,v03X,v03Y,v03Z,cv0X,cv0Y,cv0Z,(cv0X+cv1X)/2,(cv0Y+cv1Y)/2,(cv0Z+cv1Z)/2,(cv0X+cv2X)/2,(cv0Y+cv2Y)/2,(cv0Z+cv2Z)/2,(cv0X+cv3X)/2,(cv0Y+cv3Y)/2,(cv0Z+cv3Z)/2,k-1);
subdivide(v02X,v02Y,v02Z,v12X,v12Y,v12Z,v2x,v2y,v2z,v23X,v23Y,v23Z,(cv0X+cv1X)/2,(cv0Y+cv1Y)/2,(cv0Z+cv1Z)/2,cv1X,cv1Y,cv1Z,(cv1X+cv2X)/2,(cv1Y+cv2Y)/2,(cv1Z+cv2Z)/2 ,(cv1X+cv3X)/2,(cv1Y+cv3Y)/2,(cv1Z+cv3Z)/2,k-1);

subdivide(v01X,v01Y,v01Z,v1x,v1y,v1z,v12X,v12Y,v12Z,v13X,v13Y,v13Z,(cv0X+cv2X)/2,(cv0Y+cv2Y)/2,(cv0Z+cv2Z)/2,(cv1X+cv2X)/2,(cv1Y+cv2Y)/2,(cv1Z+cv2Z)/2,cv2X,cv2Y,cv2Z,(cv2X+cv3X)/2,(cv2Y+cv3Y)/2,(cv2Z+cv3Z)/2, k-1);
subdivide(v03X,v03Y,v03Z,v13X,v13Y,v13Z,v23X,v23Y,v23Z,v3x,v3y,v3z,(cv0X+cv3X)/2,(cv0Y+cv3Y)/2,(cv0Z+cv3Z)/2,(cv1X+cv3X)/2,(cv1Y+cv3Y)/2,(cv1Z+cv3Z)/2,(cv2X+cv3X)/2,(cv2Y+cv3Y)/2,(cv2Z+cv3Z)/2, cv3X,cv3Y,cv3Z,k-1);

    }
    else
    {
//v0 , v1 , v2;

        points.push_back(v0x);
        points.push_back(v0y);
        points.push_back(v0z);

        colors.push_back(cv0X);
        colors.push_back(cv0Y);
        colors.push_back(cv0Z);


        points.push_back(v1x);
        points.push_back(v1y);
        points.push_back(v1z);

        colors.push_back(cv1X);
        colors.push_back(cv1Y);
        colors.push_back(cv1Z);


        points.push_back(v2x);
        points.push_back(v2y);
        points.push_back(v2z);

        colors.push_back(cv2X);
        colors.push_back(cv2Y);
        colors.push_back(cv2Z);


////v0 , v2 , v3 .

        points.push_back(v0x);
        points.push_back(v0y);
        points.push_back(v0z);

        colors.push_back(cv0X);
        colors.push_back(cv0Y);
        colors.push_back(cv0Z);

        points.push_back(v2x);
        points.push_back(v2y);
        points.push_back(v2z);

        colors.push_back(cv2X);
        colors.push_back(cv2Y);
        colors.push_back(cv2Z);

        points.push_back(v3x);
        points.push_back(v3y);
        points.push_back(v3z);

        colors.push_back(cv3X);
        colors.push_back(cv3Y);
        colors.push_back(cv3Z);
//
////v0 , v1 , v3;

        points.push_back(v0x);
        points.push_back(v0y);
        points.push_back(v0z);

        colors.push_back(cv0X);
        colors.push_back(cv0Y);
        colors.push_back(cv0Z);

        points.push_back(v1x);
        points.push_back(v1y);
        points.push_back(v1z);

        colors.push_back(cv1X);
        colors.push_back(cv1Y);
        colors.push_back(cv1Z);

        points.push_back(v3x);
        points.push_back(v3y);
        points.push_back(v3z);

        colors.push_back(cv3X);
        colors.push_back(cv3Y);
        colors.push_back(cv3Z);

//
//// v3,v2,v1;
//

        points.push_back(v3x);
        points.push_back(v3y);
        points.push_back(v3z);

        colors.push_back(cv3X);
        colors.push_back(cv3Y);
        colors.push_back(cv3Z);
//
        points.push_back(v2x);
        points.push_back(v2y);
        points.push_back(v2z);
//
        colors.push_back(cv2X);
        colors.push_back(cv2Y);
        colors.push_back(cv2Z);

        points.push_back(v1x);
        points.push_back(v1y);
        points.push_back(v1z);

        colors.push_back(cv1X);
        colors.push_back(cv1Y);
        colors.push_back(cv1Z);

    }

}


void mouse (int bottom,int state,int x,int y)
{
    switch(bottom)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            countK += 1;
        glutPostRedisplay();
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            countK =  (countK == 0) ? 0 : countK-1;
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
    gluOrtho2D(-1.0,11.0,-1.0,11.0);
    glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei width, GLsizei height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 11.0, -1.0, 11.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void spkeyboard(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_RIGHT:
        angleZ += 5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        angleZ -= 5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
            angleX += 5;
            glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
            angleX -= 5;
        glutPostRedisplay();
    break;
    default:
        break;
    }
}


void tetaedro ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(angleX,1.0f,0.0f,0.0f);
    glRotatef(angleZ,0.0f,0.0f,1.0f);

    points.clear();
    colors.clear();
    subdivide(v0[0],v0[1],v0[2],v1[0],v1[1],v1[2],v2[0],v2[1],v2[2],v3[0],v3[1],v3[2],1,1,1,1,0,0,0,1,0,0,0,1,countK);
    glBegin(GL_TRIANGLES);
    int p = 0;
    for(int i = 0; i < points.size(); i +=3)
    {
        glColor3f(colors[p++],colors[p++],colors[p++]);
        glVertex3f(points[i],points[i+1],points[i+2]);

    }

    glEnd();
    glFlush();
    glPopMatrix();
}


int main(int argc,char**argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("TETRAEDRO DE SIERPINSK");
    myinit();
    glutDisplayFunc(tetaedro);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutSpecialFunc(spkeyboard);

    glutMainLoop();
    return 0;
}

