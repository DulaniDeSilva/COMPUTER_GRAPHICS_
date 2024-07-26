#include <GL/glut.h>
#include <math.h>
#include <SOIL2.h>
#include <stdio.h>

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

unsigned char* image;
unsigned char* pyramidimage;
unsigned char* pyramidimage2;
unsigned char* pyramidimage3;

GLuint tex;
GLuint tex1;
GLuint tex2;
GLuint tex3;


#define IMAGE_ROWS 64      // Texture image rows and columns
#define IMAGE_COLS 64

int width;
int height;

int pyramidWidth, pyramidWidth2, pyramidWidth3, pyramidWidth4;
int pyramidHeight, pyramidHeight2, pyramidHeight3, pyramidHeight4;




// Texture
GLubyte imageData[IMAGE_ROWS][IMAGE_COLS][3]; // Texture image data




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


// Load the imageData array with checkerboad pattern
void loadTextureImageData() {
	int value;
	for (int row = 0; row < IMAGE_ROWS; row++) {
		for (int col = 0; col < IMAGE_COLS; col++) {
			// Each cell is 8x8, value is 0 or 255 (black or white)
			value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
			imageData[row][col][0] = (GLubyte)value;
			imageData[row][col][1] = (GLubyte)value;
			imageData[row][col][2] = (GLubyte)value;
		}
	}
}

//land image
void loadTextureDataFromImage() {
	image = SOIL_load_image("land5.jpeg", &width, &height, 0, SOIL_LOAD_RGB);

	if (image == NULL) {
		printf("Error : %s", SOIL_last_result());
	}
}

void loadTextureDataFromPyramidImage() {
	pyramidimage = SOIL_load_image("pyramid.jpg", &pyramidWidth, &pyramidHeight, 0, SOIL_LOAD_RGB);

	if (pyramidimage == NULL) {
		printf("Error : %s", SOIL_last_result());
	}
}

void loadTextureDataFromPyramid2Image() {
	pyramidimage2 = SOIL_load_image("pyramid2.jpg", &pyramidWidth2, &pyramidHeight2, 0, SOIL_LOAD_RGB);

	if (pyramidimage2 == NULL) {
		printf("Error : %s", SOIL_last_result());
	}
}


void loadTextureDataFromPyramid3Image() {
	pyramidimage3 = SOIL_load_image("pyramid3.jpg", &pyramidWidth3, &pyramidHeight3, 0, SOIL_LOAD_RGB);

	if (pyramidimage3 == NULL) {
		printf("Error : %s", SOIL_last_result());
	}
}




void loadTextures() {

	loadTextureDataFromImage(); // Load pattern into image data array
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);  // Create texture from image data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	SOIL_free_image_data(image);
}

void loadPyramidTextures() {

	loadTextureDataFromPyramidImage(); // Load pattern into image data array
	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pyramidWidth, pyramidHeight, 0, GL_RGB,
		GL_UNSIGNED_BYTE, pyramidimage);  // Create texture from image data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	SOIL_free_image_data(pyramidimage);
}

void loadPyramid2Textures() {

	loadTextureDataFromPyramid2Image(); // Load pattern into image data array
	glGenTextures(1, &tex3);
	glBindTexture(GL_TEXTURE_2D, tex2);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pyramidWidth2, pyramidHeight2, 0, GL_RGB,
		GL_UNSIGNED_BYTE, pyramidimage2);  // Create texture from image data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	SOIL_free_image_data(pyramidimage2);
}

void loadPyramid3Textures() {

	loadTextureDataFromPyramid3Image(); // Load pattern into image data array
	glGenTextures(1, &tex3);
	glBindTexture(GL_TEXTURE_2D, tex3);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pyramidWidth3, pyramidHeight3, 0, GL_RGB,
		GL_UNSIGNED_BYTE, pyramidimage3);  // Create texture from image data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	SOIL_free_image_data(pyramidimage3);
}


void setLighting() {
	// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	GLfloat qaAmbientLight0[] = { 0.7, 0.7, 0.6, 1.0 };
	GLfloat qaDiffuseLight0[] = { 0.8, 0.8, 0.7, 1.0 };
	GLfloat qaSpecularLight0[] = { 1.0, 1.0, 1.0, 1.0 };


	// Set lighting intensity and color
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight0);

	// Set the light position
	GLfloat qaLightPosition0[] = { -500.0, -100.0, -100.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition0);

	GLfloat qaLightPosition1[] = { -500.0, -100.0, -100.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition1);

}



void drawLand() {
	//GLfloat step = 1.0f;
	GLint line;
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, 0.0, -100);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100, 0.0, 100);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100, 0.0, 100);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100, 0.0, -100);

	glEnd();

}



void drawAxes() {
	glBegin(GL_LINES);
	glLineWidth(1.5);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-40, 0, 0);
	glVertex3f(40, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -40, 0);
	glVertex3f(0, 40, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -40);
	glVertex3f(0, 0, 40);

	glEnd();
}





//drawing a pyramid
void drawPyramid() {
	//glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 0.0, 1.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 1.0, 0.5);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 1.0, 0.5);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, 0.0, 1.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 1.0, 0.5);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, 1.0, 0.5);


	glEnd();

}

void drawGiza() {

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

	glMaterialfv(GL_FRONT, GL_AMBIENT, qaWhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, qabrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 200.0);



	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tex3);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex3);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex3);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	glScalef(3.0, 3.0, 3.0);
	glTranslatef(0.4, 0.0, -1.1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	glScalef(5.0, 5.0, 5.0);
	glTranslatef(0.8, 0.0, -1.5);
	glBindTexture(GL_TEXTURE_2D, tex1);
	drawPyramid();
	glPopMatrix();

	glPushMatrix();
	glScalef(5.0, 5.0, 5.0);
	//glTranslatef(2.5, 0.0, -2.8);
	glTranslatef(1.6, 0.0, -2.0);
	glBindTexture(GL_TEXTURE_2D, tex3);
	drawPyramid();
	glPopMatrix();

}



void init(void) {
	glClearColor(0.0, 0.74, 1.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	loadTextures();
	loadPyramidTextures();
	loadPyramid2Textures();
	loadPyramid3Textures();
	glEnable(GL_LIGHT0);

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
	//drawGrid();
	//drawAxes();
	drawLand();


	glPushMatrix();
	drawGiza();
	glPopMatrix();
	setLighting();

	//displayPyramid();

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
	if (key == '!')
		glEnable(GL_LIGHT0);
	if (key == '@')
		glDisable(GL_LIGHT0);

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

























