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

/*
 * FreeGLUT Animation - Scene 1: Dunia Dino yang Damai
 * Mengintegrasikan Detail Voxel Food Store, Dino Hijau, Triceratops, Pterodactyl, Pohon, dan Telur.
 */


#include <GL/glut.h>
#include <cmath>

// ================= GLOBAL =================
float stepAngle = 0.0f;
float wingAngle = 0.0f;
float camX = 0.0f;
float camY = 10.0f;
float camZ = 22.0f;

float lookX = 0.0f;
float lookY = 3.5f;
float lookZ = 0.0f;

float camAngle = 0.0f;

// ================= GLOBAL VARIABLES =================

float rotY = 0.0f; // Bisa diubah jika ingin memutar seluruh world
float cloudMove = 0.0f;

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




// ================= TRICERATOPS (UPGRADE - DIAM TOTAL) =================
void triceratops(){
    glPushMatrix();
    glTranslatef(6,1.2f,0); // biar napak tanah

    // putar agar menghadap telur
    glRotatef(-140.0f, 0.0f, 1.0f, 0.0f);
    
    // Efek bob (naik-turun tubuh) dihilangkan agar diam

    // tubuh
    drawVoxel(0,0,0,3.5,2,2,0.8,0.1,0.1);
    drawVoxel(1.8,0.5,0,1,1.2,1.5,0.8,0.1,0.1);

    // kepala (diam, rotasi dihilangkan)
    glPushMatrix();
    // glRotatef dihilangkan agar kepala tidak bergerak

    drawVoxel(2.3,1.5,0,0.3,2.5,2.5,0.85,0.3,0);
    drawVoxel(2.7,0.8,0,1.5,1.4,1.4,0.8,0.1,0.1,true);
    drawVoxel(3.2,0.4,0,1,1,1,0.8,0.1,0.1);

    // tanduk
    drawVoxel(2.9,1.6,0.4,0.3,0.8,0.3,0.9,0.8,0.6);
    drawVoxel(2.9,1.6,-0.4,0.3,0.8,0.3,0.9,0.8,0.6);
    drawVoxel(3.5,1.0,0,0.3,0.5,0.3,0.9,0.8,0.6);

    glPopMatrix();

    // EKOR (diam, rotasi goyangan dihilangkan)
    glPushMatrix();
    glTranslatef(-1.8,0.2,0);
    drawVoxel(-0.8,0,0,2.5,0.8,1,0.8,0.1,0.1);
    glPopMatrix();

    // kaki (diam tegak berdiri, ayunan kaki dihilangkan)
    float x[4]={-1,-1,1.2,1.2};
    float z[4]={0.7,-0.7,0.7,-0.7};

    for(int i=0;i<4;i++){
        glPushMatrix();
        glTranslatef(x[i], 0.0f, z[i]);

        // Variabel ayun dan glRotatef dihilangkan agar kaki tidak melangkah

        drawVoxel(0,-0.6,0,0.8,1.2,0.8,0.8,0.1,0.1);
        drawVoxel(0,-1.2,0,0.9,0.4,0.9,0.3,0.3,0.3);
        glPopMatrix();
    }

    glPopMatrix();
}


// ================= PTERODACTYL (UPGRADE FULL) =================
void ptero(){
    glPushMatrix();

    glTranslatef(0,4 + sin(wingAngle*0.5)*0.5,0);

    // tubuh
    drawVoxel(0,0,0,2.5,1.2,1.2,1,0.5,0);

    // leher panjang
    drawVoxel(1.2,0.6,0,0.8,1.2,0.8,1,0.5,0);
    drawVoxel(1.8,1.5,0,0.7,1.5,0.7,1,0.5,0);
    drawVoxel(2.4,2.8,0,0.6,1.8,0.6,1,0.5,0);

    // kepala + paruh
    drawVoxel(2.8,3.8,0,1.2,1,0.8,1,0.5,0,true);
    drawVoxel(4.5,3.6,0,3.5,0.5,0.6,1,0.8,0);

    // ekor kecil
    drawVoxel(-1.8,0,0,1.2,0.4,0.6,1,0.5,0);

    float flap = sin(wingAngle)*30;

    // sayap kanan
    glPushMatrix();
    glTranslatef(0,0.2,0.6);
    glRotatef(flap,1,0,0);
    drawVoxel(0,0,2,2,0.2,4,1,0.6,0.1);
    glPopMatrix();

    // sayap kiri
    glPushMatrix();
    glTranslatef(0,0.2,-0.6);
    glRotatef(-flap,1,0,0);
    drawVoxel(0,0,-2,2,0.2,4,1,0.6,0.1);
    glPopMatrix();

    glPopMatrix();
}


