#include <iostream>
#include<GL/glut.h>
#include<algorithm>
#include<GL/gl.h>
#include<vector>
#include<math.h>
#include <vector>

using namespace std;

typedef int coord_t;
typedef long long coord2_t;

int bottom_direito = 0;

struct Point
{
    float x, y;

    bool operator <(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

vector<Point> points;

// produto cruzado 2D de vetores OA e OB, isto é, componente z de seu produto cruzado 3D.
// Retorna um valor positivo, se o OAB fizer um giro no sentido anti-horário,
// negativo para a curva no sentido horário e zero se os pontos forem colineares.
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (coord2_t)(B.y - O.y) - (A.y - O.y) * (coord2_t)(B.x - O.x);
}


/// Retorna uma lista de pontos no casco convexo no sentido anti-horário.
/// Nota: o último ponto na lista retornada é o mesmo que o primeiro.
///retorna os ponto pertencentes ao fecho convexo.
vector<Point> convex_hull(vector<Point> P)
{
    int n = P.size(), k = 0;
    vector<Point> H(2*n);

    // Ordena os pontos lexicocagraficamente pelas abscissas.
    sort(P.begin(), P.end());

    // Construir casco inferior
    for (int i = 0; i < n; i++)
    {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];

    }

    // Construir casco superior
    for (int i = n-2, t = k+1; i >= 0; i--)
    {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }

    H.resize(k);
    return H;
}

void myinit()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    glMatrixMode(GL_POSITION);
    gluOrtho2D(-350.0,350.0,-350.0,350.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouse (int bottom,int state,int x,int y)
{
    switch(bottom)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            Point point;
            point.x = x-350;
            point.y = -(y-350);
            points.push_back(point);
            cout << "x = " << point.x << " , y = " << point.y << "\n";
            bottom_direito = 0;
            glutPostRedisplay();

        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            bottom_direito = 1;

        }
        break;
    default:
        break;
    }

}
void reshape (int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350.0,350.0,-350.0,350.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}



int contain (vector<Point> l , Point p)
{
    for (int i = 0; i < l.size(); i++)
        if (l[i].x == p.x && l[i].y == p.y) return 1;
    return 0;
}

void desenha ()
{

    glClear (GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); i += 1)
    {
        glVertex2f(points[i].x,points[i].y);
    }
    glEnd();


    vector<Point> fecho = convex_hull(points);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < fecho.size(); i += 1)
    {
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2f(fecho[i].x,fecho[i].y);
    }
    glEnd();

    if (bottom_direito == 1)
    {
        glColor3f(0.0,0.0,1.0);
        for (int i = 0; i < points.size(); i++)
        {
            if (!contain(fecho,points[i]))  //Se o points[i] não ppertence ao fecho convexo
            {
                glBegin(GL_LINES);
                for(int k = 0; k < fecho.size(); k += 1)
                {
                    glVertex2f(points[i].x,points[i].y);
                    glVertex2f(fecho[k].x,fecho[k].y);
                }
                glEnd();
            }
        }
    }

    glFlush ();

}


int main(int argc,char**argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("FECHO CONVEXO");
    myinit();
    glutDisplayFunc(desenha);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;

}

