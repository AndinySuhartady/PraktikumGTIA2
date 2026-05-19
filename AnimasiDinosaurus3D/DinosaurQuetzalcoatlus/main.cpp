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

// --- Variabel Animasi ---
float wingAngle = 0.0f;
float flySpeed = 0.1f; 

void drawVoxel(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b, bool hasEye = false) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(r, g, b);
    glutSolidCube(1.0);

    if (hasEye) {
        glDisable(GL_LIGHTING);
        glColor3f(0.1f, 0.1f, 0.1f);
        glPushMatrix();
        glTranslatef(0.2f, 0.2f, 0.51f);
        glScalef(0.2f, 0.2f, 0.05f);
        glutSolidCube(1.0);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera dari samping atas agar sayap terlihat jelas
    gluLookAt(15.0, 10.0, 15.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0);

    // Lantai (Background Jauh di bawah)
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-50.0f, -10.0f, -50.0f);
    glVertex3f( 50.0f, -10.0f, -50.0f);
    glVertex3f( 50.0f, -10.0f,  50.0f);
    glVertex3f(-50.0f, -10.0f,  50.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    // --- ANIMASI TERBANG (Bobbing naik turun) ---
    glPushMatrix();
    glTranslatef(0.0f, sin(wingAngle * 0.5f) * 0.5f, 0.0f);

    // 1. TUBUH UTAMA (Oranye)
    drawVoxel(0.0f, 0.0f, 0.0f, 2.5f, 1.2f, 1.2f, 1.0f, 0.5f, 0.0f);

    // 2. LEHER SANGAT PANJANG (Khas Quetzalcoatlus)
    drawVoxel(1.2f, 0.6f, 0.0f, 0.8f, 1.2f, 0.8f, 1.0f, 0.5f, 0.0f);
    drawVoxel(1.8f, 1.5f, 0.0f, 0.7f, 1.5f, 0.7f, 1.0f, 0.5f, 0.0f);
    drawVoxel(2.4f, 2.8f, 0.0f, 0.6f, 1.8f, 0.6f, 1.0f, 0.5f, 0.0f);

    // 3. KEPALA & PARUH RAKSASA (Kuning)
    drawVoxel(2.8f, 3.8f, 0.0f, 1.2f, 1.0f, 0.8f, 1.0f, 0.5f, 0.0f, true); // Kepala
    drawVoxel(4.5f, 3.6f, 0.0f, 3.5f, 0.5f, 0.6f, 1.0f, 0.8f, 0.0f);       // Paruh panjang
    
    // Jambul belakang
    drawVoxel(2.0f, 4.4f, 0.0f, 0.4f, 1.2f, 0.4f, 1.0f, 0.7f, 0.0f);

    // 4. EKOR
    drawVoxel(-1.8f, 0.0f, 0.0f, 1.2f, 0.4f, 0.6f, 1.0f, 0.5f, 0.0f);

    // --- 5. SAYAP (MENGEPAK) ---
    float flap = sin(wingAngle) * 30.0f; // Sudut kepakan

    // Sayap Kanan
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.6f);  // Engsel sayap kanan
    glRotatef(flap, 1, 0, 0);       // Rotasi kepak pada sumbu X
    drawVoxel(0.0f, 0.0f, 2.0f, 2.0f, 0.2f, 4.0f, 1.0f, 0.6f, 0.1f); // Membran sayap
    glPopMatrix();

    // Sayap Kiri
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, -0.6f); // Engsel sayap kiri
    glRotatef(-flap, 1, 0, 0);      // Berlawanan arah
    drawVoxel(0.0f, 0.0f, -2.0f, 2.0f, 0.2f, 4.0f, 1.0f, 0.6f, 0.1f);
    glPopMatrix();

    glPopMatrix(); // End Animasi Terbang

    glutSwapBuffers();
}

void timer(int v) {
    wingAngle += flySpeed;
    if (wingAngle > 360) wingAngle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.4f, 0.7f, 1.0f, 1.0f);

    GLfloat light_pos[] = { 20.0f, 30.0f, 20.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
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
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Quetzalcoatlus Flying Voxel");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
