/*Program to translate, rotate a pentagon, triangle and trapezoid*/
/*To Run - g++ TranslateRotateTimer.cpp -o gl -lGL -lGLU -lglut*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
 
GLfloat angle = 0.0f;  // rotational angle of the shapes
int refreshMills = 30; // refresh interval in milliseconds
 
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);                       //Black 
}
 
void Timer(int value) {
   glutPostRedisplay();     
   glutTimerFunc(refreshMills, Timer, 0);                      //Next timer call
}
 
void display() {
   glClear(GL_COLOR_BUFFER_BIT);   
   glMatrixMode(GL_MODELVIEW);     
   glLoadIdentity();               
 
   glPushMatrix();                     
   glTranslatef(-0.5f, 0.4f, 0.0f);                            //Translate
   glRotatef(angle*2, 0.0f, 0.0f, 1.0f);                       //Rotate by angle in degrees
   glBegin(GL_QUADS);                  
      glColor3f(1.0f, 0.0f, 0.0f);                             //Red
      glVertex2f(-0.4f, -0.4f);
      glVertex2f( 0.4f, -0.4f);
      glVertex2f( 0.2f,  0.2f);
      glVertex2f(-0.2f,  0.2f);
   glEnd();
   glPopMatrix();                                              //Restore the model-view matrix
 
   glPushMatrix();                     
   glTranslatef(0.4f, -0.3f, 0.0f);    
   glRotatef(-1*angle, 0.0f, 0.0f, 1.0f); 
   glBegin(GL_TRIANGLES);
      glColor3f(0.0f, 0.0f, 1.0f);                             //Blue
      glVertex2f(-0.3f, -0.2f);
      glVertex2f( 0.3f, -0.2f);
      glVertex2f( 0.0f,  0.3f);
   glEnd();
   glPopMatrix();                      
 
   glPushMatrix();                     
   glTranslatef(0.7f, 0.3f, 0.0f);    
   glRotatef(angle, 0.0f, 0.0f, 1.0f);
   float angleIncrement = 360.0f / 5; 
   angleIncrement *= 3.14f / 180.0f;    
   glBegin(GL_TRIANGLE_FAN);
      glColor3f(1.0f, 1.0f, 0.0f);                             // Yellow
      float ang = 0.0f;
      float radius = 0.2;
      for (int k = 0; k < 5; ++k) {
         glVertex3f(radius * cos(ang), radius * sin(ang), 0.0f);
         ang += angleIncrement;
      }
   glEnd(); 
   glPopMatrix();                    
 
   glutSwapBuffers();                                         //Double buffered - swap the front and back buffers
 
   // Change the rotational angle after each display()
   angle += 2.0f;
}
 
void reshape(GLsizei width, GLsizei height) {  
   
   if (height == 0) 
      height = 1;                
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);  
   glLoadIdentity();

   if (width >= height) {
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);          
   glutInitDisplayMode(GLUT_DOUBLE);  
   glutInitWindowSize(640, 480);   
   glutInitWindowPosition(50, 50); 
   glutCreateWindow("Transalte and Rotate");  
   glutDisplayFunc(display);       
   glutReshapeFunc(reshape);      
   glutTimerFunc(0, Timer, 0);     
   initGL();                       
   glutMainLoop();                 
   return 0;
}