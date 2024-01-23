
#include <GL/glut.h>  
#include <math.h>

float moveX;
float moveY;
float moveZ;

float rotateX;
float rotateY;
float rotateZ;

float cameraX;
float cameraY;
float cameraZ;

float rotateobject;

GLfloat vertices[][3] = { {0,0,0}, {0.5, 0, 1}, {1, 0, 0.5}, {0.5, 0, 0}, {0, 0, 0.5},
                            {0.5, 1, 1}, {1, 1, 0.5}, {0.5, 1, 0}, {0, 1, 0.5},
                            {1, 0.5, 1}, {1, 0.5, 0},
                            {0, 0.5, 1}, {0, 0.5, 0}
                            };



void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
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
void DrawGrid() {
    GLfloat ext = 20.0f;
    GLfloat step = 1.0f;
    GLfloat yGrid = -0.4f;
    GLint line;

    glBegin(GL_LINES);
    for (line = -ext; line <= ext; line += step) {
        glVertex3f(line, yGrid, ext);
        glVertex3f(line, yGrid, -ext);

        glVertex3f(ext, yGrid, line);
        glVertex3f(-ext, yGrid, line);
    }
    glEnd();
}

void surface4(int v1, int v2, int v3, int v4) {
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[v1]);
    glVertex3fv(vertices[v2]);
    glVertex3fv(vertices[v3]);
    glVertex3fv(vertices[v4]);
    glEnd();
}



void drawCube() {
    //front
    glColor3f(1.0, 0.0, 0.0);
    surface4(1, 9, 5, 11);

    //back
    glColor3f(0.0, 1.0, 0.0);
    surface4(3,10,7,12);

    //left
    glColor3f(1.0, 1.0, 0.0);
    surface4(2, 10, 6, 9);

    //right
    glColor3f(0.0, 1.0, 1.0);      
    surface4(8, 11, 4, 12);

    //top
    glColor3f(0.5, 0.5, 1.0);
    surface4(5, 6, 7, 8);

    //bottom
    glColor3f(1.0, 0.3, 0.9);
    surface4(1, 2, 3, 4);

}



void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    gluLookAt(3.0 + cameraX, 2.0 + cameraY, 5.0 + cameraZ, 0, 0, 0, 0, 1.0, 0);
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(moveX, moveY, moveZ);
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);
    glRotatef(rotateZ, 0.0, 0.0, 1.0);

    DrawGrid();

    drawAxes();

    glPushMatrix();
    glRotatef(rotateobject, 0.0, 1.0, 0.0);
    glScalef(5.0, 5.0, 5.0);
    //glTranslatef(-2.0, 0, 0);
    drawCube();
    glPopMatrix();

   


    glPopMatrix();
    glutSwapBuffers();

}



void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        cameraY += 0.5;
    if (key == GLUT_KEY_DOWN)
        cameraY -= 0.5;
    if (key == GLUT_KEY_LEFT)
        cameraZ += 0.5;
    if (key == GLUT_KEY_RIGHT)
        cameraZ -= 0.5;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'X')
        moveX++;
    if (key == 'x')
        moveX--;
    if (key == 'Z')
        moveZ++;
    if (key == 'z')
        moveZ--;
    if (key == 'Y')
        moveY++;
    if (key == 'y')
        moveY--;

    glutPostRedisplay();

}

void Timer(int x) {
    rotateobject += rotateobject >= 360.0 ? -rotateobject : 2;
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







