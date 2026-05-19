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
#include <vector>

// Struktur untuk menyimpan data voxel individu
struct Voxel {
    float x, y, z;
    float r, g, b;
};

std::vector<Voxel> voxelWorld;

// Fungsi untuk menambahkan balok voxel kustom ke dunia
void addVoxel(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b) {
    // Kita menambahkan beberapa voxel solid untuk mereplikasi balok-balok di gambar
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Fungsi untuk menggambar pemandangan voxel lengkap
void drawVoxelWorld() {
    // 1. Gambar LAUT (Air - Hijau Toska/Cyan)
    // Direplikasi sebagai satu balok voxel tipis dan luas di permukaan air
    addVoxel(0.0f, -0.1f, 0.0f, 100.0f, 0.2f, 100.0f, 0.0f, 0.8f, 0.7f); // Air atas

    // 2. Gambar PANTAI & DATARAN (Pasir - Krem & Rumput - Hijau Cerah)
    // Tumpukan voxel untuk mereplikasi balok-balok pantai dan tanah
    for(int x = -10; x < 15; x++) {
        for(int z = -15; z < 20; z++) {
            // Pasir Pantai (Krem)
            if(x > 2 && x < 8 && z > -10 && z < 15) {
                addVoxel((float)x, 0.0f, (float)z, 1.0f, 0.2f, 1.0f, 0.9f, 0.85f, 0.6f);
            }
            // Tanah Rumput (Hijau Cerah)
            if(x > 8 && x < 13 && z > -15 && z < 18) {
                addVoxel((float)x, 0.1f, (float)z, 1.0f, 0.2f, 1.0f, 0.2f, 0.8f, 0.1f); // Tanah
                addVoxel((float)x, 0.2f, (float)z, 1.0f, 0.1f, 1.0f, 0.2f, 0.9f, 0.1f); // Rumput atas
            }
        }
    }

    // 3. Gambar HUTAN POHON VOXEL (Voxel Trees)
    // Mereplikasi posisi pohon-pohon di gambar
    float treePos[5][2] = {
        {10.0f, -5.0f}, {11.0f, 2.0f}, {11.0f, 8.0f}, 
        {12.0f, -8.0f}, {12.0f, -1.0f}
    };
    
    for(int i = 0; i < 5; i++) {
        // Batang (Cokelat)
        addVoxel(treePos[i][0], 1.0f, treePos[i][1], 0.6f, 1.6f, 0.6f, 0.5f, 0.35f, 0.15f);
        // Daun (Hijau Tua Berlapis)
        // Lapisan Daun Bawah
        addVoxel(treePos[i][0], 2.0f, treePos[i][1], 2.5f, 1.2f, 2.5f, 0.0f, 0.6f, 0.0f);
        // Lapisan Daun Atas
        addVoxel(treePos[i][0], 2.8f, treePos[i][1], 1.8f, 1.0f, 1.8f, 0.0f, 0.65f, 0.0f);
        // Puncak Daun
        addVoxel(treePos[i][0], 3.4f, treePos[i][1], 1.0f, 0.6f, 1.0f, 0.0f, 0.7f, 0.0f);
    }

  
    // 5. Gambar AWAN VOXEL TUNGGAL (Awan putih di langit)
    addVoxel(-20.0f, 8.0f, 20.0f, 2.0f, 0.4f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera sudut pandang isometrik meniru gambar
    gluLookAt(25.0, 15.0, 25.0,  // Posisi kamera (Diagonal kanan atas)
              0.0, 0.0, 0.0,   // Titik fokus (Tengah dataran)
              0.0, 1.0, 0.0);  // Vektor up

    // Gambar Dunia Voxel
    drawVoxelWorld();

    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    // Warna Background (Biru Langit Minecraft)
    glClearColor(0.45f, 0.75f, 1.0f, 1.0f);

    // Pengaturan Cahaya agar solid/flat (Minimal Ambient, Cahaya diagonal)
    GLfloat light_position[] = { 10.0f, 15.0f, 10.0f, 1.0f };
    GLfloat light_diffuse[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat light_ambient[]  = { 0.4f, 0.4f, 0.4f, 1.0f }; // Solid shading

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
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
    glutInitWindowSize(1200, 900); // Ukuran jendela besar meniru gambar
    glutCreateWindow("Pemandangan Pantai Voxel Replika");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
