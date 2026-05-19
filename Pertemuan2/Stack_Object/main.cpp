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

#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(0.0f, 0.20, 0.0);
            glVertex3f(0.0f, -0.20, 0.0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glPointSize(5.0f);
        glTranslatef(0.35, 0.35, 0.0);
        glBegin(GL_POINTS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(0.25, 0.25, 0.0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.50, 0.50, 0.0);
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); 
            glVertex3f(-0.05, -0.05, 0.0);

            glColor3f(0.0f, 1.0f, 0.0f); 
            glVertex3f(0.15, -0.05, 0.0);

            glColor3f(0.0f, 0.0f, 1.0f); 
            glVertex3f(-0.05, 0.05, 0.0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        #define PI 3.1415926535898
        glBegin(GL_LINE_LOOP);
            int circle_points = 100;
            int i;
            float angle;

            for (i = 0; i < circle_points; i++) {
                angle = 2 * PI * i / circle_points;
                glVertex2f(cos(angle), sin(angle));
            }
        glEnd();
    glPopMatrix();

    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Simple");
    glutDisplayFunc(RenderScene);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}
