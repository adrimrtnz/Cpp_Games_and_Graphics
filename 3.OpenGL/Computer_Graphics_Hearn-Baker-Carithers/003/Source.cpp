#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

static const double TWO_PI = 6.2831853;
static const GLsizei WIDTH = 600;
static const GLsizei HEIGHT = 500;

using namespace std;

struct screenPt
{
	GLint x;
	GLint y;
};

typedef enum {
	limacon = 1,
	cardioid,
	threeLeaf,
	fourLeaf,
	spiral
} curveName;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void lineSegment(screenPt pt1, screenPt pt2)
{
	glBegin(GL_LINES);
		glVertex2i(pt1.x, pt2.y);
		glVertex2i(pt2.x, pt2.y);
	glEnd();
}

void drawCurve(GLint curveNum)
{
	/*	The limacon of Pascal is a modification of the circle equation
	 *	with the radius varying as r=a*cos(theta) + b, where a and b
	 *	are costants. A cardioid is a limacon with a = b.
	 *	Three-leaf and four-leaf curves are generated when r=a*cos(n*theta)
	 *	with n=3 and n=2, respectively.
	 *	A espiral is displayed when r is multiple of theta.
	 */

	const GLint a = 175, b = 60;

	GLfloat r, theta, dtheta = 1.0 / float(a);
	GLint x0 = 200, y0 = 250;					// Initial position
	screenPt curvePt[2];
	glColor3f(0, 0, 0);

	curvePt[0].x = x0;
	curvePt[0].y = y0;

	switch (curveNum) {
	case limacon:
		curvePt[0].x += a + b;
		break;
	case cardioid:
		curvePt[0].x += a + a;
		break;
	case threeLeaf:
		curvePt[0].x += a;
		break;
	case fourLeaf:
		curvePt[0].x += a;
		break;
	case spiral:
		break;
	default:
		break;
	}

	theta = dtheta;
	while (theta < TWO_PI) {
		switch (curveNum) {
		case limacon:
			r = a * cos(theta) + b;
			break;
		case cardioid:
			r = a * (1 + cos(theta));
			break;
		case threeLeaf:
			r = a * cos(3 * theta) + b;
			break;
		case fourLeaf:
			r = (a / 4.0) * theta;
			break;
		case spiral:
			break;
		default:
			break;
		}

		curvePt[1].x = x0 + r * cos(theta);
		curvePt[1].y = y0 + r * sin(theta);
		lineSegment(curvePt[0], curvePt[1]);

		curvePt[0].x = curvePt[1].x;
		curvePt[0].y = curvePt[1].y;
		theta += dtheta;
	}
}

void display(void)
{
	GLint curveNum;

	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window

	cout << "\nEnter the integer value corresponding to\none of the following curve names.\n";
	cout << "Press any other key to exit.\n";
	cout << "\n\t1-limacon\n\t2-cardioid\n\t3-threeLeaf\n\t4-fourLeaf\n\t5-spiral:" ;
	cin >> curveNum;

	if (curveNum >= 1 && curveNum <= 5) {
		drawCurve(curveNum);
	}
	else {
		exit(0);
	}

	glFlush();
}

void reshape(GLint w, GLint h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowPosition(WIDTH, HEIGHT);
	glutCreateWindow("Draw Curves");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}