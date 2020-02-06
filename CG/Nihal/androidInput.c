#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

//semicircle
int SR = 60;
int SX = 200;
int SY = 200;
//eyes
int ER = 10;
int EX1 = 215;
int EY1 = 215;
int EX2 = 185;
int EY2 = 215;

int begin = 1;
float xpos = 0.0;
float scale = 1.0;

void semicircle_points(int x, int y,int xc, int yc)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}

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

void bresenham_semicircle(int xc, int yc, int r)
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
    semicircle_points(x,y,xc,yc);
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

void draw_diagram(void){
  
  glClear(GL_COLOR_BUFFER_BIT);

  glTranslatef(xpos,0,0);
  glScalef(scale, scale, 1.0f);
  // Head
  bresenham_semicircle(SX,SY,SR);
  bresenham_circle(EX1,EY1,ER);
  bresenham_circle(EX2,EY2,ER);
  draw_line(SX-SR,SX+SR,SY,SY);

  // Hair
  draw_line(SX+(SR/2)*sqrt(2) , SX+(SR)*sqrt(2) , SY+(SR/2)*sqrt(2) , SY+(SR)*sqrt(2));
  draw_line(SX-(SR/2)*sqrt(2) , SX-(SR)*sqrt(2) , SY+(SR/2)*sqrt(2) , SY+(SR)*sqrt(2));

  //Draw Body
  draw_line(SX-60,SX+60,SY-20,SY-20);
  draw_line(SX+60,SX+60,SY-20,SY-100);
  draw_line(SX-60,SX+60,SY-100,SY-100);
  draw_line(SX-60,SX-60,SY-20,SY-100);

  //Draw arm1
  glPushMatrix();
  draw_line(SX+60,SX+80,SY-20,SY-20);
  draw_line(SX+80,SX+80,SY-20,SY-100);
  draw_line(SX+60,SX+80,SY-100,SY-100);
  draw_line(SX+60,SX+60,SY-20,SY-100);
  glPopMatrix();

  //Draw arm2
  glPushMatrix();
  draw_line(SX-60,SX-80,SY-20,SY-20);
  draw_line(SX-80,SX-80,SY-20,SY-100);
  draw_line(SX-60,SX-80,SY-100,SY-100);
  draw_line(SX-60,SX-60,SY-20,SY-100);
  glPopMatrix();

  //Draw leg1
  draw_line(SX+20,SX+20,SY-100,SY-120);
  draw_line(SX+20,SX+5,SY-120,SY-120);
  draw_line(SX+5,SX+5,SY-100,SY-120);

  //Draw leg2
  draw_line(SX-20,SX-20,SY-100,SY-120);
  draw_line(SX-20,SX-5,SY-120,SY-120);
  draw_line(SX-5,SX-5,SY-100,SY-120);

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

    case 'i'  : scale=1.1;
                break;

    case 'd'  : scale-=0.1;
                if(scale==0.0){
                  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
                  glFlush();
                }
                break;

    case 'c'  : glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
                glFlush();
                xpos = 0;
                break;

    case 'e'  : exit(0);
                break;

    case 'h'  : xpos = -5;
                break;

    case 't'  : xpos = 5;
                break;

    default   : break;    
  }     

}

void mouse(int button, int Y , int X)
{
  switch(button){
    case GLUT_RIGHT_BUTTON  : exit(0);
                              break;
    case GLUT_LEFT_BUTTON   : glutPostRedisplay();
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
  glutCreateWindow("ANDROID");
  Init();
  glClear(GL_COLOR_BUFFER_BIT);
  glutDisplayFunc(draw_diagram);
  glutKeyboardFunc(process_keys);
  glutMouseFunc(mouse);
  glutMainLoop();
}

