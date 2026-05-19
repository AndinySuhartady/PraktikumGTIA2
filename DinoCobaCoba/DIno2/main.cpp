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

#include <GL/glut.h>
#include <math.h>

// rotasi kamera
float angle = 0;

// fungsi bikin silinder
void drawCylinder(float radius, float height) {
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius, height, 20, 20);
    gluDeleteQuadric(quad);
}

// fungsi dinosaurus
void drawDino() {

    // ===== BADAN =====
    glPushMatrix();
    glColor3f(0.5, 0.35, 0.2);
    glScalef(2.0, 1.2, 1.0);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();

    // ===== LEHER =====
    glPushMatrix();
    glTranslatef(1.5, 0.8, 0.0);
    glRotatef(-30, 0, 0, 1);
    glColor3f(0.3, 0.6, 0.6);

    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, 0.2, 0.15, 3.0, 20, 20);
    gluDeleteQuadric(q);
    glPopMatrix();

    // ===== KEPALA =====
    glPushMatrix();
    glTranslatef(3.8, 2.5, 0.0);
    glColor3f(0.8, 0.4, 0.2);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    // ===== EKOR =====
    glPushMatrix();
    glTranslatef(-2.0, 0.3, 0.0);
    glRotatef(180, 0, 1, 0);
    glRotatef(20, 0, 0, 1);
    glColor3f(0.4, 0.3, 0.2);

    GLUquadric* q2 = gluNewQuadric();
    gluCylinder(q2, 0.25, 0.05, 2.5, 20, 20);
    gluDeleteQuadric(q2);
    glPopMatrix();

    // ===== KAKI (4) =====
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glTranslatef(i * 0.8, -1.2, j * 0.4);
            glColor3f(0.3, 0.25, 0.2);

            GLUquadric* q3 = gluNewQuadric();
            gluCylinder(q3, 0.2, 0.2, 1.2, 20, 20);
            gluDeleteQuadric(q3);

            glPopMatrix();
        }
    }
}

// display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5*sin(angle), 2, 5*cos(angle),
              0,0,0,
              0,1,0);

    drawDino();

    glutSwapBuffers();
}

// animasi kamera muter
void update(int value) {
    angle += 0.01;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// init
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1,1,1,1);
}

// main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Dinosaurus 3D");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
