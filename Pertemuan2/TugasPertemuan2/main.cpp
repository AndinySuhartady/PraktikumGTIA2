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
#include <math.h>

float angleRoda = 0;
float posisiMobil = 0;
float radius = 0.2;
// fungsi lingkaran roda

void lingkaran()
{
    float angle;

    glBegin(GL_TRIANGLE_FAN);

    // pusat roda (kuning kecil)
    glColor3f(1.0, 1.0, 0.2);
    glVertex2f(0.0, 0.0);

    for(int i=0;i<=100;i++)
    {
        angle = 2 * 3.1416 * i / 100;

        float x = radius * cos(angle);
        float y = radius * sin(angle);

        if(i < 30)
            glColor3f(0.73,0.33,0.83); // Medium Orchid (#BA55D3)

        else if(i < 70)
            glColor3f(0.9,0.9,0.98); // Lavender

        else
            glColor3f(1.0,0.0,1.0); // Fuchsia (#FF00FF)

        glVertex2f(x,y);
    }

    glEnd();
}

// bunga di mobil
void bunga()
{
    glColor3f(1.0,0.7,0.8);

    for(int i=0;i<5;i++)
    {
        glPushMatrix();
        glRotatef(i*72,0,0,1);

        glBegin(GL_POLYGON);
            glVertex2f(0.0,0.05);
            glVertex2f(0.05,0.1);
            glVertex2f(0.1,0.05);
            glVertex2f(0.05,0.0);
        glEnd();

        glPopMatrix();
    }

    glColor3f(1,1,0);

    glBegin(GL_POLYGON);
        glVertex2f(-0.02,-0.02);
        glVertex2f(0.02,-0.02);
        glVertex2f(0.02,0.02);
        glVertex2f(-0.02,0.02);
    glEnd();
}


void mobil()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(posisiMobil,0,0);

    glColor3f(0.6,0.2,0.8);

    glBegin(GL_POLYGON);
        glVertex2f(-0.8,-0.2);
        glVertex2f(0.8,-0.2);
        glVertex2f(0.8,0.2);
        glVertex2f(-0.8,0.2);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.4,0.2);
        glVertex2f(0.4,0.2);
        glVertex2f(0.25,0.5);
        glVertex2f(-0.25,0.5);
    glEnd();

    glPushMatrix();
        bunga();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.5,-0.35,0);
        glRotatef(angleRoda,0,0,1);
        glColor3f(0,0,0);
        lingkaran();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5,-0.35,0);
        glRotatef(angleRoda,0,0,1);
        glColor3f(0,0,0);
        lingkaran();
    glPopMatrix();

    glPopMatrix();

    glFlush();
}


void animasi(int value)
{
    angleRoda += 5;
    posisiMobil += 0.01;

    if(posisiMobil > 1.2)
        posisiMobil = -1.2;

    glutPostRedisplay();
    glutTimerFunc(50,animasi,0);
}



int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Mobil Ungu Bunga");

    glClearColor(1,1,1,1);

    glutDisplayFunc(mobil);
    glutTimerFunc(50,animasi,0);

    glutMainLoop();
}

