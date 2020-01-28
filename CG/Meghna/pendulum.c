
Skip to content
Using Gmail with screen readers
36 of 4,278
cg lab4
Inbox
	x
Meghna Savit <meghna.savit99@gmail.com>
	
AttachmentsWed, Jan 22, 3:31 PM (6 days ago)
	
to me

3 Attachments
	
	
	

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


void bresenham_line(int x0,int y0, int x1, int y1)
{     
    int dx = fabs(x1 - x0), dy = fabs(y1 - y0);
    int p = 2*dy-dx;
    int x, y;

    if(x0>x1){
        x=x1;
        y=y1;
        x1=x0;
    }
    else{
        x=x0;
        y=y0;
    }

    glBegin(GL_POINTS);
        glColor3f(1.0,1.0,1.0);
        glVertex2i(x,y);
    glEnd();

    while(y<y1){
        y++;
        if(p>0){
            p = p + 2*dy;
        }
        else{
            x++;
            p= p + 2*dy - 2*dx;
       }
        glBegin(GL_POINTS);
            glColor3f(1.0,1.0,1.0);
            glVertex2i(x,y);
        glEnd();

    }
    glFlush();

}


void pendulum(void)
{
  bresenham_circle();
  bresenham_line(xc,yc+r,xc,yc+r+150);
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
  glutDisplayFunc(pendulum);
  glutMainLoop();
}

4b.c
Displaying 4a.c.
