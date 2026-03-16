/*
 * FreeGLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone 
 * and torus shapes in FreeGLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/glut.h>

#include <stdlib.h>

void SegiEmpat (void)

{
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(-0.50, 0.50, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(-0.18, 0.18, 0.18, -0.18);
	glFlush();
}

int main (int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Segi Emoat");
	glutDisplayFunc(SegiEmpat);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
