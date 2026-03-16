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



void Garis(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2.0f);     // ketebalan garis
    glBegin(GL_LINES);     // mulai menggambar garis

    glColor3f(1.0f, 1.0f, 1.0f); // warna putih
    glVertex3f(0.00, 0.20, 0.0); // titik awal
    glVertex3f(0.00, -0.20, 0.0); // titik akhir

    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Membuat Garis");

    glutDisplayFunc(Garis);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glutMainLoop();
    return 0;
}

