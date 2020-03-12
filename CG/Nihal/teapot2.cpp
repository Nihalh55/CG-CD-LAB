
#include <GL/gl.h>
#include <GL/glut.h>

int window;
int value;

void display () {

    glClear(GL_COLOR_BUFFER_BIT);
    if(value==1) {

        glColor3f(1.0, 0.0, 0.0); 
        glutWireTeapot(.3);
        glEnd();
    }
    else if(value==2){

        glColor3f(0.0 , 1.0 ,0.0); 
        glutWireTeapot(.3);
        glEnd();
    }
    else if(value==3){
        glColor3f(1.0, 0.0, 0.0); 
        glutSolidTeapot(.5);
    }
    else if(value==4){
        glColor3f(0.0, 1.0, 0.0); 
        glutSolidTeapot(.5);
    }
        
    glFlush();

}

void menu(int num){
  if(num == 0){
        glClear(GL_COLOR_BUFFER_BIT);
  }
  value = num;
  glutPostRedisplay();
} 
void createMenu(void){     
    int sub1 = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    int sub2 = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 3);
    glutAddMenuEntry("Green", 4);
    glutCreateMenu(menu);
    glutAddSubMenu("Wired Teapot", sub1);
    glutAddSubMenu("Solid Teapot", sub2);
    glutAddMenuEntry("Clear", 0);     
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