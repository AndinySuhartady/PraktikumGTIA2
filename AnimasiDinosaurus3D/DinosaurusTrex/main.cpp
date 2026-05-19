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
#include <cmath> // Library untuk fungsi matematika fabs dan sin

// --- Variabel Animasi ---
float stepAngle = 0.0f;
float moveSpeed = 0.1f; // Sesuaikan kecepatan jalan di sini

// --- Fungsi untuk Menggambar Blok (Voxel) ---
void drawBlok(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b, bool adaMata = false) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    
    // Set warna material
    glColor3f(r, g, b);
    glutSolidCube(1.0);

    // Detail Mata (hanya untuk blok kepala)
    if (adaMata) {
        glDisable(GL_LIGHTING); // Mata hitam pekat
        glColor3f(0.0f, 0.0f, 0.0f);
        glPushMatrix();
        glTranslatef(0.2f, 0.15f, 0.51f); 
        glScalef(0.2f, 0.25f, 0.1f);
        glutSolidCube(1.0);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera sudut pandang isometrik (seperti di gambar)
    gluLookAt(10.0, 7.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 1. LANTAI (Abu-abu)
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(-20.0f, -2.1f, -20.0f);
    glVertex3f( 20.0f, -2.1f, -20.0f);
    glVertex3f( 20.0f, -2.1f,  20.0f);
    glVertex3f(-20.0f, -2.1f,  20.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    // 2. DINOSAURUS
    glPushMatrix();
    // Efek badan naik turun sedikit (Bobbing) - menggunakan fabs agar tidak error
    glTranslatef(0.0f, fabs(sin(stepAngle)) * 0.15f, 0.0f);

    // Bagian Tubuh Utama
    drawBlok(0.0f, 0.0f, 0.0f, 3.0f, 1.6f, 1.8f, 0.4f, 0.9f, 0.0f);
    // Leher
    drawBlok(1.4f, 0.9f, 0.0f, 1.0f, 1.0f, 1.2f, 0.4f, 0.9f, 0.0f);
    // Kepala
    drawBlok(2.2f, 1.8f, 0.0f, 2.2f, 1.4f, 1.6f, 0.4f, 0.9f, 0.0f, true);
    // Ekor (Warna agak gelap)
    drawBlok(-2.0f, -0.2f, 0.0f, 1.6f, 0.8f, 1.2f, 0.3f, 0.7f, 0.0f);

    // --- KAKI DENGAN ANIMASI ---
    float posX[4] = {-0.9f, -0.9f, 1.0f, 1.0f}; // Posisi X kaki
    float posZ[4] = {0.7f, -0.7f, 0.7f, -0.7f}; // Posisi Z kaki (samping)
    
    for(int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(posX[i], -0.8f, posZ[i]); 
        
        // Animasi Ayunan: diagonal bergerak bersamaan
        float ayun;
        if (i == 0 || i == 3) ayun = sin(stepAngle * 2.0f) * 20.0f; 
        else ayun = -sin(stepAngle * 2.0f) * 20.0f;
        
        glRotatef(ayun, 0, 0, 1); // Ayun maju mundur
        
        // Bagian kaki hijau
        drawBlok(0, -0.5f, 0, 0.8f, 1.0f, 0.8f, 0.4f, 0.9f, 0.0f);
        // Bagian sepatu abu-abu
        drawBlok(0, -1.2f, 0, 0.9f, 0.4f, 0.9f, 0.25f, 0.25f, 0.25f);
        glPopMatrix();
    }
    glPopMatrix();

    glutSwapBuffers();
}

// Fungsi Timer untuk mengupdate frame animasi
void timer(int value) {
    stepAngle += moveSpeed;
    if (stepAngle > 360) stepAngle -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // Refresh setiap ~60 FPS
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    glClearColor(0.4f, 0.7f, 1.0f, 1.0f); // Background Biru Langit

    // Posisi cahaya agar shading sama dengan gambar
    GLfloat light_pos[] = { 15.0f, 15.0f, 10.0f, 1.0f };
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
    glutCreateWindow("Dino Voxel Animasi Berjalan");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0); 
    
    glutMainLoop();
    return 0;
}
