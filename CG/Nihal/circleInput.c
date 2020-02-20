#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int R = 100;
int r = 40;
int begin = 1;
int x = 180;
int y = 180;

void circle_points(int x, int y,int xc, int yc)
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


void bresenham_circle(int xc, int yc, int r)
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
    circle_points(x,y,xc,yc);
  }
}

void draw_pixel(int x, int y) {
  glColor3f(0.0,1.0,1.0);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void draw_line(int x1, int x2, int y1, int y2) {
  int dx, dy, i, e;
  int incx, incy, inc1, inc2;
  int x,y;

  dx = x2-x1;
  dy = y2-y1;

  if (dx < 0) dx = -dx;
  if (dy < 0) dy = -dy;
  incx = 1;
  if (x2 < x1) incx = -1;
  incy = 1;
  if (y2 < y1) incy = -1;
  x = x1; y = y1;
  if (dx > dy) {
    draw_pixel(x, y);
    e = 2 * dy-dx;
    inc1 = 2*(dy-dx);
    inc2 = 2*dy;
    for (i=0; i<dx; i++) {
      if (e >= 0) {
        y += incy;
        e += inc1;
      }
      else
        e += inc2;
      x += incx;
      draw_pixel(x, y);
    }

  } else {
    draw_pixel(x, y);
    e = 2*dx-dy;
    inc1 = 2*(dx-dy);
    inc2 = 2*dx;
    for (i=0; i<dy; i++) {
      if (e >= 0) {
        x += incx;
        e += inc1;
      }
      else
        e += inc2;
      y += incy;
      draw_pixel(x, y);
    }
  }
}

// void idle(){
//     glutPostRedisplay();
// }

void draw_diagram(void){
  
  bresenham_circle(x,y,R);
  bresenham_circle(x,y,r);

  float bigCircleMid =(R/2)*sqrt(2);
  float smallCircleMid =(r/2)*sqrt(2);

  draw_line(x,x,y+r,y+R);
  draw_line(x + bigCircleMid,x + smallCircleMid,y + bigCircleMid,y + smallCircleMid);
  draw_line(x+r,x+R,y,y);
  draw_line(x + bigCircleMid,x + smallCircleMid,(x+y) - bigCircleMid,(x+y) - smallCircleMid);
  draw_line(x,x,y-r,y-R);
  draw_line(x-r,x-R,y,y);
  draw_line((x+y) - bigCircleMid,(x+y) - smallCircleMid,y + bigCircleMid,y + smallCircleMid);
  draw_line((x+y) - bigCircleMid,(x+y) - smallCircleMid,(x+y) - bigCircleMid,(x+y) - smallCircleMid);

  if(begin == 1)
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  begin = 0 ;

  glEnd();
  glFlush();
}

void Init()
{
  glClearColor(0.0,0.0,0.0,0);
  glColor3f(1.0,1.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}

void process_keys(unsigned char key, int X, int Y) 
{
  switch(key){

    case 'i'  : R++;
                r++;
                break;

    case 'd'  : R--;
                r--;
                break;

    case 'c'  : glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
                glFlush();
                break;

    default   : break;    
  }     

}

void mouse(int button, int Y , int X)
{
  switch(button){
    case GLUT_RIGHT_BUTTON  : exit(0);
                              break;
    case GLUT_LEFT_BUTTON   : x = X; y = Y+250;  
                              glutPostRedisplay();
                              break;
    default                 : break;
  }
}


void main(int argc, char **argv)
{

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("BALL-DIAGRAM");
  Init();
  glClear(GL_COLOR_BUFFER_BIT);
  glutDisplayFunc(draw_diagram);
  glutKeyboardFunc(process_keys);
  glutMouseFunc(mouse);
  glutMainLoop();
}

