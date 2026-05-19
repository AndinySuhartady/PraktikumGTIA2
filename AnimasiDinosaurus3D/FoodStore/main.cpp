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

// ================= GLOBAL VARIABLES =================
float rotY = -22.0f;

// ================= VOXEL HELPER =================
void drawVoxel(float x, float y, float z,
                float sx, float sy, float sz,
                float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidCube(1.0);

    glPopMatrix();
}

// ================= DRAW TEXT =================
void drawText(const char* text, float x, float y, float z)
{
    glDisable(GL_LIGHTING);

    glColor3f(0.95f, 0.90f, 0.75f);

    glRasterPos3f(x, y, z);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }

    glEnable(GL_LIGHTING);
}

// ================= SMALL DETAIL HELPERS =================
void drawFruitPile(float x, float y, float z,
                   float r, float g, float b)
{
    drawVoxel(x, y, z, 0.35f, 0.35f, 0.35f, r, g, b);
    drawVoxel(x + 0.28f, y, z, 0.35f, 0.35f, 0.35f, r * 0.9f, g * 0.9f, b);
    drawVoxel(x - 0.28f, y, z, 0.35f, 0.35f, 0.35f, r, g * 0.8f, b);
    drawVoxel(x, y + 0.25f, z, 0.3f, 0.3f, 0.3f, r, g, b);
}

void drawWoodCrate(float x, float y, float z)
{
    // peti luar
    drawVoxel(x, y, z, 1.6f, 0.7f, 1.4f, 0.45f, 0.28f, 0.14f);

    // pinggiran
    drawVoxel(x, y + 0.28f, z + 0.55f, 1.5f, 0.08f, 0.08f, 0.62f, 0.4f, 0.2f);
    drawVoxel(x, y + 0.28f, z - 0.55f, 1.5f, 0.08f, 0.08f, 0.62f, 0.4f, 0.2f);

    // isi buah
    drawFruitPile(x - 0.3f, y + 0.4f, z, 0.9f, 0.2f, 0.1f);
    drawFruitPile(x + 0.3f, y + 0.42f, z, 0.95f, 0.7f, 0.15f);
}

