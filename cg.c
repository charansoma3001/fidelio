//Bresenham

#include <GL/glut.h> 
#include <stdio.h> 
int x1, y1, x2, y2;
void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}
void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void draw_line(int x1, int x2, int y1, int y2)
{
	int dx, dy, i, e, x, y, incx, incy, inc1, inc2;
	dx = x2 - x1;
	dy = y2 - y1;
	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;

	incx = 1;
	if (x2 < x1)
		incx = -1;

	incy = 1;
	if (y2 < y1)
		incy = -1;

	x = x1; y = y1;
	if (dx > dy)
	{
		draw_pixel(x, y);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (e >= 0)
			{
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}
	}
	else
	{
		draw_pixel(x, y);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (e >= 0)
			{
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
void myDisplay()
{
	draw_line(x1, x2, y1, y2);
	glFlush();
}
int main(int argc, char** argv)
{
	printf("Enter (x1, y1, x2, y2)\n");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Line Drawing");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}

//Triangle

#include<stdio.h>
#include<GL/glut.h>
int x, y;
int rflag = 0;
void draw_pixel(float x1, float y1)
{
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
}
void triangle()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(250, 400);
	glVertex2f(400, 100);
	glEnd();
}
float th = 0.0;
float trx = 0.0, trY = 0.0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	if (rflag == 1)
	{
		trx = 0.0;
		trY = 0.0;
		th += 0.5;
		draw_pixel(0.0, 0.0);
	}
	if (rflag == 2)
	{
		trx = x;
		trY = y;
		th += 0.5;
		draw_pixel(x, y);
	}
	glTranslatef(trx, trY, 0.0);
	glRotatef(th, 0.0, 0.0, 1.0);
	glTranslatef(-trx, -trY, 0.0);
	triangle();
	glutPostRedisplay();
	glutSwapBuffers();
}
void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}
void rotateMenu(int option)
{
	if (option == 1)
		rflag = 1;
	if (option == 2)
		rflag = 2;
	if (option == 3)
		rflag = 3;
}
int main(int argc, char* argv)
{
	printf("Enter fixed point (x,y) for rotation : \n");
	scanf_s("%d%d", &x, &y);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("create and rotate triangle");
	myinit();
	glutDisplayFunc(display);
	glutCreateMenu(rotateMenu);
	glutAddMenuEntry("rotate around origin", 1);
	glutAddMenuEntry("rotate around fixed point", 2);
	glutAddMenuEntry("stop rotation", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}


//Cube1

#include<stdlib.h>
#include<GL/glut.h>
GLfloat vertices[][3] = { {-1.0,-1.0,-1.0},
                         {1.0,-1.0,-1.0},
                         {1.0,1.0,-1.0},
                         {-1.0,1.0,-1.0},
                         {-1.0,-1.0,1.0},
                         {1.0,-1.0,1.0},
                         {1.0,1.0,1.0},
                         {-1.0,1.0,1.0}
};
GLfloat color[][3] = {
                        {0.0,0.0,0.0},
                        {1.0,0.0,0.0},
                        {1.0,1.0,0.0},
                        {0.0,1.0,0.0},
                        {0.0,0.0,1.0},
                        {1.0,0.0,1.0},
                        {1.0,1.0,1.0},
                        {0.0,1.0,1.0}
};

void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glColor3fv(color[a]);
    glVertex3fv(vertices[a]);
    glColor3fv(color[b]);
    glVertex3fv(vertices[b]);
    glColor3fv(color[c]);
    glVertex3fv(vertices[c]);
    glColor3fv(color[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}

void colorcube(void)
{
    polygon(0, 3, 2, 1);
    polygon(2, 3, 7, 6);
    polygon(0, 4, 7, 3);
    polygon(1, 2, 6, 5);
    polygon(4, 5, 6, 7);
    polygon(0, 1, 5, 4);
}

static GLfloat theta[] = { 0.0,0.0,0.0 };
static GLint axis = 2;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    colorcube();
    glutSwapBuffers();
}

void spinCube()
{
    theta[axis] += 0.05;
    if (theta[axis] > 360.0)
    {
        theta[axis] -= 360.0;

    }
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        axis = 0;
    }
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        axis = 1;
    }

    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        axis = 2;
    }
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    {
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
            2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    }
    else
    {
        glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
            2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("color cube viewer");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutIdleFunc(spinCube);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

//Cube2

#include<stdio.h>
#include<stdlib.h> 
#include<GL/glut.h> 
GLfloat vertices[][3] = { {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0},{-1.0,-1.0,1.0},
{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0} };
GLfloat colors[][3] = { {0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0},
{1.0,1.0,1.0},{0.0,1.0,1.0} };
void polygon(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}
void colorcube() {
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}
static GLfloat theta[] = { 0.0,0.0,0.0 };
static GLint axis = 2;
static GLdouble viewer[] = { 0.0,0.0,5.0 };
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	colorcube();
	glFlush();
	glutSwapBuffers();
}
void mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
	theta[axis] += 2.0;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	display();
}
void keys(unsigned char key, int x, int y) {
	if (key == 'x') viewer[0] -= 1.0;
	if (key == 'X') viewer[0] += 1.0;
	if (key == 'y') viewer[1] -= 1.0;
	if (key == 'Y') viewer[1] += 1.0;
	if (key == 'z') viewer[2] -= 1.0;
	if (key == 'Z') viewer[2] += 1.0;
	display();
}
void myReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, 2.0,
			20.0);
	else
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, 2.0,
			20.0);
	glMatrixMode(GL_MODELVIEW);
}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube Viewer");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

