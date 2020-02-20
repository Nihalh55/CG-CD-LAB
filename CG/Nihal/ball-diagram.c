#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

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

float angle=0.0;
float xpos = 0.0;
int direction = 1;
void idle(){
    glutPostRedisplay();
}

void draw_diagram(void){

  glClear(GL_COLOR_BUFFER_BIT);
  draw_line(40,600,80,80);
  
  glPushMatrix();
    glTranslatef(xpos,0,0);

    glPushMatrix();
    // glTranslatef(xpos+180,180,0);
    // glRotatef(angle, 0.0f, 0.0f, 1.0f);
    bresenham_circle(180,180,100);
    bresenham_circle(180,180,40);

      float bigCircleMid = 180 + 50*sqrt(2);
      float smallCircleMid = 180 + 20*sqrt(2);

      draw_line(180,180,220,280);
      draw_line(bigCircleMid,smallCircleMid,bigCircleMid,smallCircleMid);
      draw_line(220,280,180,180);
      draw_line(bigCircleMid,smallCircleMid,360 - bigCircleMid,360 - smallCircleMid);
      draw_line(180,180,140,80);
      draw_line(140,80,180,180);
      draw_line(360 - bigCircleMid,360 - smallCircleMid, bigCircleMid,smallCircleMid);
      draw_line(360 - bigCircleMid,360 - smallCircleMid,360 - bigCircleMid,360 - smallCircleMid);

  glPopMatrix();

  glEnd();
  glFlush();
  if(direction){
        xpos+=0.1;
        angle-=0.01;
    }else{
        xpos-=0.1;
        angle+=0.01;
    }
    // printf("%f\n",xpos);
    if(xpos>=400)
        direction = 0;
    else if(xpos<=-150)
        direction = 1;
}

void Init()
{
  glClearColor(0.0,0.0,0.0,0);
  glColor3f(1.0,1.0,1.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}

void main(int argc, char **argv)
{
  // printf("Enter the x coordinate of centre ");
  // scanf("%d",&xc);
  // printf("Enter the y coordinate of centre ");
  // scanf("%d",&yc);
  // printf("Enter the radius of the circle ");
  // scanf("%d",&r);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("BALL-DIAGRAM");
  Init();
  glClear(GL_COLOR_BUFFER_BIT);
  glutDisplayFunc(draw_diagram);
  glutIdleFunc(idle);
  glutMainLoop();
}

