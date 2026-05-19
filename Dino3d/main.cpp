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
#include <cmath>

// Sudut animasi kaki
float legAngle = 0.0f;
bool forward = true;

void drawCube(float x, float y, float z) {
    glPushMatrix();
    glScalef(x, y, z);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawDino() {
    // BADAN
    glColor3f(0.2f, 0.8f, 0.2f);
    glPushMatrix();
    glScalef(2.5f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    // KEPALA
    glPushMatrix();
    glTranslatef(1.8f, 0.8f, 0.0f);
    glScalef(1.2f, 1.2f, 1.2f);
    glutSolidCube(1.0);
    glPopMatrix();

    // MATA
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(2.2f, 0.8f, 0.6f);
    drawCube(0.2f, 0.2f, 0.2f);
    glPopMatrix();

    // EKOR
    glColor3f(0.2f, 0.7f, 0.2f);
    glPushMatrix();
    glTranslatef(-1.8f, 0.0f, 0.0f);
    glScalef(2.0f, 0.5f, 0.5f);
    glutSolidCube(1.0);
    glPopMatrix();

    // KAKI (4)
    float offset = sin(legAngle) * 30;

    // Kaki depan kiri
    glPushMatrix();
    glTranslatef(0.8f, -1.0f, 0.6f);
    glRotatef(offset, 1, 0, 0);
    drawCube(0.5f, 1.0f, 0.5f);
    glPopMatrix();

    // Kaki depan kanan
    glPushMatrix();
    glTranslatef(0.8f, -1.0f, -0.6f);
    glRotatef(-offset, 1, 0, 0);
    drawCube(0.5f, 1.0f, 0.5f);
    glPopMatrix();

    // Kaki belakang kiri
    glPushMatrix();
    glTranslatef(-0.8f, -1.0f, 0.6f);
    glRotatef(-offset, 1, 0, 0);
    drawCube(0.5f, 1.0f, 0.5f);
    glPopMatrix();

    // Kaki belakang kanan
    glPushMatrix();
    glTranslatef(-0.8f, -1.0f, -0.6f);
    glRotatef(offset, 1, 0, 0);
    drawCube(0.5f, 1.0f, 0.5f);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5, 3, 5, 0, 0, 0, 0, 1, 0);

    drawDino();

    glutSwapBuffers();
}

void update(int value) {
    legAngle += 0.1f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f); // langit biru
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Dino Jalan");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
