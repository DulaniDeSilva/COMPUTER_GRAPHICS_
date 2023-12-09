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

GLfloat vertices[][3] = { {0,0,0}, {1,0,0}, {1, 0, 1},{0, 0, 1}, {0.5, 1, 0.5}
};

void surface4(int v1, int v2, int v3, int v4) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glVertex3fv(vertices[v4]);
	glEnd();
}

void surface3(int v1, int v2, int v3) {
	glBegin(GL_TRIANGLES);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glEnd();
}





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


void setLighting() {
	// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);



	// Set lighting intensity and color
	GLfloat qaAmbientLight0[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight0[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat qaSpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight0);

	// Set the light position
	GLfloat qaLightPosition0[] = { 0.0, 1.0, -1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition0);


	glEnable(GL_LIGHT1);
	GLfloat qaAmbientLight1[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat qaDiffuseLight1[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat qaSpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight1);
	GLfloat qaLightPosition1[] = { 2.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);



	glEnable(GL_LIGHT3);
	GLfloat qaAmbientLight3[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat qaDiffuseLight3[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat qaSpecularLight3[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT3, GL_AMBIENT, qaAmbientLight3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, qaDiffuseLight3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, qaSpecularLight3);
	GLfloat qaLightPosition3[] = { -2.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT3, GL_POSITION, qaLightPosition3);


}


void drawPyramid() {
	glPushMatrix();
	glColor3f(0.67, 0.60, 0.50);
	surface4(0, 1, 2, 3);
	surface3(0, 1, 4);
	surface3(2, 4, 1);
	surface3(2, 4, 3);
	surface3(0, 4, 3);
	glPopMatrix();
}

void displayPyramid() {

	GLfloat qabrown[] = { 0.67, 0.60, 0.50 };
	GLfloat qadarkbrown[] = { 0.36, 0.25, 0.2 };
	GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat qaLowAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaFullAmbient[] = { 1.0, 1.0, 1.0, 1.0 };

	for (int iIndex = 0; iIndex < 2; ++iIndex) {
		if (iIndex == 0) {
			glShadeModel(GL_FLAT);
		}
		else {
			glShadeModel(GL_SMOOTH);
		}
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT, qabrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, qabrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0);









	glPushMatrix();
	glScalef(3.0, 3.0, 3.0);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	//glScalef(2.0, 2.0, 2.0);
	glScalef(3.0, 3.0, 3.0);
	glTranslatef(-2.0, 0.0, 0.0);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	//glScalef(2.0, 2.0, 2.0);
	glScalef(3.0, 3.0, 3.0);
	glTranslatef(-4.0, 0.0, 0.0);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	//glScalef(2.0, 2.0, 2.0);
	glScalef(5.0, 5.0, 5.0);
	glTranslatef(-0.5, 0.0, -1.1);
	drawPyramid();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, qabrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, qadarkbrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0);


	glPushMatrix();
	//glScalef(2.0, 2.0, 2.0);
	glScalef(5.0, 5.0, 5.0);
	glTranslatef(-1.8, 0.0, -1.1);
	drawPyramid();
	glPopMatrix();
}








void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
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

	displayPyramid();

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




