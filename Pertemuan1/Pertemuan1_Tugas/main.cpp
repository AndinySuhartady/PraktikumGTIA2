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


void gambar(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. GL_LINE_STRIP
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.9,0.5);
        glVertex2f(-0.7,0.7);
        glVertex2f(-0.5,0.5);
        glVertex2f(-0.3,0.7);
    glEnd();

    // 2. GL_LINE_LOOP
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.2,0.5);
        glVertex2f(0.0,0.7);
        glVertex2f(0.2,0.5);
        glVertex2f(0.0,0.3);
    glEnd();

    // 3. GL_TRIANGLE_FAN
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.6,-0.1);
        glVertex2f(-0.8,-0.4);
        glVertex2f(-0.6,-0.6);
        glVertex2f(-0.4,-0.4);
        glVertex2f(-0.5,-0.2);
    glEnd();

    // 4. GL_TRIANGLE_STRIP
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-0.1,-0.6);
        glVertex2f(0.1,-0.2);
        glVertex2f(0.3,-0.6);
        glVertex2f(0.5,-0.2);
    glEnd();

    // 5. GL_QUADS
    glColor3f(1.0,0.0,1.0);
    glBegin(GL_QUADS);
        glVertex2f(0.4,0.6);
        glVertex2f(0.6,0.6);
        glVertex2f(0.6,0.4);
        glVertex2f(0.4,0.4);
    glEnd();

    // 6. GL_QUAD_STRIP
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.6,-0.2);
        glVertex2f(0.8,-0.2);
        glVertex2f(0.6,-0.5);
        glVertex2f(0.8,-0.5);
        glVertex2f(0.6,-0.8);
        glVertex2f(0.8,-0.8);
    glEnd();

    glFlush();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Andiny Khaerany Suhuartady");

    glutDisplayFunc(gambar);
    glClearColor(0.0,0.0,0.0,1.0);

    glutMainLoop();
    return 0;
}