// ================= STORE STRUCTURE =================
void drawStore()
{
    // ================= COLORS =================
    float darkWoodR = 0.30f;
    float darkWoodG = 0.18f;
    float darkWoodB = 0.10f;

    float woodR = 0.46f;
    float woodG = 0.30f;
    float woodB = 0.16f;

    // ================= BACK WALL =================
    drawVoxel(0.0f, 3.0f, -1.5f,
               9.0f, 6.0f, 0.7f,
               0.26f, 0.17f, 0.09f);

    // ================= FLOOR =================
    drawVoxel(0.0f, 0.2f, 1.5f,
               10.0f, 0.4f, 5.5f,
               0.65f, 0.58f, 0.42f);

    // ================= MAIN PILLARS =================
    drawVoxel(-4.4f, 3.2f, 2.2f,
               0.9f, 6.5f, 0.9f,
               darkWoodR, darkWoodG, darkWoodB);

    drawVoxel(4.4f, 3.2f, 2.2f,
               0.9f, 6.5f, 0.9f,
               darkWoodR, darkWoodG, darkWoodB);

    // inner pillars
    drawVoxel(-1.7f, 3.0f, 1.6f,
               0.5f, 5.0f, 0.5f,
               darkWoodR, darkWoodG, darkWoodB);

    drawVoxel(1.7f, 3.0f, 1.6f,
               0.5f, 5.0f, 0.5f,
               darkWoodR, darkWoodG, darkWoodB);

    // ================= TOP BEAMS =================
    drawVoxel(0.0f, 6.1f, 2.0f,
               9.4f, 0.7f, 0.8f,
               woodR, woodG, woodB);

    drawVoxel(0.0f, 5.4f, 1.2f,
               8.5f, 0.4f, 0.6f,
               0.33f, 0.20f, 0.10f);

    // ================= SIGN BOARD =================
    drawVoxel(0.0f, 5.9f, 2.5f,
               6.8f, 1.3f, 0.35f,
               0.40f, 0.24f, 0.12f);

    // border papan
    drawVoxel(0.0f, 6.35f, 2.7f,
               6.9f, 0.12f, 0.08f,
               0.65f, 0.46f, 0.22f);

    // ================= TEXT FOOD STORE =================
drawText("FOOD STORE", -2.0f, 5.8f, 2.8f);

    // ================= LEAF ROOF =================
    // layer bawah
    drawVoxel(0.0f, 7.0f, 1.8f,
               10.5f, 1.2f, 4.0f,
               0.12f, 0.42f, 0.08f);

    // layer tengah
    drawVoxel(0.0f, 7.9f, 1.5f,
               9.0f, 0.9f, 3.0f,
               0.16f, 0.52f, 0.10f);

    // layer atas
    drawVoxel(0.0f, 8.5f, 1.2f,
               7.5f, 0.7f, 2.2f,
               0.20f, 0.60f, 0.14f);

    // daun menggantung kiri kanan
    drawVoxel(-5.2f, 6.8f, 2.0f,
               1.2f, 1.2f, 1.2f,
               0.14f, 0.48f, 0.10f);

    drawVoxel(5.2f, 6.8f, 2.0f,
               1.2f, 1.2f, 1.2f,
               0.14f, 0.48f, 0.10f);

    // ================= LEFT SHELVES =================
    drawVoxel(-2.9f, 2.0f, 1.3f,
               2.0f, 0.12f, 1.6f,
               woodR, woodG, woodB);

    drawVoxel(-2.9f, 3.8f, 1.3f,
               2.0f, 0.12f, 1.6f,
               woodR, woodG, woodB);

    // buah kiri bawah
    drawFruitPile(-3.4f, 2.45f, 1.2f, 0.92f, 0.24f, 0.12f);
    drawFruitPile(-2.8f, 2.45f, 1.2f, 0.95f, 0.65f, 0.10f);
    drawFruitPile(-2.2f, 2.45f, 1.2f, 0.20f, 0.65f, 0.15f);

    // buah kiri atas
    drawFruitPile(-3.2f, 4.2f, 1.2f, 0.20f, 0.70f, 0.20f);
    drawFruitPile(-2.5f, 4.2f, 1.2f, 0.85f, 0.35f, 0.10f);

    // ================= RIGHT SHELVES =================
    drawVoxel(2.9f, 2.0f, 1.3f,
               2.0f, 0.12f, 1.6f,
               woodR, woodG, woodB);

    drawVoxel(2.9f, 3.8f, 1.3f,
               2.0f, 0.12f, 1.6f,
               woodR, woodG, woodB);

    drawFruitPile(2.3f, 2.45f, 1.2f, 0.92f, 0.22f, 0.10f);
    drawFruitPile(2.9f, 2.45f, 1.2f, 0.95f, 0.70f, 0.12f);
    drawFruitPile(3.5f, 2.45f, 1.2f, 0.18f, 0.65f, 0.18f);

    drawFruitPile(2.5f, 4.2f, 1.2f, 0.96f, 0.50f, 0.08f);
    drawFruitPile(3.2f, 4.2f, 1.2f, 0.90f, 0.82f, 0.18f);

    // ================= FRONT CRATES =================
    drawWoodCrate(-4.2f, 0.45f, 3.4f);
    drawWoodCrate(3.8f, 0.45f, 3.4f);

    // crate tengah
    drawVoxel(0.0f, 0.45f, 2.9f,
               1.8f, 0.7f, 1.5f,
               0.40f, 0.26f, 0.14f);

    drawFruitPile(-0.3f, 0.9f, 2.9f, 0.22f, 0.72f, 0.22f);
    drawFruitPile(0.4f, 0.9f, 2.9f, 0.92f, 0.35f, 0.10f);

    // ================= SIDE LEAF DECOR =================
    drawVoxel(-5.3f, 3.8f, 1.4f,
               1.2f, 3.8f, 1.2f,
               0.10f, 0.38f, 0.08f);

    drawVoxel(5.3f, 3.8f, 1.4f,
               1.2f, 3.8f, 1.2f,
               0.10f, 0.38f, 0.08f);
}

// ================= DISPLAY =================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        0.0, 6.5, 18.0,
        0.0, 3.5, 0.0,
        0.0, 1.0, 0.0
    );

    glRotatef(rotY, 0, 1, 0);

    // ================= GROUND =================
    glDisable(GL_LIGHTING);

    glBegin(GL_QUADS);

    glColor3f(0.45f, 0.63f, 0.28f);

    glVertex3f(-30, 0, -30);
    glVertex3f(30, 0, -30);
    glVertex3f(30, 0, 30);
    glVertex3f(-30, 0, 30);

    glEnd();

    glEnable(GL_LIGHTING);

    // render toko
    drawStore();

    glutSwapBuffers();
}

// ================= INIT =================
void init()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);

    // sky color
    glClearColor(0.55f, 0.78f, 0.96f, 1.0f);

    GLfloat light_pos[] = {18.0f, 22.0f, 15.0f, 1.0f};

    GLfloat ambient[] = {0.45f, 0.45f, 0.45f, 1.0f};

    GLfloat diffuse[] = {0.95f, 0.95f, 0.95f, 1.0f};

    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

// ================= RESHAPE =================
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0, (float)w / h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

// ================= MAIN =================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1280, 720);

    glutCreateWindow("DetailedVoxel Food Store");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