//Cohen

#include <stdio.h> 
#include <GL\glut.h>  
double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;
const int RIGHT = 8; const int LEFT = 2;
const int TOP = 4; const int BOTTOM = 1;
int ComputeOutCode(double x, double y)
{
	int code = 0;   if (y > ymax)
		code |= TOP;
	//above the clip window    
	else if (y < ymin)
		code |= BOTTOM;
	//below the clip window    
	if (x > xmax)
		code |= RIGHT;
	//to the right of clip window
	else if (x < xmin)
		code |= LEFT;
	//to the left of clip window    
	return code;
}
void CohenSutherland(double x0, double y0, double x1, double y1)
{
	int outcode0, outcode1, outcodeOut;
	int accept = 0, done = 0;
	outcode0 = ComputeOutCode(x0, y0);
	outcode1 = ComputeOutCode(x1, y1);
	do {
		if (!(outcode0 | outcode1))
		{
			accept = 1;      done = 1;
		}
		else if (outcode0 & outcode1)         done = 1;
		else {
			double x, y;
			outcodeOut = outcode0 ? outcode0 : outcode1;
			if (outcodeOut & TOP)
			{
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			}
			else if (outcodeOut & BOTTOM)
			{
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			}
			else if (outcodeOut & RIGHT)
			{
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			}
			else
			{
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}
			if (outcodeOut == outcode0)
			{
				x0 = x;     y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			}
			else {
				x1 = x;     y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}
	} while (!done);
	if (accept)
	{
		double sx = (xvmax - xvmin) / (xmax - xmin);
		double sy = (yvmax - yvmin) / (ymax - ymin);
		double vx0 = xvmin + (x0 - xmin) * sx;
		double vy0 = yvmin + (y0 - ymin) * sy;
		double vx1 = xvmin + (x1 - xmin) * sx;
		double vy1 = yvmin + (y1 - ymin) * sy;
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
		glEnd();  glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex2d(vx0, vy0);
		glVertex2d(vx1, vy1);
		glEnd();
	}
}
void display()
{
	double x0 = 60, y0 = 20, x1 = 80, y1 = 120;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);    glVertex2d(x0, y0);
	glVertex2d(x1, y1);  glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();
	CohenSutherland(x0, y0, x1, y1);
	glFlush();
}
void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Cohen Suderland Line Clipping Algorithm");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}


//Teapot

#include<GL/glut.h>
void obj(double tx, double ty, double tz, double sx, double sy, double sz)
{
	glRotated(50, 0, 1, 0);
	glRotated(10, -1, 0, 0);
	glRotated(11.7, 0, 0, -1);
	glTranslated(tx, ty, tz);
	glScaled(sx, sy, sz);
	glutSolidCube(1);
	glLoadIdentity();
}
void display()
{
	glViewport(0, 0, 700, 700);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	obj(0, 0, 0.5, 1, 1, 0.04);  // three walls
	obj(0, -0.5, 0, 1, 0.04, 1);
	obj(-0.5, 0, 0, 0.04, 1, 1);
	obj(0, -0.3, 0, 0.02, 0.2, 0.02);   // four table legs
	obj(0, -0.3, -0.4, 0.02, 0.2, 0.02);
	obj(0.4, -0.3, 0, 0.02, 0.2, 0.02);
	obj(0.4, -0.3, -0.4, 0.02, 0.2, 0.02);
	obj(0.2, -0.18, -0.2, 0.6, 0.02, 0.6);  // table top
	glRotated(50, 0, 1, 0);
	glRotated(10, -1, 0, 0);
	glRotated(11.7, 0, 0, -1);
	glTranslated(0.3, -0.1, -0.3);
	glutSolidTeapot(0.09);
	glFlush();
	glLoadIdentity();
}

