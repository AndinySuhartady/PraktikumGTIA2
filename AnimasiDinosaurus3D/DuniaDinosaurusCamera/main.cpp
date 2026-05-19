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

// ================= GLOBAL =================
float stepAngle = 0.0f;
float wingAngle = 0.0f;

// Variabel Kamera (FPS Style)
float camX = 15.0f, camY = 10.0f, camZ = 15.0f;
float angle = 0.0f; // sudut rotasi horizontal
float lx = 0.0f, lz = -1.0f; // arah pandang (look-at vector)
float speed = 0.5f;

// ================= VOXEL =================
void drawVoxel(float x, float y, float z,
               float sx, float sy, float sz,
               float r, float g, float b,
               bool eye = false)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidCube(1.0);

    if (eye) {
        glDisable(GL_LIGHTING);
        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(0.3f, 0.2f, 0.51f);
        glScalef(0.2f, 0.2f, 0.05f);
        glutSolidCube(1);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();
}

// ================= DINOSAURUS & OBJEK =================
void dinoHijau() {
    glPushMatrix();
    glTranslatef(-6, 1.2f, 0);
    float bob = fabs(sin(stepAngle)) * 0.15;
    glTranslatef(0, bob, 0);
    drawVoxel(0, 0, 0, 3, 1.6, 1.8, 0.4, 0.9, 0);
    drawVoxel(1.4, 0.9, 0, 1, 1, 1.2, 0.4, 0.9, 0);
    drawVoxel(2.2, 1.8, 0, 2.2, 1.4, 1.6, 0.4, 0.9, 0, true);
    drawVoxel(-2, -0.2, 0, 1.6, 0.8, 1.2, 0.3, 0.7, 0);
    float x[4] = { -0.9,-0.9,1,1 }, z[4] = { 0.7,-0.7,0.7,-0.7 };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(x[i], 0.0f, z[i]);
        float ayun = (i == 0 || i == 3) ? sin(stepAngle * 2) * 20 : -sin(stepAngle * 2) * 20;
        glRotatef(ayun, 0, 0, 1);
        drawVoxel(0, -0.5, 0, 0.8, 1, 0.8, 0.4, 0.9, 0);
        drawVoxel(0, -1.2, 0, 0.9, 0.4, 0.9, 0.3, 0.3, 0.3);
        glPopMatrix();
    }
    glPopMatrix();
}

void triceratops() {
    glPushMatrix();
    glTranslatef(6, 1.2f, 0);
    float bob = fabs(sin(stepAngle)) * 0.12;
    glTranslatef(0, bob, 0);
    drawVoxel(0, 0, 0, 3.5, 2, 2, 0.8, 0.1, 0.1);
    drawVoxel(1.8, 0.5, 0, 1, 1.2, 1.5, 0.8, 0.1, 0.1);
    glPushMatrix();
    glRotatef(sin(stepAngle) * 2, 0, 0, 1);
    drawVoxel(2.3, 1.5, 0, 0.3, 2.5, 2.5, 0.85, 0.3, 0);
    drawVoxel(2.7, 0.8, 0, 1.5, 1.4, 1.4, 0.8, 0.1, 0.1, true);
    drawVoxel(3.2, 0.4, 0, 1, 1, 1, 0.8, 0.1, 0.1);
    drawVoxel(2.9, 1.6, 0.4, 0.3, 0.8, 0.3, 0.9, 0.8, 0.6);
    drawVoxel(2.9, 1.6, -0.4, 0.3, 0.8, 0.3, 0.9, 0.8, 0.6);
    drawVoxel(3.5, 1.0, 0, 0.3, 0.5, 0.3, 0.9, 0.8, 0.6);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.8, 0.2, 0);
    glRotatef(sin(stepAngle * 0.5) * 5, 0, 1, 0);
    drawVoxel(-0.8, 0, 0, 2.5, 0.8, 1, 0.8, 0.1, 0.1);
    glPopMatrix();
    float x[4] = { -1,-1,1.2,1.2 }, z[4] = { 0.7,-0.7,0.7,-0.7 };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(x[i], 0.0f, z[i]);
        float ayun = (i == 0 || i == 3) ? sin(stepAngle * 1.5) * 20 : -sin(stepAngle * 1.5) * 20;
        glRotatef(ayun, 0, 0, 1);
        drawVoxel(0, -0.6, 0, 0.8, 1.2, 0.8, 0.8, 0.1, 0.1);
        drawVoxel(0, -1.2, 0, 0.9, 0.4, 0.9, 0.3, 0.3, 0.3);
        glPopMatrix();
    }
    glPopMatrix();
}

