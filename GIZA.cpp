#include<gl\glut.h>
#include<math.h>

//variables to move the camera
GLfloat camX = 0.0;
GLfloat camY = 0.0;
GLfloat camZ = 0.0;

//variables to move the scene
GLfloat moveX = 0.0;
GLfloat moveY = 0.0;
GLfloat moveZ = 0.0;

//variables to move the object
GLfloat objX = 0.0;
GLfloat objY = 0.0;
GLfloat objZ = 0.0;

GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;





constexpr float PI = 3.14159265358979323846;

GLfloat vertices[][3] = { {0,0,0}, {1,0,0}, {1, 0, 1},{0, 0, 1}, {0.5, 1, 0.5} };



void drawGrid() {
	GLfloat step = 1.0f;
	GLint line;

	glBegin(GL_LINES);
	for (line = -20; line <= 20; line += step) {
		glVertex3f(line, -0.4, 20);
		glVertex3f(line, -0.4, -20);

		glVertex3f(20, -0.4, line);
		glVertex3f(-20, -0.4, line);
	}
	glEnd();
}

void drawAxes() {
	glBegin(GL_LINES);
	glLineWidth(1.5);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-200, 0, 0);
	glVertex3f(200, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -200, 0);
	glVertex3f(0, 200, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -200);
	glVertex3f(0, 0, 200);

	glEnd();
}

void drawLand() {
	GLint line;

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	//glColor3f(0.14, 0.58, 0.74);
	for (line = -20; line <= 20; line += 20) {
		glVertex3f(line, -0.4, 20);
		glVertex3f(line, -0.4, -20);
		glVertex3f(20, -0.4, line);
		glVertex3f(-20, -0.4, line);
	}
	glEnd();
}

//drawing quadrangle surface
void surface4(int v1, int v2, int v3, int v4) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glVertex3fv(vertices[v4]);
	glEnd();
}

//drawing triangular surface
void surface3(int v1, int v2, int v3) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glEnd();
}

void drawPyramid() {
	//Base square
	//glNormal3f(0, 1, 0);
	surface4(0, 3, 2, 1);

	//glNormal3f(-1, 0, 0);
	surface3(1, 2,4);
	
	//glNormal3f(0, 0, 1);
	surface3(3, 4, 2);

	//glNormal3f(-1, 0, 0);
	surface3(3, 0, 4);

	//glNormal3f(0, 0, -1);
	surface3(4, 0, 1);

}

void setLighting() {
	//lighting setup
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//setting light intensity and color for sunlight like effect
	GLfloat qaAmbientLight[] = { 0.7, 0.7, 0.6, 1.0 };
	GLfloat qaDiffuseLight[] = { 0., 0.8, 0.7, 1.0 };
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	GLfloat qaLightPosition[] = { -500.0, -100.0, -400.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);
	GLfloat qaLightPosition1[] = { -500.0, -100.0, -400.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition1);

}


void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// 
	//changing the background black color to blue color
	//glClearColor(0.14, 0.58, 0.75, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}


void drawPyramidWithLighting() {
	GLfloat qaPyramid_Light[] = { 0.76,0.59,0.36,1.0 };
	GLfloat qaPyramid[] = { 0.47,0.3,0.14 };
	GLfloat qaLowAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaFullAmbient[] = { 1.0, 1.0, 1.0, 1.0 };


}




void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(0.0 + camX, 0.0 + camY, 5.0 + camZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glTranslatef(moveX, moveY, moveZ);
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

	glColor3f(1.0, 1.0, 1.0);
	drawGrid();
	drawAxes();


	setLighting();

	//displayPyramid();
	//drawLand();

	glPushMatrix();
	
	drawPyramid();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();






}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, aspect_ratio, 1.0, 100.0);
}

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		camY += 0.5;
	if (key == GLUT_KEY_DOWN)
		camY -= 0.5;
	if (key == GLUT_KEY_LEFT)
		camZ += 0.5;
	if (key == GLUT_KEY_RIGHT)
		camZ -= 0.5;
	glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'z')
		moveZ++;
	if (key == 'Z')
		moveZ--;
	if (key == 'x')
		moveX++;
	if (key == 'X')
		moveX--;
	if (key == 'y')
		moveY++;
	if (key == 'Y')
		moveY--;
	if (key == 'l')
		rotY -= 5.0;
	if (key == 'r')
		rotY += 5.0;

	glutPostRedisplay();

}




int main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Olympic Stadium");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}


