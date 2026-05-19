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

// Fungsi untuk menggambar balok voxel dengan warna krem telur
void drawVoxel(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera sudut pandang isometrik meniru gambar
    gluLookAt(8.0, 6.0, 10.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0);

    // 1. LANTAI (Abu-abu Beton)
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.55f, 0.55f);
    glVertex3f(-15.0f, -0.51f, -15.0f);
    glVertex3f( 15.0f, -0.51f, -15.0f);
    glVertex3f( 15.0f, -0.51f,  15.0f);
    glVertex3f(-15.0f, -0.51f,  15.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    // 2. KONSTRUKSI TELUR VOXEL (Warna Krem/Beige)
    float r = 0.92f, g = 0.85f, b = 0.65f;

    // Lapisan 1 (Dasar)
    drawVoxel(0.0f, 0.0f, 0.0f, 1.2f, 0.5f, 1.2f, r, g, b);
    
    // Lapisan 2
    drawVoxel(0.0f, 0.5f, 0.0f, 2.0f, 0.6f, 2.0f, r, g, b);
    
    // Lapisan 3 (Mulai Melebar)
    drawVoxel(0.0f, 1.2f, 0.0f, 2.8f, 0.8f, 2.8f, r, g, b);
    
    // Lapisan 4 (Tengah - Paling Lebar)
    drawVoxel(0.0f, 2.1f, 0.0f, 3.2f, 1.0f, 3.2f, r, g, b);
    
    // Lapisan 5 (Mulai Mengecil Kembali)
    drawVoxel(0.0f, 3.1f, 0.0f, 2.8f, 0.9f, 2.8f, r, g, b);
    
    // Lapisan 6
    drawVoxel(0.0f, 4.0f, 0.0f, 2.0f, 0.8f, 2.0f, r, g, b);
    
    // Lapisan 7 (Puncak)
    drawVoxel(0.0f, 4.8f, 0.0f, 1.0f, 0.7f, 1.0f, r, g, b);
    
    // Detail Paling Atas (Satu Blok Kecil)
    drawVoxel(0.0f, 5.2f, 0.0f, 0.6f, 0.3f, 0.6f, r, g, b);

    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    // Warna Background Biru Langit Cerah
    glClearColor(0.45f, 0.75f, 1.0f, 1.0f);

    // Posisi cahaya dari depan atas agar shading voxel identik dengan gambar
    GLfloat light_pos[] = { 10.0f, 15.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    GLfloat ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
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
    glutInitWindowSize(800, 800);
    glutCreateWindow("Telur Voxel Replika");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
