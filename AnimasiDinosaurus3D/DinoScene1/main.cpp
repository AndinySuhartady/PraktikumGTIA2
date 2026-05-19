/*
 * FreeGLUT Animation - Scene 1: Dunia Dino yang Damai
 * Mengintegrasikan Detail Voxel Food Store, Dino Hijau, Triceratops, Pterodactyl, Pohon, dan Telur.
 */

#include <GL/glut.h>
#include <cmath>

// ================= GLOBAL VARIABLES =================
float stepAngle = 0.0f;
float wingAngle = 0.0f;
float rotY = 0.0f; // Bisa diubah jika ingin memutar seluruh world

// ================= VOXEL HELPER =================
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

    if(eye){
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
void drawFruitPile(float x, float y, float z, float r, float g, float b)
{
    drawVoxel(x, y, z, 0.35f, 0.35f, 0.35f, r, g, b);
    drawVoxel(x + 0.28f, y, z, 0.35f, 0.35f, 0.35f, r * 0.9f, g * 0.9f, b);
    drawVoxel(x - 0.28f, y, z, 0.35f, 0.35f, 0.35f, r, g * 0.8f, b);
    drawVoxel(x, y + 0.25f, z, 0.3f, 0.3f, 0.3f, r, g, b);
}

void drawWoodCrate(float x, float y, float z)
{
    drawVoxel(x, y, z, 1.6f, 0.7f, 1.4f, 0.45f, 0.28f, 0.14f);
    drawVoxel(x, y + 0.28f, z + 0.55f, 1.5f, 0.08f, 0.08f, 0.62f, 0.4f, 0.2f);
    drawVoxel(x, y + 0.28f, z - 0.55f, 1.5f, 0.08f, 0.08f, 0.62f, 0.4f, 0.2f);
    drawFruitPile(x - 0.3f, y + 0.4f, z, 0.9f, 0.2f, 0.1f);
    drawFruitPile(x + 0.3f, y + 0.42f, z, 0.95f, 0.7f, 0.15f);
}

// ================= FOOD STORE STRUCT =================
void drawStore(float posX, float posZ)
{
    glPushMatrix();
    glTranslatef(posX, 0.0f, posZ);

    float darkWoodR = 0.30f; float darkWoodG = 0.18f; float darkWoodB = 0.10f;
    float woodR = 0.46f;     float woodG = 0.30f;     float woodB = 0.16f;

    // BACK WALL
    drawVoxel(0.0f, 3.0f, -1.5f, 9.0f, 6.0f, 0.7f, 0.26f, 0.17f, 0.09f);
    // FLOOR
    drawVoxel(0.0f, 0.2f, 1.5f, 10.0f, 0.4f, 5.5f, 0.65f, 0.58f, 0.42f);
    // MAIN PILLARS
    drawVoxel(-4.4f, 3.2f, 2.2f, 0.9f, 6.5f, 0.9f, darkWoodR, darkWoodG, darkWoodB);
    drawVoxel(4.4f, 3.2f, 2.2f, 0.9f, 6.5f, 0.9f, darkWoodR, darkWoodG, darkWoodB);
    // INNER PILLARS
    drawVoxel(-1.7f, 3.0f, 1.6f, 0.5f, 5.0f, 0.5f, darkWoodR, darkWoodG, darkWoodB);
    drawVoxel(1.7f, 3.0f, 1.6f, 0.5f, 5.0f, 0.5f, darkWoodR, darkWoodG, darkWoodB);
    // TOP BEAMS
    drawVoxel(0.0f, 6.1f, 2.0f, 9.4f, 0.7f, 0.8f, woodR, woodG, woodB);
    drawVoxel(0.0f, 5.4f, 1.2f, 8.5f, 0.4f, 0.6f, 0.33f, 0.20f, 0.10f);
    // SIGN BOARD
    drawVoxel(0.0f, 5.9f, 2.5f, 6.8f, 1.3f, 0.35f, 0.40f, 0.24f, 0.12f);
    drawVoxel(0.0f, 6.35f, 2.7f, 6.9f, 0.12f, 0.08f, 0.65f, 0.46f, 0.22f);
    
    // TEXT FOOD STORE
    drawText("FOOD STORE", -2.0f, 5.8f, 2.8f);

    // LEAF ROOF
    drawVoxel(0.0f, 7.0f, 1.8f, 10.5f, 1.2f, 4.0f, 0.12f, 0.42f, 0.08f);
    drawVoxel(0.0f, 7.9f, 1.5f, 9.0f, 0.9f, 3.0f, 0.16f, 0.52f, 0.10f);
    drawVoxel(0.0f, 8.5f, 1.2f, 7.5f, 0.7f, 2.2f, 0.20f, 0.60f, 0.14f);
    drawVoxel(-5.2f, 6.8f, 2.0f, 1.2f, 1.2f, 1.2f, 0.14f, 0.48f, 0.10f);
    drawVoxel(5.2f, 6.8f, 2.0f, 1.2f, 1.2f, 1.2f, 0.14f, 0.48f, 0.10f);

    // LEFT SHELVES & FRUITS
    drawVoxel(-2.9f, 2.0f, 1.3f, 2.0f, 0.12f, 1.6f, woodR, woodG, woodB);
    drawVoxel(-2.9f, 3.8f, 1.3f, 2.0f, 0.12f, 1.6f, woodR, woodG, woodB);
    drawFruitPile(-3.4f, 2.45f, 1.2f, 0.92f, 0.24f, 0.12f);
    drawFruitPile(-2.8f, 2.45f, 1.2f, 0.95f, 0.65f, 0.10f);
    drawFruitPile(-2.2f, 2.45f, 1.2f, 0.20f, 0.65f, 0.15f);
    drawFruitPile(-3.2f, 4.2f, 1.2f, 0.20f, 0.70f, 0.20f);
    drawFruitPile(-2.5f, 4.2f, 1.2f, 0.85f, 0.35f, 0.10f);

    // RIGHT SHELVES & FRUITS
    drawVoxel(2.9f, 2.0f, 1.3f, 2.0f, 0.12f, 1.6f, woodR, woodG, woodB);
    drawVoxel(2.9f, 3.8f, 1.3f, 2.0f, 0.12f, 1.6f, woodR, woodG, woodB);
    drawFruitPile(2.3f, 2.45f, 1.2f, 0.92f, 0.22f, 0.10f);
    drawFruitPile(2.9f, 2.45f, 1.2f, 0.95f, 0.70f, 0.12f);
    drawFruitPile(3.5f, 2.45f, 1.2f, 0.18f, 0.65f, 0.18f);
    drawFruitPile(2.5f, 4.2f, 1.2f, 0.96f, 0.50f, 0.08f);
    drawFruitPile(3.2f, 4.2f, 1.2f, 0.90f, 0.82f, 0.18f);

    // FRONT CRATES
    drawWoodCrate(-4.2f, 0.45f, 3.4f);
    drawWoodCrate(3.8f, 0.45f, 3.4f);
    drawVoxel(0.0f, 0.45f, 2.9f, 1.8f, 0.7f, 1.5f, 0.40f, 0.26f, 0.14f);
    drawFruitPile(-0.3f, 0.9f, 2.9f, 0.22f, 0.72f, 0.22f);
    drawFruitPile(0.4f, 0.9f, 2.9f, 0.92f, 0.35f, 0.10f);

    // SIDE LEAF DECOR
    drawVoxel(-5.3f, 3.8f, 1.4f, 1.2f, 3.8f, 1.2f, 0.10f, 0.38f, 0.08f);
    drawVoxel(5.3f, 3.8f, 1.4f, 1.2f, 3.8f, 1.2f, 0.10f, 0.38f, 0.08f);

    glPopMatrix();
}

// ================= DINO HIJAU =================
void dinoHijau(){
    glPushMatrix();
    glTranslatef(-7.0f, 1.2f, 4.0f); // Posisi keliling lapangan kiri depan

    float bob = fabs(sin(stepAngle)) * 0.15f;
    glTranslatef(0, bob, 0);

    drawVoxel(0,0,0,3,1.6,1.8,0.4,0.9,0);
    drawVoxel(1.4,0.9,0,1,1,1.2,0.4,0.9,0);
    drawVoxel(2.2,1.8,0,2.2,1.4,1.6,0.4,0.9,0,true);
    drawVoxel(-2,-0.2,0,1.6,0.8,1.2,0.3,0.7,0);

    float x[4]={-0.9f, -0.9f, 1.0f, 1.0f};
    float z[4]={0.7f, -0.7f, 0.7f, -0.7f};

    for(int i=0; i<4; i++){
        glPushMatrix();
        glTranslatef(x[i], 0.0f, z[i]);
        float ayun = (i==0 || i==3) ? sin(stepAngle*2)*20 : -sin(stepAngle*2)*20;
        glRotatef(ayun, 0, 0, 1);
        drawVoxel(0,-0.5,0,0.8,1,0.8,0.4,0.9,0);
        drawVoxel(0,-1.2,0,0.9,0.4,0.9,0.3,0.3,0.3);
        glPopMatrix();
    }
    glPopMatrix();
}

// ================= TRICERATOPS =================
void triceratops(){
    glPushMatrix();
    glTranslatef(7.0f, 1.2f, 4.0f); // Menjaga telur di kanan depan

    float bob = fabs(sin(stepAngle)) * 0.12f;
    glTranslatef(0, bob, 0);

    drawVoxel(0,0,0,3.5,2,2,0.8,0.1,0.1);
    drawVoxel(1.8,0.5,0,1,1.2,1.5,0.8,0.1,0.1);

    glPushMatrix();
    glRotatef(sin(stepAngle)*2, 0, 0, 1);
    drawVoxel(2.3,1.5,0,0.3,2.5,2.5,0.85,0.3,0);
    drawVoxel(2.7,0.8,0,1.5,1.4,1.4,0.8,0.1,0.1,true);
    drawVoxel(3.2,0.4,0,1,1,1,0.8,0.1,0.1);
    drawVoxel(2.9,1.6,0.4,0.3,0.8,0.3,0.9,0.8,0.6);
    drawVoxel(2.9,1.6,-0.4,0.3,0.8,0.3,0.9,0.8,0.6);
    drawVoxel(3.5,1.0,0,0.3,0.5,0.3,0.9,0.8,0.6);
    glPopMatrix();

    // EKOR
    glPushMatrix();
    glTranslatef(-1.8f, 0.2f, 0.0f);
    glRotatef(sin(stepAngle*0.5f)*5, 0, 1, 0);
    drawVoxel(-0.8f, 0, 0, 2.5f, 0.8f, 1.0f, 0.8f, 0.1f, 0.1f);
    glPopMatrix();

    // KAKI
    float x[4]={-1.0f, -1.0f, 1.2f, 1.2f};
    float z[4]={0.7f, -0.7f, 0.7f, -0.7f};
    for(int i=0; i<4; i++){
        glPushMatrix();
        glTranslatef(x[i], 0.0f, z[i]);
        float ayun = (i==0 || i==3) ? sin(stepAngle*1.5f)*20 : -sin(stepAngle*1.5f)*20;
        glRotatef(ayun, 0, 0, 1);
        drawVoxel(0,-0.6,0,0.8,1.2,0.8,0.8,0.1,0.1);
        drawVoxel(0,-1.2,0,0.9,0.4,0.9,0.3,0.3,0.3);
        glPopMatrix();
    }
    glPopMatrix();
}

// ================= PTERODACTYL =================
void ptero(){
    glPushMatrix();
    // Terbang melayang di atas area tengah langit
    float flyX = sin(stepAngle * 0.4f) * 4.0f;
    glTranslatef(flyX, 9.0f + sin(wingAngle*0.5f)*0.5f, 0.0f);

    drawVoxel(0,0,0,2.5,1.2,1.2,1,0.5,0);
    drawVoxel(1.2,0.6,0,0.8,1.2,0.8,1,0.5,0);
    drawVoxel(1.8,1.5,0,0.7,1.5,0.7,1,0.5,0);
    drawVoxel(2.4,2.8,0,0.6,1.8,0.6,1,0.5,0);
    drawVoxel(2.8,3.8,0,1.2,1,0.8,1,0.5,0,true);
    drawVoxel(4.5,3.6,0,3.5,0.5,0.6,1,0.8,0);
    drawVoxel(-1.8,0,0,1.2,0.4,0.6,1,0.5,0);

    float flap = sin(wingAngle)*30;
    // Sayap Kanan
    glPushMatrix();
    glTranslatef(0, 0.2f, 0.6f);
    glRotatef(flap, 1, 0, 0);
    drawVoxel(0, 0, 2, 2, 0.2f, 4, 1, 0.6f, 0.1f);
    glPopMatrix();

    // Sayap Kiri
    glPushMatrix();
    glTranslatef(0, 0.2f, -0.6f);
    glRotatef(-flap, 1, 0, 0);
    drawVoxel(0, 0, -2, 2, 0.2f, 4, 1, 0.6f, 0.1f);
    glPopMatrix();

    glPopMatrix();
}

// ================= POHON =================
void pohon(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    drawVoxel(0.0f, 2.0f, 0.0f, 1.0f, 4.0f, 1.0f, 0.4f, 0.25f, 0.1f); // Batang
    drawVoxel(0.0f, 0.3f, 0.0f, 1.6f, 0.8f, 1.6f, 0.35f, 0.2f, 0.05f); // Akar
    drawVoxel(0.8f, 4.0f, 0.0f, 0.6f, 0.4f, 0.4f, 0.4f, 0.25f, 0.1f); // Cabang
    drawVoxel(-0.8f, 4.0f, 0.0f, 0.6f, 0.4f, 0.4f, 0.4f, 0.25f, 0.1f);

    // Daun Layer
    drawVoxel(0.0f, 5.0f, 0.0f, 5.0f, 1.5f, 5.0f, 0.0f, 0.5f, 0.0f);
    drawVoxel(0.0f, 6.5f, 0.0f, 4.0f, 1.5f, 4.0f, 0.1f, 0.6f, 0.0f);
    drawVoxel(0.0f, 7.8f, 0.0f, 2.5f, 1.2f, 2.5f, 0.2f, 0.7f, 0.0f);
    drawVoxel(0.0f, 8.8f, 0.0f, 1.2f, 1.0f, 1.2f, 0.3f, 0.8f, 0.0f);

    // Semak
    drawVoxel(1.2f, 0.3f, 1.2f, 0.8f, 0.8f, 0.8f, 0.0f, 0.45f, 0.0f);
    drawVoxel(-1.2f, 0.3f, -1.2f, 0.8f, 0.8f, 0.8f, 0.0f, 0.45f, 0.0f);

    glPopMatrix();
}

// ================= TELUR =================
void telur(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    float r = 0.92f, g = 0.85f, b = 0.65f;

    drawVoxel(0.0f, 0.0f, 0.0f, 0.6f, 0.3f, 0.6f, r, g, b);
    drawVoxel(0.0f, 0.3f, 0.0f, 1.0f, 0.4f, 1.0f, r, g, b);
    drawVoxel(0.0f, 0.8f, 0.0f, 1.4f, 0.5f, 1.4f, r, g, b);
    drawVoxel(0.0f, 1.3f, 0.0f, 1.6f, 0.6f, 1.6f, r, g, b);
    drawVoxel(0.0f, 1.9f, 0.0f, 1.4f, 0.5f, 1.4f, r, g, b);
    drawVoxel(0.0f, 2.4f, 0.0f, 1.0f, 0.4f, 1.0f, r, g, b);
    drawVoxel(0.0f, 2.8f, 0.0f, 0.6f, 0.3f, 0.6f, r, g, b);
    glPopMatrix();
}

// ================= DISPLAY =================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Sudut pandang kamera sinematik agar semua objek tertangkap ideal
    gluLookAt(
        0.0, 10.0, 22.0,  // Kamera agak tinggi mundur ke belakang
        0.0, 3.5, 0.0,   // Melihat ke arah tengah map
        0.0, 1.0, 0.0
    );

    glRotatef(rotY, 0, 1, 0);

    // GROUND (Tanah Lapang Hijau)
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.45f, 0.63f, 0.28f);
    glVertex3f(-35, 0, -35);
    glVertex3f(35, 0, -35);
    glVertex3f(35, 0, 35);
    glVertex3f(-35, 0, 35);
    glEnd();
    glEnable(GL_LIGHTING);

    // 1. RENDER FOOD STORE (Ditempatkan di tengah belakang)
    drawStore(0.0f, -6.0f);

    // 2. RENDER DINOSAURUS & ANIMAISNYA
    dinoHijau();   // Lapangan Kiri
    triceratops(); // Lapangan Kanan (Menjaga telur)
    ptero();       // Di Langit

    // 3. RENDER LINGKUNGAN (Pohon Alami)
    pohon(-13.0f, -10.0f);
    pohon(-14.0f, 8.0f);
    pohon(14.0f, -10.0f);

    // 4. RENDER SARANG TELUR (Di dekat kaki depan Triceratops)
    telur(7.0f, 8.0f);
    telur(8.5f, 7.5f);
    telur(7.5f, 6.5f);

    glutSwapBuffers();
}

// ================= TIMER =================
void timer(int v){
    stepAngle += 0.08f;
    wingAngle += 0.12f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// ================= INIT =================
void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    // Warna langit cerah damai (Sky Blue)
    glClearColor(0.55f, 0.78f, 0.96f, 1.0f);

    GLfloat light_pos[] = {18.0f, 22.0f, 15.0f, 1.0f};
    GLfloat ambient[]   = {0.45f, 0.45f, 0.45f, 1.0f};
    GLfloat diffuse[]   = {0.95f, 0.95f, 0.95f, 1.0f};
    GLfloat specular[]  = {1.0f, 1.0f, 1.0f, 1.0f};

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
    gluPerspective(45.0, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// ================= MAIN =================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Detailed Voxel Storyboard - Scene 1 Final");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}



