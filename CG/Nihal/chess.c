#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
float x1,x2,y1,y2;
 
void display(void)
{
float dy,dx,step,x,y,k,Xin,Yin;
int i;
x1=-90;
y1=-90;
x2=-90;
y2=-10;
for(i=1;i<=9;i++){

dx=x2-x1;
dy=y2-y1;
 
if(abs(dx)> abs(dy))
{
step = abs(dx);
}
else
step = abs(dy);
 
Xin = dx/step;
Yin = dy/step;
 
x= x1;
y=y1;
glBegin(GL_POINTS);
glVertex2i(x,y);
glEnd();
 
for (k=1 ;k<=step;k++)
{
x= x + Xin;
y= y + Yin;
 
glBegin(GL_POINTS);
glVertex2i(x,y);
glEnd();
}
x1+=10;
x2+=10; 
}
x1=-90;
y1=-90;
x2=-10;
y2=-90;
for(i=1;i<=9;i++){

dx=x2-x1;
dy=y2-y1;
 
if(abs(dx)> abs(dy))
{
step = abs(dx);
}
else
step = abs(dy);
 
Xin = dx/step;
Yin = dy/step;
 
x= x1;
y=y1;
glBegin(GL_POINTS);
glVertex2i(x,y);
glEnd();
 
for (k=1 ;k<=step;k++)
{
x= x + Xin;
y= y + Yin;
 
glBegin(GL_POINTS);
glVertex2i(x,y);
glEnd();
}
y1+=10;
y2+=10; 
}
glFlush();

}
 
void init(void)
{
glClearColor(0.7,0.7,0.7,0.7);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-95,0,-95,0);
}
 
int main(int argc, char** argv) {
 
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100,100);
glutCreateWindow ("DDA Line Algo");
init();
glutDisplayFunc(display);
glutMainLoop();
 
return 0;
}
