
//
// Grafika dan Teknik Interaktif
// 10/05/2026
// Andiny Khaerany Suhartady
// 24060124140194
// Mobil 3D OpenGL
//

/*
==========================================
           MOBIL 3D OPENGL
==========================================

KONTROL:
- Panah Kiri/Kanan : lihat kiri kanan
- Panah Atas/Bawah : maju mundur
- A / D            : putar mobil
- Q                : keluar
*/

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

// ==========================================
// VARIABEL KAMERA
// ==========================================
float angle = 0.0f;
float deltaAngle = 0.0f;

float x = 0.0f;
float y = 2.0f;
float z = 15.0f;

float lx = 0.0f;
float ly = 0.0f;
float lz = -1.0f;

int deltaMove = 0;

float ratio;
int h, w;

// ==========================================
// VARIABEL MOBIL
// ==========================================
float rotMobil = 0.0f;

// ==========================================
// LIGHTING
// ==========================================
const GLfloat light_ambient[]  = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {0.0f, 15.0f, 10.0f, 1.0f};

const GLfloat mat_ambient[]    = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[]    = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[]   = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

// ==========================================
// GRID / LANTAI
// ==========================================
void Grid()
{
    double i;

    const float Z_MIN = -50;
    const float Z_MAX =  50;

    const float X_MIN = -50;
    const float X_MAX =  50;

    const float gap = 1.5f;

    glDisable(GL_LIGHTING);

    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    for(i = Z_MIN; i <= Z_MAX; i += gap)
    {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }

    for(i = X_MIN; i <= X_MAX; i += gap)
    {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }

    glEnd();

    glEnable(GL_LIGHTING);
}

// ==========================================
// RODA
// ==========================================
void Roda()
{
    glPushMatrix();

    // Ban
    glColor3f(0.1f, 0.1f, 0.1f);
    glutSolidTorus(0.15, 0.35, 30, 30);

    // Velg
    glColor3f(0.8f, 0.8f, 0.8f);
    glutSolidSphere(0.15, 20, 20);

    glPopMatrix();
}

// ==========================================
// MOBIL
// ==========================================
void Mobil()
{
    glPushMatrix();

    // Rotasi mobil
    glRotatef(rotMobil, 0, 1, 0);

    // ======================================
    // BADAN MOBIL
    // ======================================
    glPushMatrix();

        glScalef(4.0f, 1.0f, 2.0f);

        // badan solid
        glLineWidth(3.0f);
        glColor3f(0.6f, 0.0f, 0.8f);
        glutSolidCube(1.5);

        // rangka
        glLineWidth(3.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glutWireCube(1.52);

    glPopMatrix();

    // ======================================
    // ATAP MOBIL
    // ======================================
    glPushMatrix();

        glTranslatef(0.0f, 1.0f, 0.0f);

        glScalef(2.0f, 1.0f, 2.0f);

        // atap solid
        glColor3f(1.0f, 0.4f, 0.7f);
        glutSolidCube(1.2);

        // rangka atap
        glColor3f(1.0f, 1.0f, 1.0f);
        glutWireCube(1.22);

    glPopMatrix();

    // ======================================
    // KACA DEPAN
    // ======================================
    glPushMatrix();

        glTranslatef(0.7f, 1.0f, 0.0f);

        glScalef(0.1f, 0.6f, 1.5f);

        glColor3f(0.5f, 0.8f, 1.0f);
        glutSolidCube(1.0f);

    glPopMatrix();

    // ======================================
    // RODA DEPAN KIRI
    // ======================================
    glPushMatrix();

        glTranslatef(-2.0f, -0.8f, 1.5f);
        glRotatef(90, 0, 0, 1);

        Roda();

    glPopMatrix();

    // ======================================
    // RODA DEPAN KANAN
    // ======================================
    glPushMatrix();

        glTranslatef(2.0f, -0.8f, 1.5f);
        glRotatef(90, 0, 0, 1);

        Roda();

    glPopMatrix();

    // ======================================
    // RODA BELAKANG KIRI
    // ======================================
    glPushMatrix();

        glTranslatef(-2.0f, -0.8f, -1.5f);
        glRotatef(90, 0, 0, 1);

        Roda();

    glPopMatrix();

    // ======================================
    // RODA BELAKANG KANAN
    // ======================================
    glPushMatrix();

        glTranslatef(2.0f, -0.8f, -1.5f);
        glRotatef(90, 0, 0, 1);

        Roda();

    glPopMatrix();

    // ======================================
    // LAMPU DEPAN
    // ======================================
    glPushMatrix();

        glTranslatef(3.1f, 0.0f, 0.7f);

        glColor3f(1.0f, 1.0f, 0.0f);

        glutSolidSphere(0.2f, 20, 20);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(3.1f, 0.0f, -0.7f);

        glColor3f(1.0f, 1.0f, 0.0f);

        glutSolidSphere(0.2f, 20, 20);

    glPopMatrix();

    glPopMatrix();
}

// ==========================================
// ORIENTASI KAMERA
// ==========================================
void orientMe(float ang)
{
    lx = sin(ang);
    lz = -cos(ang);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

// ==========================================
// GERAK KAMERA
// ==========================================
void moveMeFlat(int i)
{
    x = x + i * lx * 0.2f;
    z = z + i * lz * 0.2f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

// ==========================================
// DISPLAY
// ==========================================
void display()
{
    if(deltaMove)
        moveMeFlat(deltaMove);

    if(deltaAngle)
    {
        angle += deltaAngle;
        orientMe(angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    // Grid
    Grid();

    // Mobil
    glPushMatrix();

        glTranslatef(0.0f, 1.0f, 0.0f);

        Mobil();

    glPopMatrix();

    glutSwapBuffers();
}

// ==========================================
// RESHAPE
// ==========================================
void Reshape(int w1, int h1)
{
    if(h1 == 0)
        h1 = 1;

    w = w1;
    h = h1;

    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

// ==========================================
// KEYBOARD PANAH DITEKAN
// ==========================================
void pressKey(int key, int xx, int yy)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            deltaAngle = -0.01f;
            break;

        case GLUT_KEY_RIGHT:
            deltaAngle = 0.01f;
            break;

        case GLUT_KEY_UP:
            deltaMove = 1;
            break;

        case GLUT_KEY_DOWN:
            deltaMove = -1;
            break;
    }
}

// ==========================================
// KEYBOARD PANAH DILEPAS
// ==========================================
void releaseKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.0f;
            break;

        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0;
            break;
    }
}

// ==========================================
// KEYBOARD BIASA
// ==========================================
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'a':
        case 'A':
            rotMobil += 5.0f;
            break;

        case 'd':
        case 'D':
            rotMobil -= 5.0f;
            break;

        case 'q':
        case 'Q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

// ==========================================
// LIGHTING
// ==========================================
void lighting()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

// ==========================================
// INIT
// ==========================================
void init()
{
    glEnable(GL_DEPTH_TEST);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

// ==========================================
// MAIN
// ==========================================
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 600);

    glutCreateWindow("Mobil3D OpenGL");

    init();
    lighting();

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(keyboard);

    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutMainLoop();

    return 0;
}


