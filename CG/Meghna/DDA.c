#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
float x0,x1,y0,y1;
 
void display(void)
{
	float dy,dx,steps,x,y,i,xinc,yinc;
	dx=x1-x0;
	dy=y1-y0;
 
	if(abs(dx)> abs(dy))
		steps = abs(dx);

	else
		steps = abs(dy);
 
 
	xinc = dx/steps;
	yinc = dy/steps;
 
	x=x0;
	y=y0;
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
 
	for (i=1 ;i<=steps;i++)
	{
		x= x + xinc;
		y= y + yinc;
 
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
	}
 
 
	glFlush();
}
 

 
int main(int argc, char** argv) {
scanf("%f",&x0);
scanf("%f",&y0);
scanf("%f",&x1);
scanf("%f",&y1);
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (200, 200);
glutInitWindowPosition (100,100);
glutCreateWindow ("DDA");
glutDisplayFunc(display);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-100,100,-100,100);
glutMainLoop();
 
return 0;
}
