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
#include <cmath> // Dibutuhkan untuk fungsi sin()

// --- Variabel Kontrol Animasi ---
float stepAngle = 0.0f;
float moveSpeed = 5.0f; // Kecepatan ayunan

void drawVoxel(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b, bool hasEye = false) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(r, g, b);
    glutSolidCube(1.0);

    if (hasEye) {
        glDisable(GL_LIGHTING);
        glColor3f(0.05f, 0.05f, 0.05f);
        glPushMatrix();
        glTranslatef(0.25f, 0.2f, 0.51f);
        glScalef(0.2f, 0.2f, 0.02f);
        glutSolidCube(1.0);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(10.0, 6.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // --- LOGIKA BERJALAN ---
    // 1. Efek Bobbing: Tubuh naik turun sedikit mengikuti irama langkah
    float bobbing = sin(stepAngle * 0.1f) * 0.1f;
    glTranslatef(0.0f, bobbing, 0.0f);

    // 2. Sudut Ayunan Sirip
    float swing = sin(stepAngle * 0.1f) * 20.0f; 

    // Lantai
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.55f, 0.55f);
    glVertex3f(-25.0f, -1.8f, -25.0f);
    glVertex3f( 25.0f, -1.8f, -25.0f);
    glVertex3f( 25.0f, -1.8f,  25.0f);
    glVertex3f(-25.0f, -1.8f,  25.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    // --- TUBUH UTAMA ---
    drawVoxel(0.0f, 0.0f, 0.0f, 3.5f, 1.6f, 1.8f, 0.0f, 0.45f, 0.9f);
    drawVoxel(0.0f, -0.6f, 0.0f, 3.6f, 0.6f, 1.9f, 0.85f, 0.75f, 0.55f);
    drawVoxel(2.0f, 0.3f, 0.0f, 1.0f, 1.0f, 1.2f, 0.0f, 0.45f, 0.9f);
    drawVoxel(2.0f, -0.2f, 0.0f, 1.1f, 0.6f, 1.3f, 0.85f, 0.75f, 0.55f);
    drawVoxel(2.8f, 1.0f, 0.0f, 1.6f, 1.2f, 1.0f, 0.0f, 0.45f, 0.9f, true);
    drawVoxel(3.6f, 0.8f, 0.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.45f, 0.9f);
    drawVoxel(3.6f, 0.5f, 0.0f, 0.9f, 0.4f, 0.9f, 0.85f, 0.75f, 0.55f);
    drawVoxel(-2.5f, 0.0f, 0.0f, 2.0f, 0.8f, 1.2f, 0.0f, 0.45f, 0.9f);
    drawVoxel(-3.5f, -0.2f, 0.0f, 1.0f, 0.4f, 0.8f, 0.0f, 0.45f, 0.9f);

    // --- SIRIP (FLIPPER) DENGAN ANIMASI ---
    
    // Depan Kanan
    glPushMatrix();
    glTranslatef(1.2f, -1.0f, 0.7f);
    glRotatef(swing, 0, 1, 0); // Ayun pada sumbu Y
    drawVoxel(0.4f, 0.0f, 0.0f, 1.2f, 0.3f, 1.0f, 0.0f, 0.45f, 0.9f);
    glPopMatrix();

    // Depan Kiri (Arah berlawanan)
    glPushMatrix();
    glTranslatef(1.2f, -1.0f, -0.7f);
    glRotatef(-swing, 0, 1, 0);
    drawVoxel(0.4f, 0.0f, 0.0f, 1.2f, 0.3f, 1.0f, 0.0f, 0.45f, 0.9f);
    glPopMatrix();

    // Belakang Kanan (Satu fase dengan Depan Kiri)
    glPushMatrix();
    glTranslatef(-0.8f, -1.0f, 0.7f);
    glRotatef(-swing, 0, 1, 0);
    drawVoxel(0.3f, 0.0f, 0.0f, 1.0f, 0.3f, 0.8f, 0.0f, 0.45f, 0.9f);
    glPopMatrix();

    // Belakang Kiri (Satu fase dengan Depan Kanan)
    glPushMatrix();
    glTranslatef(-0.8f, -1.0f, -0.7f);
    glRotatef(swing, 0, 1, 0);
    drawVoxel(0.3f, 0.0f, 0.0f, 1.0f, 0.3f, 0.8f, 0.0f, 0.45f, 0.9f);
    glPopMatrix();

    glutSwapBuffers();
}

// Fungsi Timer untuk update sudut animasi (~60 FPS)
void timer(int value) {
    stepAngle += moveSpeed;
    if (stepAngle > 3600) stepAngle -= 3600; // Reset agar tidak overflow

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.4f, 0.7f, 1.0f, 1.0f);

    GLfloat light_position[] = { 10.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 750);
    glutCreateWindow("Mesosaurus Berjalan");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0); // Mulai timer animasi
    glutMainLoop();
    return 0;
}
