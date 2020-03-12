
#include <GL/gl.h>
#include <GL/glut.h>

int window;
int value;

void display () {

    glClear(GL_COLOR_BUFFER_BIT);
    if(value==1) {
        glutWireTeapot(.3);
        glEnd();
    }
    else if(value==2)
        glutSolidTeapot(.5);

    glFlush();

}

void menu(int num){
  if(num == 0){
        glutDestroyWindow(window);
    exit(0);
  }
  value = num;
  glutPostRedisplay();
} 
void createMenu(void){     
    glutCreateMenu(menu);
    glutAddMenuEntry("Wired Teapot", 1);
    glutAddMenuEntry("Solid Teapot", 2);
    glutAddMenuEntry("Quit", 0);     
    glutAttachMenu(GLUT_RIGHT_BUTTON);
} 

int main ( int argc, char * argv[] ) {

    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB);
    window = glutCreateWindow("Teapot");
    createMenu();
    glutDisplayFunc(display);
    glutMainLoop();
}