void ptero() {
    glPushMatrix();
    glTranslatef(0, 5 + sin(wingAngle * 0.5) * 1.0, 0);
    drawVoxel(0, 0, 0, 2.5, 1.2, 1.2, 1, 0.5, 0);
    drawVoxel(1.2, 0.6, 0, 0.8, 1.2, 0.8, 1, 0.5, 0);
    drawVoxel(1.8, 1.5, 0, 0.7, 1.5, 0.7, 1, 0.5, 0);
    drawVoxel(2.4, 2.8, 0, 0.6, 1.8, 0.6, 1, 0.5, 0);
    drawVoxel(2.8, 3.8, 0, 1.2, 1, 0.8, 1, 0.5, 0, true);
    drawVoxel(4.5, 3.6, 0, 3.5, 0.5, 0.6, 1, 0.8, 0);
    drawVoxel(-1.8, 0, 0, 1.2, 0.4, 0.6, 1, 0.5, 0);
    float flap = sin(wingAngle) * 30;
    glPushMatrix();
    glTranslatef(0, 0.2, 0.6); glRotatef(flap, 1, 0, 0);
    drawVoxel(0, 0, 2, 2, 0.2, 4, 1, 0.6, 0.1); glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0.2, -0.6); glRotatef(-flap, 1, 0, 0);
    drawVoxel(0, 0, -2, 2, 0.2, 4, 1, 0.6, 0.1); glPopMatrix();
    glPopMatrix();
}

void pohon(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    drawVoxel(0.0f, 2.0f, 0.0f, 1.0f, 4.0f, 1.0f, 0.4f, 0.25f, 0.1f);
    drawVoxel(0.0f, 5.0f, 0.0f, 5.0f, 1.5f, 5.0f, 0.0f, 0.5f, 0.0f);
    drawVoxel(0.0f, 6.5f, 0.0f, 4.0f, 1.5f, 4.0f, 0.1f, 0.6f, 0.0f);
    glPopMatrix();
}

void telur(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    float r = 0.92f, g = 0.85f, b = 0.65f;
    drawVoxel(0.0f, 0.3f, 0.0f, 1.0f, 0.4f, 1.0f, r, g, b);
    drawVoxel(0.0f, 0.8f, 0.0f, 1.4f, 0.5f, 1.4f, r, g, b);
    glPopMatrix();
}

// ================= CAMERA CONTROLS =================
void processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // maju
            camX += lx * speed;
            camZ += lz * speed;
            break;
        case 's': // mundur
            camX -= lx * speed;
            camZ -= lz * speed;
            break;
        case 'a': // kiri
            camX += lz * speed;
            camZ -= lx * speed;
            break;
        case 'd': // kanan
            camX -= lz * speed;
            camZ += lx * speed;
            break;
        case 'q': // naik
            camY += 0.5f;
            break;
        case 'e': // turun
            camY -= 0.5f;
            break;
        case 27: // ESC
            exit(0);
    }
    glutPostRedisplay();
}

void processPassiveMotion(int x, int y) {
    // Gerakkan mouse untuk menoleh
    angle = (x - 512) * 0.005f;
    lx = sin(angle);
    lz = -cos(angle);
    glutPostRedisplay();
}

// ================= DISPLAY =================
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera mengikuti posisi camX, camY, camZ dan melihat ke arah lx, lz
    gluLookAt(camX, camY, camZ, 
              camX + lx, camY, camZ + lz, 
              0.0f, 1.0f, 0.0f);

    // Lantai
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.5, 0.2);
    glVertex3f(-50, 0, -50); glVertex3f(50, 0, -50);
    glVertex3f(50, 0, 50); glVertex3f(-50, 0, 50);
    glEnd();
    glEnable(GL_LIGHTING);

    // Objek-objek
    dinoHijau();
    triceratops();
    ptero();
    pohon(-15, -15); pohon(-15, 15); pohon(15, -15);
    telur(0, 5); telur(-5, -5); telur(5, 5);

    glutSwapBuffers();
}

// ================= TIMER =================
void timer(int v) {
    stepAngle += 0.08f;
    wingAngle += 0.12f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// ================= INIT, RESHAPE, MAIN =================
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.5, 0.8, 1, 1);
    GLfloat light_pos[] = { 20, 30, 20, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / h, 0.1, 200);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Dunia Dino: Jalan-jalan (W,A,S,D + Mouse)");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    // Aktifkan Input
    glutKeyboardFunc(processNormalKeys);
    glutPassiveMotionFunc(processPassiveMotion);
    
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