void main()
{
	float ambient[] = { 1,1,1,1 };
	float light_pos[] = { 27,80,2,3 };
	glutInitWindowSize(700, 700);
	glutCreateWindow("scene");
	glutDisplayFunc(display);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}


//Tetrahedron

#include <GL/glut.h> 
/* initial triangle */
typedef GLfloat point[3];
point v[] = { {30.0, 50.0, 100.0}, {0.0, 450.0, -150.0}, {-350.0, -400.0, -150.0}, {350.0, -400.0, -150.0} };
int n; /* number of recursive steps */
void triangle(point a, point b, point c)
{
	glBegin(GL_TRIANGLES); /* display one triangle */
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void tetra(point a, point b, point c, point d)
{
	glColor3f(1.0, 0.0, 0.0);
	triangle(a, b, c);
	glColor3f(0.0, 1.0, 0.0);
	triangle(a, c, d);
	glColor3f(0.0, 0.0, 1.0);
	triangle(a, d, b);
	glColor3f(0.0, 0.0, 0.0);
	triangle(b, d, c);
}
void divide_tetra(point a, point b, point c, point d, int m)
{
	/* tretra subdivision using vertex numbers */
	float mid[6][3];
	int j;
	if (m > 0)
	{
		for (j = 0; j < 3; j++) mid[0][j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 3; j++) mid[1][j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) mid[2][j] = (a[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) mid[3][j] = (b[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) mid[4][j] = (c[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) mid[5][j] = (b[j] + d[j]) / 2;
		divide_tetra(a, mid[0], mid[1], mid[2], m - 1);
		divide_tetra(mid[0], b, mid[3], mid[5], m - 1);
		divide_tetra(mid[1], mid[3], c, mid[4], m - 1);
		divide_tetra(mid[2], mid[5], mid[4], d, m - 1);
	}
	else tetra(a, b, c, d);
}
void display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divide_tetra(v[0], v[1], v[2], v[3], n);
	glFlush();
}
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-499.0, 499.0, -499.0, 499.0, -499.0, 499.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	printf("\n Enter the number of division:\n");
	scanf("%d", &n);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D gasket");
	glEnable(GL_DEPTH_TEST);
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}

//Scanline

#include <GL/glut.h> 
#include <stdlib.h> 
float x1, x2, x3, x4, y1, y2, y3, y4;
void edgedetect(float x1, float y1, float x2, float y2, int* le, int* re)
{
	float mx, x, temp;
	int i;
	if ((y2 - y1) < 0)
	{
		temp = y1; y1 = y2; y2 = temp;
		temp = x1; x1 = x2; x2 = temp;
	}
	if ((y2 - y1) != 0)
		mx = (x2 - x1) / (y2 - y1);
	else
		mx = x2 - x1;
	x = x1;
	for (i = y1; i <= y2; i++)
	{
		if (x < (float)le[i])
			le[i] = (int)x;
		if (x > (float)re[i])
			re[i] = (int)x;
		x += mx;
	}
}
void draw_pixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	int le[500], re[500];
	int i, y;
	for (i = 0; i < 500; i++)
	{
		le[i] = 500;
		re[i] = 0;
	}
	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x4, y4, le, re);
	edgedetect(x4, y4, x1, y1, le, re);
	for (y = 0; y < 500; y++)
	{
		if (le[y] <= re[y])
			for (i = (int)le[y]; i < (int)re[y]; i++)
				draw_pixel(i, y);
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
void select(int ch)
{
	switch (ch)
	{
	case 1:
		x1 = 200.0; y1 = 200.0; x2 = 100.0; y2 = 300.0; x3 = 200.0; y3 = 400.0; x4 = 300.0; y4 = 300.0;
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);
		glEnd();
		scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
		glFlush();
		glutPostRedisplay();
		break;

	case 2:
		x1 = 200.0; y1 = 200.0; x2 = 100.0; y2 = 300.0; x3 = 200.0; y3 = 400.0; x4 = 300.0; y4 = 300.0;
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);
		glEnd();
		scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
		glFlush();
		glutPostRedisplay();
		break;
	case 3:
		x1 = 200.0; y1 = 200.0; x2 = 100.0; y2 = 300.0; x3 = 200.0; y3 = 400.0; x4 = 300.0; y4 = 300.0;
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);
		glEnd();
		scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
		glFlush();
		glutPostRedisplay();
		break;
	}
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("scan");
	myinit();
	glutDisplayFunc(display);
	glutCreateMenu(select);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
