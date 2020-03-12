#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

#define MENU_SMOOTH 1
#define MENU_FLAT 0

void generateColors();
double random(bool reset = false);
void drawSquare(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
void divideSquare(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int iteraciones);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void menu(int item);
void display();
void doZoom();
void init();


GLfloat square[4][2] = {{-10.0, -10.0}, 
                        { -10.0, 10.0}, 
                        { 10.0,  10.0},
                    	{ 10.0 ,-10.0}};


double colors[1000] = {0};

int iterations = 1;
double zoom = 0;
int shading = GL_FLAT;

void generateColors() {
	for (int i = 0; i < 1000; i++) {
		colors[i] = rand() / (double) RAND_MAX;
	}
}

double random(bool reset) {
	static int curr = 0;
	if (reset) { 
		curr = 0;
		return 0.0;
	} else {
		if (curr >= 1000) curr = 0;
		return colors[curr++];
	}
}

void drawSquare(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d,bool isBlack) {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	
	glShadeModel(shading);
	
	if (!isBlack){
	glBegin(GL_POLYGON);
		glColor3f(random(false), random(false), random(false));
		glVertex2fv(a);
		glColor3f(random(false), random(false), random(false));
		glVertex2fv(b);
		glColor3f(random(false), random(false), random(false));
		glVertex2fv(c);
		glColor3f(random(false), random(false), random(false));
		glVertex2fv(d);
	glEnd();
	}
	else{
	glBegin(GL_POLYGON);
		glColor3f(0.0,0.0,0.0);
		glVertex2fv(a);
		glColor3f(0.0,0.0,0.0);
		glVertex2fv(b);
		glColor3f(0.0,0.0,0.0);
		glVertex2fv(c);
		glColor3f(0.0,0.0,0.0);
		glVertex2fv(d);
	glEnd();
	}
	
}

void divideSquare(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int iteraciones) {
     GLfloat v[4][2];
     int j;
     if (iteraciones > 0) {

     	v[0][0] = ((a[0]+d[0])/2) - 1;
     	v[1][0] = ((b[0]+c[0])/2) - 1;
     	v[3][0] = ((a[0]+d[0])/2) + 1;
     	v[2][0] = ((b[0]+c[0])/2) + 1;

     	v[0][1] = ((a[1]+b[1])/2) - 1;
     	v[2][1] = ((c[1]+d[1])/2) + 1;
     	v[3][1] = ((c[0]+d[1])/2) - 1;
     	v[1][1] = ((a[1]+b[1])/2) + 1;

     	drawSquare(v[0],v[1],v[2],v[3],true);

     	GLfloat temp1[2] = {a[0] ,v[0][1]};
     	GLfloat temp2[2] = {v[0][0] , a[1]};
     	divideSquare(a , temp1 , v[0] , temp2 , iteraciones-1);

     	GLfloat temp3[2] = {b[0] , v[1][1]};
     	GLfloat temp4[2] = {v[1][0], b[1]};
     	divideSquare( temp3 , b , temp4 , v[1], iteraciones-1);

     	GLfloat temp5[2] = {v[2][0],c[1]};
     	GLfloat temp6[2] = {c[0],v[2][1]};
     	divideSquare( v[2] , temp5 , c , temp6 , iteraciones-1);

     	GLfloat temp7[2] = {v[3][0] , d[1]};
     	GLfloat temp8[2] = {d[0] , v[3][1]};
     	divideSquare( temp7 , v[3] , temp8 , d , iteraciones-1);

     } else 
        return;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case '+':
			if (iterations < 10) iterations += 1;
			display();
			break;
		case '-':
			if (iterations > 0) iterations -= 1;
			display();
			break;
		case 'q':
			exit(0);
			break;
	}
}

void special(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			if (zoom - 0.1 > -1) zoom -= 0.05;
			doZoom();
			break;
		case GLUT_KEY_DOWN:
			zoom += 0.05;
			doZoom();
			break;
	}
}

void mouse(int button, int state, int x, int y) {
	if (state == GLUT_UP) {
		generateColors();
		display();
	}
}

void menu(int item) {
	switch (item) {
		case MENU_FLAT:
			shading = GL_FLAT;
			display();
			break;
		case MENU_SMOOTH:
			shading = GL_SMOOTH;
			display();
			break;
	}
}

void doZoom() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 - zoom, 1.0 + zoom, -1.0 - zoom, 1.0 + zoom);
	glMatrixMode(GL_MODELVIEW);
	display();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	random(true);
	drawSquare(square[0], square[1], square[2], square[3],false);
	divideSquare(square[0], square[1], square[2], square[3], iterations);
	glFlush();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-12.0, 12.0, -12.0, 12.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); 
	srand(time(NULL));

	generateColors();

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	init();
	glutCreateWindow("Sierpinski Triangle");
	glutPositionWindow(100, 100);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutCreateMenu(menu);
	glutAddMenuEntry("Smooth shading", MENU_SMOOTH);
	glutAddMenuEntry("Flat shading", MENU_FLAT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}