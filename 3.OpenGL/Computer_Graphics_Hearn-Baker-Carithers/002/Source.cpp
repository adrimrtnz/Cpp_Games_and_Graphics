#include <GL/glut.h>
#include <math.h>

const double TWO_PI = 6.2831853;
GLsizei winWidth = 600, winHeight = 500;
GLint xRaster = 25, yRaster = 150;

GLubyte label[36] = {
	'J', 'a', 'n',	'F', 'e', 'b',	'M', 'a', 'r',
	'A', 'p', 'r',	'M', 'a', 'y',	'J', 'u', 'n',
	'J', 'u', 'l',	'A', 'u', 'g',	'S', 'e', 'p',
	'O', 'c', 't',	'N', 'o', 'v',	'D', 'e', 'c'
};

GLint dataValue[12] = {
	420, 342, 324, 310, 262, 185,
	190, 196, 217, 240, 312, 438
};

class screenPt
{
private:
	GLint x, y;

public:
	/* Default Constructor: itializes coordinate position to (0,0) */
	screenPt() {
		x = y = 0;
	}

	void setCoords(GLint xCoord, GLint yCoord) {
		x = xCoord;
		y = yCoord;
	}

	GLint getx() { return x; }
	GLint gety() { return y; }
};

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

void lineGraph(void)
{
	GLint month;
	GLint x = 30;					// Initialize x position for chart

	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 12; i++)
		glVertex2i(x + i * 50, dataValue[i]);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 12; i++) {	// Plot data as asterisk polymarkers
		glRasterPos2i(xRaster + i * 50, dataValue[i] - 4);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
	}

	glColor3f(0.0, 0.0, 0.0);
	xRaster = 20;					// Display chart labels
	for (month = 0; month < 12; month++) {
		glRasterPos2i(xRaster, yRaster);
		for (int i = 3 * month; i < 3 * month + 3; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
		}
		xRaster += 50;
	}
	glFlush();
}

void barChart(void)
{
	GLint month;
	glClear(GL_COLOR_BUFFER_BIT);	// Clear display window
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 12; i++) {
		glRecti(20 +  i*50, 165, 40 + i*50, dataValue[i]);
	}

	glColor3f(0.0, 0.0, 0.0);
	xRaster = 20;
	for (month = 0; month < 12; month++) {
		glRasterPos2i(xRaster, yRaster);
		for (int i = 3*month; i < 3 * month + 3; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
		xRaster += 50;
	}
	glFlush();
}


void pieChart(void)
{
	screenPt circCtr, piePtr;
	GLint radius = winWidth / 4;
	GLdouble sliceAngle, previousSliceAngle = 0.0;
	GLint nSlices = 12;
	GLfloat dataSum = 0.0;

	circCtr.setCoords(winWidth / 2, winHeight / 2);
	//circleMidpoint(circCtr, radius);

	for (int i = 0; i < nSlices; i++)
		dataSum += dataValue[i];

	for (int i = 0; i < nSlices; i++) {
		sliceAngle = TWO_PI * dataValue[i] / dataSum + previousSliceAngle;
		piePtr.setCoords(circCtr.getx() + radius * cos(sliceAngle), circCtr.gety() + radius * sin(sliceAngle));
		glBegin(GL_LINES);
			glVertex2i(circCtr.getx(), circCtr.gety());
			glVertex2i(piePtr.getx(), piePtr.gety());
		glEnd();
		previousSliceAngle = sliceAngle;
	}

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	pieChart();
	glFlush();
}

void winReshapeFcn(int newWidth, int newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Line Chart Data Plot");

	init();
	//glutDisplayFunc(lineGraph);
	//glutDisplayFunc(barChart);
	glutDisplayFunc(display);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}