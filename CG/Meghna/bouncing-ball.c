
Skip to content
Using Gmail with screen readers
36 of 4,278
cg lab4
Inbox
	x
Meghna Savit <meghna.savit99@gmail.com>
	
AttachmentsJan 22, 2020, 3:31 PM (6 days ago)
	
to me

3 Attachments
	
	
	

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int xc = 0, yc = 0;

void plot_point(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}

void bresenham_circle(int r)
{
  int x=0,y=r;
  float pk=3-2.0*r;
  plot_point(x,y);
  int k;

  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 4*x + 6;
    else
    {
      y = y - 1;
      pk = pk + 4*(x - y) + 10;
    }
    plot_point(x,y);
  }
  glEnd();
  glFlush();
}

void circles(void)
{
int i=0;
  glClear(GL_COLOR_BUFFER_BIT);                                                                                                                                                                                                                                  
  int radius = 50;
  bresenham_circle(radius);
  for(;;){
  for(i=0;i<25;i++)
  {
  	yc+=10;
	xc+=10;
  	usleep(10000);
  	glClear(GL_COLOR_BUFFER_BIT);
  	bresenham_circle(radius);  
  }

  for(i=0;i<25;i++)
  {
  	yc-=10;
	xc+=10;
  	usleep(10000);
  	glClear(GL_COLOR_BUFFER_BIT);
	bresenham_circle(radius);  
  }
  	//for(i=0;i<30;i++)
  	//{
  	//	yc+=10;
  	//	usleep(10000);
  	//	glClear(GL_COLOR_BUFFER_BIT);
  	//	bresenham_circle(radius);  
  	//}
  }
}

void Init()
{

  glClearColor(0.0,0.0,0.0,0);
  glColor3f(1.0,1.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}

void main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("bresenham_circle");
  Init();
  glutDisplayFunc(circles);
  glutMainLoop();
}

4c.c
Displaying 4a.c.
