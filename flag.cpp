#include<windows.h>
#include<stdio.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<SOIL2.h>

//for make curve figure flag to animate
GLfloat ya = 50, xa = 10;
int yFlag = 1, xFlag = 1;


void Animate()
{
        if (ya > -50 && yFlag == 1)
            ya = ya - 0.2;

        if (ya <= -50 && yFlag == 1)
            yFlag = 0;

        if (ya < 50 && yFlag == 0)
            ya = ya + 0.2;

        if (ya >= 50 && yFlag == 0)
            yFlag = 1;



        if (xa > -10 && xFlag == 1)
            xa = xa - 0.2;

        if (xa <= -10 && xFlag == 1)
            xFlag = 0;

        if (xa < 10 && xFlag == 0)
            xa = xa + 0.2;

        if (xa >= 10 && xFlag == 0)
            xFlag = 1;
    
    glutPostRedisplay();
}

void Draw()
{
    GLfloat x[4], y1[4], y2[4];
    GLdouble xt[200], y1t[200], y2t[200], t;
    int i, c;
    glClear(GL_COLOR_BUFFER_BIT);

    x[0] = 100; x[1] = 200; x[2] = 200;  x[3] = 300 - xa;
    y1[0] = 450; y1[1] = 450 + ya; y1[2] = 450 - ya;  y1[3] = 450;
    y2[0] = 300; y2[1] = 300 + ya; y2[2] = 300 - ya;  y2[3] = 300;

    for (i = 0, t = 0, c = 0; t < 1; i++, t = t + 0.01)
    {
        xt[i] = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
        y1t[i] = pow(1 - t, 3) * y1[0] + 3 * t * pow(1 - t, 2) * y1[1] + 3 * pow(t, 2) * (1 - t) * y1[2] + pow(t, 3) * y1[3];
        y2t[i] = pow(1 - t, 3) * y2[0] + 3 * t * pow(1 - t, 2) * y2[1] + 3 * pow(t, 2) * (1 - t) * y2[2] + pow(t, 3) * y2[3];
        c++;
    }

    glColor3f(1, 1.0, 0);
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < c; i++)
    {
         glVertex2d(xt[i], y1t[i]);
         glVertex2d(xt[i], y2t[i]);
    }
    glEnd();


    glColor3f(0.6, 0.6, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(90.0, 460.0);
    glVertex2f(100.0, 460.0);
    glVertex2f(100.0, 50.0);
    glVertex2f(90.0, 50.0);
    glEnd();

 

    glFlush();
}


void MyInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
   
    

}

int main(int argC, char* argV[])
{
    glutInit(&argC, argV);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Normal Flag");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Animate);
    glutMainLoop();
    return 0;
}