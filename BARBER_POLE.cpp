#include <GL/glut.h>  
#include <math.h>
#define PI 3.1415927


GLfloat animYRot = 0.0;


//variables to move the camera
GLfloat camX = 0.0;
GLfloat camY = 0.0;
GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceX = 0.0;
GLfloat sceY = 0.0;
GLfloat sceZ = 0.0;

//variables to move the snowman
GLfloat objX = 0.0;
GLfloat objY = 0.0;
GLfloat objZ = 0.0;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST); //do depth comparisons and update the depth buffer
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}
void material(GLfloat amb[], GLfloat dif[], GLfloat spec[], GLfloat shin[])
{

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);
}

void draw_cylinder(GLfloat radius, GLfloat height)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */

    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */

    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * PI) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void drawAxes() {

    glBegin(GL_LINES);

    glLineWidth(1.5);

    glColor3f(0.0, 1.0, 0.0);
    GLfloat amb2[] = { 0,1,0,1 };
    GLfloat dif2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat spec2[] = { 1,1,1,1 };
    GLfloat shin2[] = { 50 };
    material(amb2, dif2, spec2, shin2);
    glVertex3f(0, -200, 0);
    glVertex3f(0, 200, 0);


    glEnd();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    GLfloat lightIntensity[] = { 1,1,1,1.0 };
    GLfloat light_position[] = { 130.0,50.0,200.0,1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    GLfloat lightIntensity1[] = { 0.5,0.5,0.5,1.0 };
    GLfloat light_position1[] = { 30.0,-30.0,30.0,1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity1);

    // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    gluLookAt(0.0, 2.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(sceY, 0.0, 1.0, 0.0);


    glPushMatrix();
    glPushMatrix();
    GLfloat amb[] = { 1,1,1,1 };
    GLfloat dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat spec[] = { 1,1,1,1 };
    GLfloat shin[] = { 50 };
    material(amb, dif, spec, shin);
    glColor3f(1, 0, 0);
    glTranslatef(0, 2, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    draw_cylinder(0.8, 6.0);
    glPopMatrix();

    //half sphere
    glPushMatrix();
    GLfloat amb1[] = { 1,1,0,1 };
    GLfloat dif1[] = { 1.5f, 0.89f, 0.0f, 1.0f };
    GLfloat spec1[] = { 1,1,1,1 };
    GLfloat shin1[] = { 10 };
    material(amb1, dif1, spec1, shin1);

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0, 2.5, 0);
    glutSolidSphere(0.9, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0, -4.5, 0);
    /*glScalef(2, 2, 2);*/
    glutSolidSphere(0.9, 20, 20);
    glPopMatrix();

    glPopMatrix();

    //Middle torus
    glPushMatrix();
    GLfloat amb2[] = { 1,1,0,1 };
    GLfloat dif2[] = { 1.5f, 0.89f, 0.0f, 1.0f };
    GLfloat spec2[] = { 1,1,1,1 };
    GLfloat shin2[] = { 100 };
    material(amb2, dif2, spec2, shin2);

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0, 1.9, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.2, 0.8, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0, -3.9, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.2, 0.8, 50, 50);
    glPopMatrix();

    glPopMatrix();

    //Inside torus
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0, 1.7, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.1, 0.8, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0, -3.7, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.1, 0.8, 50, 50);
    glPopMatrix();

    //Outside torus
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0, 2.1, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.1, 0.8, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(0, -4.1, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.1, 0.8, 50, 50);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();

}

//Animation timer function
void timer(int x) {
    if (animYRot == 360.0)
        animYRot = 0.0;
    else
        animYRot += 2.0;
    glutPostRedisplay();

    glutTimerFunc(60.0, timer, 1);
}

void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camY += 1;

    if (key == GLUT_KEY_DOWN)
        camY -= 1;

    if (key == GLUT_KEY_RIGHT)
        sceY += 1;

    if (key == GLUT_KEY_LEFT)
        sceY -= 1;


    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'l')
        glEnable(GL_LIGHTING);

    if (key == 'k')
        glDisable(GL_LIGHTING);

    if (key == '1')
        glEnable(GL_LIGHT0);

    if (key == '!')
        glDisable(GL_LIGHT0);

    if (key == '2')
        glEnable(GL_LIGHT1);

    if (key == '@')
        glDisable(GL_LIGHT1);



    glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define the Perspective projection frustum 
    // (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
    gluPerspective(120.0, aspect_ratio, 1.0, 100.0);

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("BarberPole");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    //glutTimerFunc(60.0, timer, 1);
    init();
    glutMainLoop();


    return 0;
}

