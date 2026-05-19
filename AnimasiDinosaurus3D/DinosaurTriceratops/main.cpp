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
float stepAngle = 0.0f;
float moveSpeed = 0.08f; // Kecepatan gerak Triceratops (lebih lambat & berat)

// Fungsi menggambar blok voxel
void drawVoxel(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b, bool hasBlueEye = false) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(r, g, b);
    glutSolidCube(1.0);

    if (hasBlueEye) {
        glDisable(GL_LIGHTING);
        glColor3f(0.0f, 0.0f, 0.3f); 
        glPushMatrix();
        glTranslatef(0.35f, 0.15f, 0.51f);
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

    gluLookAt(12.0, 8.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Lantai Abu-abu
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.55f, 0.55f);
    glVertex3f(-25.0f, -2.1f, -25.0f);
    glVertex3f( 25.0f, -2.1f, -25.0f);
    glVertex3f( 25.0f, -2.1f,  25.0f);
    glVertex3f(-25.0f, -2.1f,  25.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    // --- ANIMASI TUBUH ---
    glPushMatrix();
    // Efek badan naik turun (Bobbing) saat berjalan
    float bobbing = fabs(sin(stepAngle)) * 0.12f;
    glTranslatef(0.0f, bobbing, 0.0f);

    // Tubuh Utama
    drawVoxel(0.0f, 0.0f, 0.0f, 3.5f, 2.0f, 2.0f, 0.8f, 0.1f, 0.1f);
    // Leher
    drawVoxel(1.8f, 0.5f, 0.0f, 1.0f, 1.2f, 1.5f, 0.8f, 0.1f, 0.1f);

    // --- BAGIAN KEPALA (Ikut bergerak dengan tubuh) ---
    glPushMatrix();
    // Tambahkan sedikit rotasi pada kepala saat melangkah
    glRotatef(sin(stepAngle) * 2.0f, 0, 0, 1);
    
    // Rumbat Leher
    drawVoxel(2.3f, 1.5f, 0.0f, 0.3f, 2.5f, 2.5f, 0.85f, 0.3f, 0.0f);
    // Wajah & Mata
    drawVoxel(2.7f, 0.8f, 0.0f, 1.5f, 1.4f, 1.4f, 0.8f, 0.1f, 0.1f, true);
    // Moncong
    drawVoxel(3.2f, 0.4f, 0.0f, 1.0f, 1.0f, 1.0f, 0.8f, 0.1f, 0.1f);
    // Cula
    drawVoxel(2.9f, 1.6f, 0.4f, 0.3f, 0.8f, 0.3f, 0.9f, 0.8f, 0.6f);
    drawVoxel(2.9f, 1.6f, -0.4f, 0.3f, 0.8f, 0.3f, 0.9f, 0.8f, 0.6f);
    drawVoxel(3.5f, 1.0f, 0.0f, 0.3f, 0.5f, 0.3f, 0.9f, 0.8f, 0.6f);
    glPopMatrix();

    // Ekor (Berayun kiri-kanan sedikit)
    glPushMatrix();
    glTranslatef(-1.75f, 0.2f, 0.0f);
    glRotatef(sin(stepAngle * 0.5f) * 5.0f, 0, 1, 0);
    drawVoxel(-0.75f, 0.0f, 0.0f, 2.5f, 0.8f, 1.0f, 0.8f, 0.1f, 0.1f);
    glPopMatrix();

    // --- ANIMASI KAKI ---
    float legX[4] = {-1.0f, -1.0f, 1.2f, 1.2f};
    float legZ[4] = {0.7f, -0.7f, 0.7f, -0.7f};
    
    for(int i = 0; i < 4; i++) {
        glPushMatrix();
        // Titik rotasi paha
        glTranslatef(legX[i], -0.6f, legZ[i]); 
        
        float ayun;
        // Pola jalan silang (Depan Kanan & Belakang Kiri bergerak bersamaan)
        if (i == 0 || i == 3) ayun = sin(stepAngle * 1.5f) * 20.0f;
        else ayun = -sin(stepAngle * 1.5f) * 20.0f;
        
        glRotatef(ayun, 0, 0, 1);
        
        // Kaki
        drawVoxel(0, -0.6f, 0, 0.8f, 1.2f, 0.8f, 0.8f, 0.1f, 0.1f);
        // Sepatu/Kuku
        drawVoxel(0, -1.2f, 0, 0.9f, 0.4f, 0.9f, 0.3f, 0.3f, 0.3f);
        glPopMatrix();
    }
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int v) {
    stepAngle += moveSpeed;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.45f, 0.7f, 1.0f, 1.0f);

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
    glutCreateWindow("Triceratops Voxel Walking");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
