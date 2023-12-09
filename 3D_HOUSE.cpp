#include <GL/glut.h>  
#include <math.h>

// For animating the rotation of the objects
float houseRotation = 0.0;

GLfloat xRotated = 0, yRotated = 0, zRotated = 0;
// variables to move outermost Object Frame (to move all the rendered environment)
float moveX = 0.0f;
float moveY = 0.0f;
float moveZ = 0.0f;

GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;

//variables to move the camera
float camX = 0.0f;
float camY = 0.0f;
float camZ = 0.0f;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawAxes() {

    glBegin(GL_LINES);

    glLineWidth(1.5);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-20, 0, 0);
    glVertex3f(20, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -20, 0);
    glVertex3f(0, 20, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -20);
    glVertex3f(0, 0, 20);

    glEnd();
}


void drawObject() {
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 1.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 1.0, 1.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glEnd();

}

void roof() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 1.5, 0.5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, 1.5, 0.5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 1.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 1.5, 0.5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 1.5, 0.5);
    glEnd();
}

void door() {
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.7, 0.0);
    glVertex3f(0.4, 0.0, 0.0);
    glVertex3f(0.8, 0.0, 0.0);
    glVertex3f(0.8, 0.8, 0.0);
    glVertex3f(0.4, 0.8, 0.0);
    glEnd();
}

void building() {
    glPushMatrix();
    roof();
    drawObject();
    door();
    glPopMatrix();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Setting the modelview matrix to the identity matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    gluLookAt(0.0 + camX, 2.0 + camY, 5.0 + camZ, 0, 0, 0, 0, 1.0, 0);
    glColor3f(1.0, 1.0, 1.0);
    //glTranslatef(0.0, 0.0, -5.0);

    glTranslatef(moveX, moveY, moveZ);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

 

    drawAxes();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    /*glColor3f(0.9, 0.3, 0.2);*/
    glRotatef(xRotated, 1.0, 0.0, 0.0);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    glScalef(3.0f, 3.0f, 3.0f);
    building();
    glPopMatrix();

    glutSwapBuffers();

}

void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camY += 0.5;
    if (key == GLUT_KEY_DOWN)
        camY -= 0.5;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

    if (key == 'z')
        moveZ += 1;

    if (key == 'Z')
        moveZ -= 1;

    if (key == 'l')
        rotY -= 5.0;

    if (key == 'r')
        rotY += 1.0;

    glutPostRedisplay();

}

//Rotating teapot
void Timer(int x) {
    xRotated += 1;
    yRotated += 1;
    zRotated += 1;

    houseRotation += houseRotation >= 360.0 ? -houseRotation : 2;
    glutPostRedisplay();

    glutTimerFunc(60, Timer, 1);
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Rotating Teapot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    glutTimerFunc(60.0, Timer, 1);
    init();
    glutMainLoop();


    return 0;
}