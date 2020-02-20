#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int xc,yc,r;

void circle_points(int x, int y)
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


void bresenham_circle(void)
{
  int x=0,y=r;
  float d=3-2*r;


  while(x < y)
  {
    x = x + 1;
    if(d < 0)
      d = d + 4*x+6;
    else
    {
      y = y - 1;
      d = d + 4*(x - y) + 10;
    }
    circle_points(x,y);
  }
  glFlush();
}


void Init()
{
  glClearColor(0.0,0.0,0.0,0);
  glColor3f(1.0,1.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}

void main(int argc, char **argv)
{
  printf("Enter the x coordinate of centre ");
  scanf("%d",&xc);
  printf("Enter the y coordinate of centre ");
  scanf("%d",&yc);
  printf("Enter the radius of the circle ");
  scanf("%d",&r);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("Bresenham");
  Init();
  glClear(GL_COLOR_BUFFER_BIT);
  glutDisplayFunc(bresenham_circle);
  glutMainLoop();
}

