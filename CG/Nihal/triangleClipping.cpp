#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

float minX, minY, maxX, maxY;
float fstX, fstY, sndX, sndY;
float fstA, fstB, sndA, sndB;
float fstC, fstD, sndC, sndD;

int code1[4] = { 0, 0, 0, 0 };
int code2[4] = { 0, 0, 0, 0 };
int code3[4] = { 0, 0, 0, 0 };
int code4[4] = { 0, 0, 0, 0 };
int code5[4] = { 0, 0, 0, 0 };
int code6[4] = { 0, 0, 0, 0 };

int getcode1(int x, int y) {
	if (y > maxY)
	{
		code1[0] = 1;
	}

	if (y < minY)
	{
		code1[1] = 1;
	}

	if (x > maxX)
	{
		code1[2] = 1;
	}

	if (x < minX)
	{
		code1[3] = 1;
	}

	int codeRes1 = code1[0] * 1000 + code1[1] * 100 + code1[2] * 10 + code1[3];

	return codeRes1;
}

int getcode2(int x, int y) {
	if (y > maxY)
	{
		code2[0] = 1;
	}

	if (y < minY)
	{
		code2[1] = 1;
	}

	if (x > maxX)
	{
		code2[2] = 1;
	}

	if (x < minX)
	{
		code2[3] = 1;
	}

	int codeRes2 = code2[0] * 1000 + code2[1] * 100 + code2[2] * 10 + code2[3];

	return codeRes2;
}

int getcode3(int x, int y) {
	if (y > maxY)
	{
		code3[0] = 1;
	}

	if (y < minY)
	{
		code3[1] = 1;
	}

	if (x > maxX)
	{
		code3[2] = 1;
	}

	if (x < minX)
	{
		code3[3] = 1;
	}

	int codeRes3 = code3[0] * 1000 + code3[1] * 100 + code3[2] * 10 + code3[3];

	return codeRes3;
}

int getcode4(int x, int y) {
	if (y > maxY)
	{
		code4[0] = 1;
	}

	if (y < minY)
	{
		code4[1] = 1;
	}

	if (x > maxX)
	{
		code4[2] = 1;
	}

	if (x < minX)
	{
		code4[3] = 1;
	}

	int codeRes4 = code4[0] * 1000 + code4[1] * 100 + code4[2] * 10 + code4[3];

	return codeRes4;
}

int getcode5(int x, int y) {
	if (y > maxY)
	{
		code5[0] = 1;
	}

	if (y < minY)
	{
		code5[1] = 1;
	}

	if (x > maxX)
	{
		code5[2] = 1;
	}

	if (x < minX)
	{
		code5[3] = 1;
	}

	int codeRes5 = code5[0] * 1000 + code5[1] * 100 + code5[2] * 10 + code5[3];

	return codeRes5;
}

int getcode6(int x, int y) {
	if (y > maxY)
	{
		code6[0] = 1;
	}

	if (y < minY)
	{
		code6[1] = 1;
	}

	if (x > maxX)
	{
		code6[2] = 1;
	}

	if (x < minX)
	{
		code6[3] = 1;
	}

	int codeRes6 = code6[0] * 1000 + code6[1] * 100 + code6[2] * 10 + code6[3];

	return codeRes6;
}

void generateCodeForPoints() {
	getcode1(fstX, fstY);
	getcode2(sndX, sndY);
	getcode3(fstA, fstB);
	getcode4(sndA, sndB);
	getcode5(fstC, fstD);
	getcode6(sndC, sndD);
}

void drawLine(int x0, int y0, int x1, int y1){
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
}

void cohenSuth1(){

	float m = (sndY-fstY)/(sndX - fstX);

	bool isReject = false;
	// Is both point accepted
	if (getcode1(fstX, fstY) == 0 && getcode2(sndX, sndY) == 0 && isReject == false)
	{
		drawLine(fstX, fstY, sndX, sndY);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			// Is both point rejected
			if (code1[i] == code2[i] && code1[i] == 1)
			{
				isReject = true;
				break;
			}


		}

		if (isReject)
		{
			cout << "Both point rejected" << endl;
		}
		else
		{
			//cout << "Not rejected" << endl;

			for (int i = 0; i < 4; i++)
			{
				if (code1[i] == 1)
				{
					switch (i)
					{

					case 0:
						fstX = fstX + (maxY-fstY)/m; 
						fstY = maxY;
						break;

					case 1:
						fstX = fstX + (minY-fstY)/m;
						fstY = minY;
						break;

					case 2:
						fstY = fstY + m*(maxX-fstX);
						fstX = maxX;
						break;

					case 3:
						fstY = fstY + m*(minX-fstX);
						fstX = minX;
						break;
					}
				}

				if (code2[i] == 1)
				{
					switch (i)
					{

					case 0:
						sndX = sndX + (maxY-sndY)/m;
						sndY = maxY;
						break;

					case 1:
						sndX = sndX + (minY-sndY)/m;
						sndY = minY;
						break;

					case 2:
						sndY = sndY + m*(maxX-sndX);
						sndX = maxX;
						break;

					case 3:
						sndY = sndY + m*(minX-sndX);
						sndX = minX;
						break;
					}
				}



			}

			drawLine(fstX, fstY, sndX, sndY);
		}
	}
}

