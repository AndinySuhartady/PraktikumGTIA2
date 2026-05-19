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


// Variabel animasi
float earthAngle = 0.0f;
float moonOrbit  = 0.0f;
float moonRotate = 0.0f;
float orbitRadius = 3.0f;

// ========================
// Render Scene
// ========================
void Render_Scene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera mundur supaya objek terlihat
    glTranslatef(0.0f,0.0f,-8.0f);

    // ROTASI BUMI
    glPushMatrix();
        glRotatef(earthAngle,0,1,0);
        glColor3f(0.0f,0.5f,1.0f);
        glutSolidSphere(1.0,30,30);
    glPopMatrix();

    // REVOLUSI BULAN
    glPushMatrix();
        glRotatef(moonOrbit,0,1,0);
        glTranslatef(orbitRadius,0,0);

        // ROTASI BULAN
        glRotatef(moonRotate,0,1,0);

        glColor3f(0.8f,0.8f,0.8f);
        glutSolidSphere(0.4,20,20);
    glPopMatrix();

    glutSwapBuffers();
}

// ========================
// Update Logika Animasi
// ========================
void Update_Logika(int value)
{
    earthAngle += 0.5f;
    moonOrbit  += 0.3f;
    moonRotate += 0.4f;

    glutPostRedisplay();
    glutTimerFunc(16, Update_Logika, 0);
}

// ========================
// Inisialisasi
// ========================
void init()
{
    glClearColor(0.1f,0.1f,0.2f,1.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1.0,1.0,100.0);

    glMatrixMode(GL_MODELVIEW);
}

// ========================
// Main Program
// ========================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Simulasi Bumi dan Bulan");

    init();

    glutDisplayFunc(Render_Scene);
    glutTimerFunc(16, Update_Logika, 0);

    glutMainLoop();

    return 0;
}
