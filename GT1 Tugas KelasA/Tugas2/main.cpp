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

// State transformasi
float tx    = -1.0f;   // posisi X sepeda
float angle =  0.0f;   // sudut rotasi roda
float R     =  0.18f;  // jari-jari roda

// Fungsi menggambar lingkaran
void drawCircle(float cx, float cy, float r, int seg) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < seg; i++) {
        float a = 2.0f * 3.1415926f * i / seg;
        glVertex2f(cx + cos(a) * r, cy + sin(a) * r);
    }
    glEnd();
}

// ==========================
// DISPLAY
// ==========================
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float w1x = tx - 0.3f, wy  = -0.1f;  
    float w2x = tx + 0.3f, wy2 = -0.1f;  
    float topX = tx, topY = 0.2f;  

    glColor3f(0.2f, 0.2f, 0.8f);
    glLineWidth(2.5f);

    // BODY SEPEDA
    glBegin(GL_LINE_STRIP);
        glVertex2f(w1x, wy);
        glVertex2f(topX, topY);
        glVertex2f(w2x, wy2);
    glEnd();

    // SETANG
    glBegin(GL_LINES);
        glVertex2f(topX - 0.12f, topY + 0.06f);
        glVertex2f(topX + 0.12f, topY + 0.06f);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);

    // RODA BELAKANG
    glPushMatrix();
        glTranslatef(w1x, wy, 0.0f);
        glRotatef(-angle, 0.0f, 0.0f, 1.0f);

        drawCircle(0.0f, 0.0f, R, 30);

        glColor3f(1.0f, 0.5f, 0.0f);
        glPointSize(6.0f);
        glBegin(GL_POINTS);
            glVertex2f(R - 0.02f, 0.0f);
        glEnd();
    glPopMatrix();

    // RODA DEPAN
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
        glTranslatef(w2x, wy2, 0.0f);
        glRotatef(-angle, 0.0f, 0.0f, 1.0f);

        drawCircle(0.0f, 0.0f, R, 30);

        glColor3f(1.0f, 0.5f, 0.0f);
        glPointSize(6.0f);
        glBegin(GL_POINTS);
            glVertex2f(R - 0.02f, 0.0f);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

// ==========================
// UPDATE ANIMASI
// ==========================
void update(int value) {

    tx += 0.003f;

    // rotasi roda sesuai jarak tempuh
    angle = (tx / R) * (180.0f / 3.1415926f);

    if (tx > 1.5f)
        tx = -1.5f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// ==========================
// MAIN
// ==========================
int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitWindowSize(800, 400);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutCreateWindow("Sepeda Primitif");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5, 1.5, -0.5, 0.5);

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