void cohenSuth3(){

	float m = (sndD-fstD)/(sndC - fstC);

	bool isReject = false;
	// Is both point accepted
	if (getcode5(fstC, fstD) == 0 && getcode6(sndC, sndD) == 0 && isReject == false)
	{
		drawLine(fstC, fstD, sndC, sndD);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			// Is both point rejected
			if (code5[i] == code6[i] && code5[i] == 1)
			{
				isReject = true;
				break;
			}


		}

		if (isReject)
		{
			cout << "Both point rejected" << endl;
		}
		else
		{
			//cout << "Not rejected" << endl;

			for (int i = 0; i < 4; i++)
			{
				if (code5[i] == 1)
				{
					switch (i)
					{

					case 0:
						fstC = fstC + (maxY-fstD)/m; 
						fstD = maxY;
						break;

					case 1:
						fstC = fstC + (minY-fstD)/m;
						fstD = minY;
						break;

					case 2:
						fstD = fstD + m*(maxX-fstC);
						fstC = maxX;
						break;

					case 3:
						fstD = fstD + m*(minX-fstC);
						fstC = minX;
						break;
					}
				}

				if (code6[i] == 1)
				{
					switch (i)
					{

					case 0:
						sndC = sndC + (maxY-sndD)/m;
						sndD = maxY;
						break;

					case 1:
						sndC = sndC + (minY-sndD)/m;
						sndD = minY;
						break;

					case 2:
						sndD = sndD + m*(maxX-sndC);
						sndC = maxX;
						break;

					case 3:
						sndD = sndD + m*(minX-sndC);
						sndC = minX;
						break;
					}
				}



			}

			drawLine(fstC, fstD, sndC, sndD);
		}
	}
}

void cohenSuth2(){

	float m = (sndB-fstB)/(sndA - fstA);

	bool isReject = false;
	// Is both point accepted
	if (getcode3(fstA, fstB) == 0 && getcode4(sndA, sndB) == 0 && isReject == false)
	{
		drawLine(fstA, fstB, sndA, sndB);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			// Is both point rejected
			if (code3[i] == code4[i] && code3[i] == 1)
			{
				isReject = true;
				break;
			}


		}

		if (isReject)
		{
			cout << "Both point rejected" << endl;
		}
		else
		{
			//cout << "Not rejected" << endl;

			for (int i = 0; i < 4; i++)
			{
				if (code3[i] == 1)
				{
					switch (i)
					{

					case 0:
						fstA = fstA + (maxY-fstB)/m; 
						fstB = maxY;
						break;

					case 1:
						fstA = fstA + (minY-fstB)/m;
						fstB = minY;
						break;

					case 2:
						fstB = fstB + m*(maxX-fstA);
						fstA = maxX;
						break;

					case 3:
						fstB = fstB + m*(minX-fstA);
						fstA = minX;
						break;
					}
				}

				if (code4[i] == 1)
				{
					switch (i)
					{

					case 0:
						sndA = sndA + (maxY-sndB)/m;
						sndB = maxY;
						break;

					case 1:
						sndA = sndA + (minY-sndB)/m;
						sndB = minY;
						break;

					case 2:
						sndB = sndB + m*(maxX-sndA);
						sndA = maxX;
						break;

					case 3:
						sndB = sndB + m*(minX-sndA);
						sndA = minX;
						break;
					}
				}



			}

			drawLine(fstA, fstB, sndA, sndB);
		}
	}
}

void myInit(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}


void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(minX, minY, maxX, maxY);

	glColor3f(1.0, 1.0, 1.0);
	cohenSuth1();
	cohenSuth2();
	cohenSuth3();

	glFlush();
}

int main(int argc, char** argv)
{

	cout << "Enter MinX: "; cin >> minX;
	cout << "Enter MinY: "; cin >> minY;
	cout << "Enter MaxX: "; cin >> maxX;
	cout << "Enter MaxY: "; cin >> maxY;

	cout << "Enter x1: "; cin >> fstX;
	cout << "Enter y1: "; cin >> fstY;
	cout << "Enter x2: "; cin >> sndX;
	cout << "Enter y2: "; cin >> sndY;
	cout << "Enter x3: "; cin >> sndA;
	cout << "Enter y3: "; cin >> sndB;

	fstA = sndX; fstB=sndY;
	fstC=sndA ; fstD=sndB;
	sndC = fstX; sndD = fstY;

	// 4 digit code generator
	generateCodeForPoints();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Clipping with Cohen-Sutherland algorithm");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

	return 0;

}