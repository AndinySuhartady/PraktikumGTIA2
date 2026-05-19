
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
//Posisi kamera
float x = 0.0f;
float y = 2.0f;
float z = 15.0f;
//Arah pandang
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

//Membuat batas
    const float Z_MIN = -50;
    const float Z_MAX =  50;

    const float X_MIN = -50;
    const float X_MAX =  50;

//Menentukan kerapatan
    const float gap = 1.5f;
//Mematikan efek cahaya agar garis grid terlihat
    glDisable(GL_LIGHTING);
//Mmemberikan warna pada garis
    glColor3f(0.5f, 0.5f, 0.5f);
    
//Menggambar garis
    glBegin(GL_LINES);
//Mnenggambar garis vertikan di sepanjang sumbu z
    for(i = Z_MIN; i <= Z_MAX; i += gap)
    {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
//Menggambar garis horizontal sepanjang sumbu x
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
//Membuat bentuk donat berbentuk hitam
    // Ban
    glColor3f(0.1f, 0.1f, 0.1f);
    glutSolidTorus(0.15, 0.35, 30, 30);
//Mmembuat lingkaran bola di tengah ban
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

    // Rotasi mobil(Memmungkinkan mobil berotasi pada sumbu Y)
    glRotatef(rotMobil, 0, 1, 0);

    // ======================================
    // BADAN MOBIL
    // ======================================
    glPushMatrix();
//Kubus yang dipiphkan
        glScalef(4.0f, 1.0f, 2.0f);

        // badan solid
        glLineWidth(3.0f);
        //ungu
        glColor3f(0.6f, 0.0f, 0.8f);
        glutSolidCube(1.5);

        // rangka
        glLineWidth(3.0f);
        //putih
        glColor3f(1.0f, 1.0f, 1.0f);
        glutWireCube(1.52);

    glPopMatrix();

    // ======================================
    // ATAP MOBIL
    // ======================================
    glPushMatrix();
//Terletak di atas badan mobil
//X= kiri dan kanan
//Y= bawah dan atas(+) satuan
//Z=belakang dan depan
        glTranslatef(0.0f, 1.0f, 0.0f);

        glScalef(2.0f, 1.0f, 2.0f);

        // atap solid warna pink
        glColor3f(1.0f, 0.4f, 0.7f);
        glutSolidCube(1.2);

        // rangka atap warna putih
        glColor3f(1.0f, 1.0f, 1.0f);
        glutWireCube(1.22);

    glPopMatrix();



    // ======================================
    // RODA DEPAN KIRI
    // ======================================
    glPushMatrix();
//Semua roda diturunkan ke bawah badan mobil
        glTranslatef(-2.0f, -0.8f, 1.5f);
        //Roda diputar dalam sumbu z
        glRotatef(90, 0, 0, 1);

        Roda();
//Pop/push ytanpa mempengaruhi roda lain
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
//Bola kecil radius 0.2
        glutSolidSphere(0.2f, 20, 20);

    glPopMatrix();

    glPushMatrix();
//Lampu di X adalah bagian ujung mobil
//Lampu di Y ada di tengah tengah mobil
//Lampu Z ynag di memisahkan lampu di mobil
        glTranslatef(3.1f, 0.0f, -0.7f);
//Warna kuning
        glColor3f(1.0f, 1.0f, 0.0f);

        glutSolidSphere(0.2f, 20, 20);

    glPopMatrix();

    glPopMatrix();
}

// ==========================================
// ORIENTASI KAMERA
// ==========================================
//Menengok menghintung lx dan lz
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
//Berjalan (Menjalankan kamera)
void moveMeFlat(int i)
{
    x = x + i * lx * 0.2f;
    z = z + i * lz * 0.2f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//Mata kamera
    gluLookAt(
    //posisi mata
        x, y, z,
        //titik fokus
        x + lx, y + ly, z + lz,
        //arah atas
        0.0f, 1.0f, 0.0f
    );
}

// ==========================================
// DISPLAY
// ==========================================
void display()
{
	//update posisi
    if(deltaMove)
        moveMeFlat(deltaMove);

    if(deltaAngle)
    {
        angle += deltaAngle;
        orientMe(angle);
    }
//bersih layar
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);

    // Grid panggil
    Grid();

    // Mobil
    glPushMatrix();
//gambar mobil
        glTranslatef(0.0f, 1.0f, 0.0f);

        Mobil();

    glPopMatrix();
//menampilkkan secara halus
    glutSwapBuffers();
}

// ==========================================
// RESHAPE
// ==========================================
//agar tidak distorsi
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

//mengatur sudut pandang
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
//kiri kanan
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
//kamera berhenti sejenak
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
	//memastikan objek jauh tertutup
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
    //sistem cahaya aktif dan memastikan warna tidak pecah
    glEnable(GL_COLOR_MATERIAL);
//hidup lampu
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//mengatur bagaimana permukaan mobil pantul cahaya
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
	//mengaktifkan sensor
    glEnable(GL_DEPTH_TEST);
//memastikan semua bentuk seperti kubus digambar padat
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//menentukan latar belakang
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

// ==========================================
// MAIN
// ==========================================
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//membuat ukuran jendela aplikasi
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 600);

    glutCreateWindow("Mobil3D OpenGL");

    init();
    lighting();
//menggambar ulang 
    glutDisplayFunc(display);
    glutIdleFunc(display);
//menghubungkan tombol panah keyboard dan kamera
    glutReshapeFunc(Reshape);

    glutKeyboardFunc(keyboard);

    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
//program berjalan
    glutMainLoop();

    return 0;
}


