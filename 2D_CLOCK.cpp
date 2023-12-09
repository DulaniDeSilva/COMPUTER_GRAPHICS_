#include<windows.h>
#include <gl/glut.h>
#include <math.h>

#define PI 3.14

float angleHour = 0;
float angleMin = 0;
float angleSec = 0;

float clockR = 80.0f;
float angle1min = PI / 30.0f;

float minStart = 0.9f;
float minEnd = 1.0f;
float stepStart = 0.8f;
float stepEnd = 1.0f;

int frameNumber = 0;


void initFunc() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
   
}


void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    if (h == 0)
        h = 1;
    GLfloat aspect = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w >= h)
        gluOrtho2D(-100 * aspect, 100 * aspect, -100, 100);
    else
        gluOrtho2D(-100, 100, -100 / aspect, 100 / aspect);
}



//drawiung case
void case_design()
{
    glPushMatrix();
    glTranslatef(-140, -160, 0);
    float Xpos = 140, Ypos = 160, radius = 90;
    glColor3f(0.0, 0.6, 1.0);
    radius = 65;


    glBegin(GL_POLYGON);
    for (float i = 0; i < 360; i += 0.01)
        glVertex2f(Xpos + sin(i) * radius, Ypos + cos(i) * radius);
    glEnd();


    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (float i = 0; i < 360; i += 0.01)
        glVertex2f(Xpos + sin(i) * radius, Ypos + cos(i) * radius);
    glEnd();


    radius = 85;
    glColor3f(1.0, 0.0, 0.0); 
    
    glLineWidth(25);
    glBegin(GL_LINE_STRIP);
    for (float i = 0; i < 360; i += 0.01)
        glVertex2f(Xpos + sin(i) * radius, Ypos + cos(i) * radius);
    glEnd();


    radius = 78;
    glColor3f(0.0, 0.0, 0.0);
   
    glLineWidth(45);
    glBegin(GL_LINE_STRIP);
    for (float i = 0; i < 360; i += 0.01)
        glVertex2f(Xpos + sin(i) * radius, Ypos + cos(i) * radius);
    glEnd();


    glPopMatrix();

    glColor3f(1.0, 0.5, 0.5);
    glPointSize(12);
    glBegin(GL_POINTS);
    glVertex2i(-1, 3);
    glEnd();
}

//drawing numbers
void textDisplay()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2i(58, 0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
    glRasterPos2i(0, -60);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '6');
    glRasterPos2i(-62, -2);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '9');
    glRasterPos2i(-2, 57);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
    glRasterPos2i(1, 57);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
    glRasterPos2d(-14, -40);

}
void minutes_design()
{
    glLineWidth(2);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    for (int i = 0; i < 60; i++)
    {
        float c = cos(i * angle1min), s = sin(i * angle1min);
        if (i % 5) { 
            if (i % 5 == 1)
                glColor3f(1.0f, 1.0f, 1.0f);
            
                glVertex2f(clockR * minStart * c, clockR * minStart * s);
                glVertex2f(clockR * minEnd * c, clockR * minEnd * s);
        }
        else {
                 glColor3f(0.0f, 1.0f, 0.0f);
            
                glVertex2f(clockR * stepStart * c, clockR * stepStart * s);
                glVertex2f(clockR * stepEnd * c, clockR * stepEnd * s);
        }
    }
    glEnd();
}
void hand_design()
{
    
    
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3);
    glPushMatrix();
    glTranslatef(-1, 3, 0);
    glPushMatrix();
    glRotatef(-angleSec, 0, 0, 1);
    glPushMatrix();
    glTranslatef(1, -3, 0);
    glBegin(GL_LINES);
    glVertex2i(-1, 3);
    glVertex2i(35, -45);
    glEnd();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    //minute hand
    glLineWidth(5);
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(-1, 3, 0);
    glRotatef(-angleMin, 0, 0, 1);
    glTranslatef(1, -3, 0);

    glBegin(GL_POLYGON);
    glVertex2i(-1, 3);
    glVertex2i(15, -2);
    glVertex2i(45, 2);
    glVertex2i(15, 5);
    glEnd();

    glPopMatrix();

   //hour
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glLineWidth(12);
    glTranslatef(-1, 3, 0);
    glRotatef(-angleHour, 0, 0, 1);

    glBegin(GL_POLYGON);
    glVertex2i(0, 0);
    glVertex2i(2, 25);
    glVertex2i(0, 50);
    glVertex2i(-2, 25);
    glEnd();

    glPopMatrix();
}

//inside clock
void drawWindmill() {
    int i;
    glColor3f(0.8f, 0.8f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 0);
    glVertex2f(1, 0);
    glVertex2f(1, 30);
    glVertex2f(-1, 30);
    glEnd();

    glTranslatef(0, 30, 0);
    glScalef(5.0, 5.0, 0.0);
    glRotated(frameNumber * (180.0 / 46), 0, 0, 1);
    glColor3f(0.4f, 0.4f, 0.8f);
    for (i = 0; i < 3; i++) {
        glRotated(120, 0, 0, 1);
        glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(0.5f, 0.1f);
        glVertex2f(1.5f, 0);
        glVertex2f(0.5f, -0.1f);
        glEnd();
    }
}

void sun() {
  
    glColor3f(1, 1, 0);
    for (int i = 0; i < 21; i++) {
        glRotatef(360 / 21, 0, 0, 1);
        glBegin(GL_LINES);
        glLineWidth(1.0);
        glVertex2f(0, 0);
        glVertex2f(7, 0);
        glEnd();
    }

}

void mountain() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-65, 0.0);
    glVertex2f(65, 0.0);
    glVertex2f(0.0, 65.0);
    glEnd();
}








void clockDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    /*
    //yaxis
    glColor3f(1.0,1.0, 1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 200.0);
    glVertex2f(0.0, -200.0);
    glEnd();

    //xaxis
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(200.0, 0.0);
    glVertex2f(-200.0, 0.0);
    glEnd();
    */

    case_design();
   

    glPushMatrix();
    glScalef(0.5, 0.8, 0);
    glTranslatef(-60, -20, 0);
    mountain();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.6, 0.7, 0);
    glTranslatef(40, -23, 0);
    mountain();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40, 0, 0);
    drawWindmill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25, 15, 0);
    drawWindmill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18, 2, 0);
    drawWindmill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 40, 0);
    sun();
    glPopMatrix();

    glPushMatrix();
  
    minutes_design();
    textDisplay();
    hand_design();
    glPopMatrix();
  


    glFlush();
}

void dial_func()
{
    if (angleSec < 360)
        angleSec += 0.03;
    else
        angleSec = 0;
    if (angleMin < 360)
        angleMin += 0.00085;
    else
        angleMin = 0;
    if (angleHour < 360)
        angleHour += 0.0000146;
    else
        angleHour = 0;
    glutPostRedisplay();
}

void doFrame(int v) {
    frameNumber++;
    glutPostRedisplay();
    glutTimerFunc(30, doFrame, 0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 10);
    glutInitWindowSize(1080, 780);
    glutCreateWindow("Clock");
    initFunc();
    glutDisplayFunc(clockDisplay);
    glutReshapeFunc(reshape);
    glutTimerFunc(200, doFrame, 0);
    glutIdleFunc(dial_func);
    glutMainLoop();
    return 0;
}