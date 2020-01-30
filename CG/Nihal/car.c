#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int max(int a, int b)
{
    return a >= b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void initialize()
{
    glClearColor(0, 0, 0, 1);
    glVertex3f(0, 1, 0);
    glPointSize(1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-780, 780, -420, 420);
}

void drawBresenhamLine(int X1, int Y1, int X2, int Y2)
{
    int incx, incy, inc1, inc2;
    int x, y;
    int dx, dy;
    dx = X2 - X1;
    dy = Y2 - Y1;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    incx = 1;
    if (X2 < X1)
        incx = -1;
    incy = 1;
    if (Y2 < Y1)
        incy = -1;
    x = X1;
    y = Y1;

    int fraction, i;
    int fractionIncrement1;
    int fractionIncrement2;
    if (dx > dy)
    {
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        fraction = 2 * dy - dx;
        fractionIncrement1 = 2 * (dy - dx);
        fractionIncrement2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (fraction >= 1)
            {
                y += incy;
                fraction += fractionIncrement1;
            }
            else
                fraction += fractionIncrement2;
            x += incx;
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
    }

    else
    {
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        fraction = 2 * dx - dy;
        fractionIncrement1 = 2 * (dx - dy);
        fractionIncrement2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (fraction >= 1)
            {
                x += incx;
                fraction += fractionIncrement1;
            }
            else
                fraction += fractionIncrement2;
            y += incy;
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
    }
}

void plotPoints(int x,int y,int p,int q){
    glBegin(GL_POINTS);
        glVertex2i(x+p, y+q);
        glVertex2i(x+p, -y+q);
        glVertex2i(-x+p, -y+q);
        glVertex2i(-x+p, y+q);
        glVertex2i(y+p, x+q);
        glVertex2i(-y+p, x+q);
        glVertex2i(y+p, -x+q);
        glVertex2i(-y+p, -x+q);
    glEnd();
}

void plot4Points(int x,int y,int p,int q){
    glBegin(GL_POINTS);
        glVertex2i(x+p, y+q);
        glVertex2i(-x+p, y+q);
        glVertex2i(y+p, x+q);
        glVertex2i(-y+p, x+q);
    glEnd();
}

void drawBresenhamCircle(int X1, int Y1, int R)
{   
    int p,q,x,y,r,d;
    p = X1,q = Y1;
    r = R;
    d = 3 - 2*r;
    x = 0;
    y = r;
    while(x<y){
        plotPoints(x,y,p,q);
        if(d<0){
            d = d+4*x+6;
            x++;
        }else{
            d = d + 4*(x-y) + 10;
            x++;
            y--;
        }
    }
}

void drawBresenhamHalfCircle(int X1, int Y1, int R)
{   
    int p,q,x,y,r,d;
    p = X1,q = Y1;
    r = R;
    d = 3 - 2*r;
    x = 0;
    y = r;
    while(x<y){
        plot4Points(x,y,p,q);
        if(d<0){
            d = d+4*x+6;
            x++;
        }else{
            d = d + 4*(x-y) + 10;
            x++;
            y--;
        }
    }
}

float angle=0.0;
float xpos = 0.0;
int direction = 1;
void idle(){
    glutPostRedisplay();
}

void drawBresenhamPattern()
{
    int x = 100;
    int y = -150;
    glClear(GL_COLOR_BUFFER_BIT);
    drawBresenhamLine(-780,-200,780,-200);
    glPushMatrix();

    glTranslatef(xpos,0,0);

    drawBresenhamLine(-160,-150,-200,-150);
    drawBresenhamLine(160,-150,200,-150);
    drawBresenhamLine(200,-150,200,-50);
    drawBresenhamLine(-200,-150,-200,-50);
    drawBresenhamLine(-100,-50,-200,-50);
    drawBresenhamLine(100,-50,200,-50);
    drawBresenhamLine(100,-50,100,50);
    drawBresenhamLine(-100,-50,-100,50);
    drawBresenhamLine(-100,50,100,50);
    drawBresenhamLine(40,-150,-40,-150);

    drawBresenhamHalfCircle(-100,-150,60);
    drawBresenhamHalfCircle(100,-150,60);

    drawBresenhamCircle(-100,-150,50);
    drawBresenhamCircle(-100,-150,10);
    drawBresenhamCircle(100,-150,50);
    drawBresenhamCircle(100,-150,10);
    
    

    glPushMatrix();
        glTranslatef(-100,-150,0);
        glRotatef(angle, 0, 0,1.0f);
        drawBresenhamLine(0,10,0,50);
        drawBresenhamLine(0,-10,0,-50);
        drawBresenhamLine(10,0,50,0);
        drawBresenhamLine(-10,0,-50,0);
        drawBresenhamLine(7,7,35,35);
        drawBresenhamLine(7,-7,35,-35);
        drawBresenhamLine(-7,7,-35,35);
        drawBresenhamLine(-7,-7,-35,-35);
    glPopMatrix();
    
    glTranslatef(100,-150,0);
    glRotatef(angle, 0, 0,1.0f);
    drawBresenhamLine(0,10,0,50);
    drawBresenhamLine(0,-10,0,-50);
    drawBresenhamLine(10,0,50,0);
    drawBresenhamLine(-10,0,-50,0);
    drawBresenhamLine(7,7,35,35);
    drawBresenhamLine(7,-7,35,-35);
    drawBresenhamLine(-7,7,-35,35);
    drawBresenhamLine(-7,-7,-35,-35);

    glPopMatrix();
    glFlush();
    
    if(direction){
        xpos+=0.1;
        angle-=0.04;
    }else{
        xpos-=0.1;
        angle+=0.04;
    }
    // printf("%f\n",xpos);
    if(xpos>=580)
        direction = 0;
    else if(xpos<=-580)
        direction = 1;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 500);
    glutInitWindowPosition(100, 0);

    glutCreateWindow("Bresenham Circle algorithm");

    initialize();
    glutDisplayFunc(drawBresenhamPattern);
    glutIdleFunc(idle);
    glutMainLoop();
}