// ================= POHON =================
void pohon(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    // 1. BATANG
    drawVoxel(0.0f, 2.0f, 0.0f, 1.0f, 4.0f, 1.0f, 0.4f, 0.25f, 0.1f);

    // Akar
    drawVoxel(0.0f, 0.3f, 0.0f, 1.6f, 0.8f, 1.6f, 0.35f, 0.2f, 0.05f);

    // Cabang
    drawVoxel(0.8f, 4.0f, 0.0f, 0.6f, 0.4f, 0.4f, 0.4f, 0.25f, 0.1f);
    drawVoxel(-0.8f, 4.0f, 0.0f, 0.6f, 0.4f, 0.4f, 0.4f, 0.25f, 0.1f);

    // 2. DAUN (Layer)
    drawVoxel(0.0f, 5.0f, 0.0f, 5.0f, 1.5f, 5.0f, 0.0f, 0.5f, 0.0f);
    drawVoxel(0.0f, 6.5f, 0.0f, 4.0f, 1.5f, 4.0f, 0.1f, 0.6f, 0.0f);
    drawVoxel(0.0f, 7.8f, 0.0f, 2.5f, 1.2f, 2.5f, 0.2f, 0.7f, 0.0f);
    drawVoxel(0.0f, 8.8f, 0.0f, 1.2f, 1.0f, 1.2f, 0.3f, 0.8f, 0.0f);

    // 3. SEMAK-SEMAK
    drawVoxel(1.2f, 0.3f, 1.2f, 0.8f, 0.8f, 0.8f, 0.0f, 0.45f, 0.0f);
    drawVoxel(-1.2f, 0.3f, -1.2f, 0.8f, 0.8f, 0.8f, 0.0f, 0.45f, 0.0f);

    glPopMatrix();
}
//Awan
void awan(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);

    // matikan lighting supaya awan tetap putih cerah
    glDisable(GL_LIGHTING);

    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;

    drawVoxel(0.0f, 0.0f, 0.0f, 3.0f, 1.5f, 2.0f, r, g, b);
    drawVoxel(2.0f, 0.3f, 0.0f, 2.5f, 1.2f, 2.0f, r, g, b);
    drawVoxel(-2.0f, 0.2f, 0.0f, 2.5f, 1.2f, 2.0f, r, g, b);
    drawVoxel(0.0f, 0.8f, 0.0f, 2.0f, 1.0f, 2.0f, r, g, b);

    // hidupkan lighting lagi
    glEnable(GL_LIGHTING);

    glPopMatrix();
}
// ================= TELUR =================

void telur(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    float r = 0.92f, g = 0.85f, b = 0.65f;

    // Versi DIPERKECIL (±50% dari aslinya)

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
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
    camX, camY, camZ,
    lookX, lookY, lookZ,
    0.0, 1.0, 0.0
);
    
    glRotatef(rotY, 0, 1, 0);

    // lantai
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.2,0.5,0.2);
    glVertex3f(-30,0,-30);
    glVertex3f(30,0,-30);
    glVertex3f(30,0,30);
    glVertex3f(-30,0,30);
    glEnd();
    glEnable(GL_LIGHTING);

    
    // dinosaurus
	triceratops();
	ptero();

	// pohon
	pohon(-10,-10);
	pohon(-10,10);
	pohon(10,-10);
	

	// telur
	telur(0,5);
	telur(-5,-5);
	telur(5,5);

 //awan   
awan(-15, 10, -10);
awan(10, 11, -5);

awan(18, 10, 5);

    

    // 1. RENDER FOOD STORE (Ditempatkan di tengah belakang)
    drawStore(0.0f, -6.0f);



    // 5. RENDER TELUR (Dibuat berdekatan/merapat membentuk kluster sarang)
    telur(1.0f, 6.0f);
    telur(2.2f, 5.8f);
    telur(1.6f, 7.0f);

    glutSwapBuffers();
}

    


// ================= TIMER =================
void timer(int v){
    stepAngle += 0.08f;
    wingAngle += 0.12f;

    glutPostRedisplay();
    glutTimerFunc(16,timer,0);
    
camY = 10 + sin(stepAngle * 0.2f) * 0.5f;
cloudMove += 0.01f;
}

// ================= INIT =================
void init(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.5,0.8,1,1);

    GLfloat light_pos[]={20,30,20,1};
    glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
}

// ================= RESHAPE =================
void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(float)w/h,1,100);
    glMatrixMode(GL_MODELVIEW);
}

// ================= MAIN =================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Dunia DinosaurusLengkapFINAL  1");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}

