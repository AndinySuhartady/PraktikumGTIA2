#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

// --- Helper Functions ---
void drawVoxel(float x, float y, float z, float sx, float sy, float sz, float r, float g, float b, bool adaMata = false) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    if (adaMata) {
        glDisable(GL_LIGHTING);
        glColor3f(0.0f, 0.0f, 0.0f); // Black eye
        
        // Kanan
        glPushMatrix();
        glTranslatef(0.2f, 0.15f, 0.51f); 
        glScalef(0.2f, 0.25f, 0.1f);
        glutSolidCube(1.0);
        glPopMatrix();
        
        // Kiri
        glPushMatrix();
        glTranslatef(0.2f, 0.15f, -0.51f); 
        glScalef(0.2f, 0.25f, 0.1f);
        glutSolidCube(1.0);
        glPopMatrix();
        
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();
}

void drawFruitPile(float x, float y, float z, float r, float g, float b) {
    drawVoxel(x, y, z, 0.35f, 0.35f, 0.35f, r, g, b);
    drawVoxel(x + 0.28f, y, z, 0.35f, 0.35f, 0.35f, r * 0.9f, g * 0.9f, b);
    drawVoxel(x - 0.28f, y, z, 0.35f, 0.35f, 0.35f, r, g * 0.8f, b);
    drawVoxel(x, y + 0.25f, z, 0.3f, 0.3f, 0.3f, r, g, b);
}

void drawWoodCrate(float x, float y, float z) {
    drawVoxel(x, y, z, 1.6f, 0.7f, 1.4f, 0.45f, 0.28f, 0.14f);
    drawVoxel(x, y + 0.28f, z + 0.55f, 1.5f, 0.08f, 0.08f, 0.62f, 0.4f, 0.2f);
    drawVoxel(x, y + 0.28f, z - 0.55f, 1.5f, 0.08f, 0.08f, 0.62f, 0.4f, 0.2f);
    drawFruitPile(x - 0.3f, y + 0.4f, z, 0.9f, 0.2f, 0.1f);
    drawFruitPile(x + 0.3f, y + 0.42f, z, 0.95f, 0.7f, 0.15f);
}

void drawTelur(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.46f, z); // 0.46f disesuaikan agar pas di lantai saat skala membesar
    glScalef(0.5f, 0.5f, 0.5f); // Skala diperbesar
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

void drawPohon(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    
    // BATANG POHON (Cokelat)
    drawVoxel(0.0f, 2.0f, 0.0f, 1.0f, 4.0f, 1.0f, 0.4f, 0.25f, 0.1f);
    drawVoxel(0.0f, 0.3f, 0.0f, 1.6f, 0.8f, 1.6f, 0.35f, 0.2f, 0.05f); // Akar
    drawVoxel(0.8f, 4.0f, 0.0f, 0.6f, 0.4f, 0.4f, 0.4f, 0.25f, 0.1f); // Cabang
    drawVoxel(-0.8f, 4.0f, 0.0f, 0.6f, 0.4f, 0.4f, 0.4f, 0.25f, 0.1f);

    // DAUN (Gradasi Hijau)
    drawVoxel(0.0f, 5.0f, 0.0f, 5.0f, 1.5f, 5.0f, 0.0f, 0.5f, 0.0f);
    drawVoxel(0.0f, 6.5f, 0.0f, 4.0f, 1.5f, 4.0f, 0.1f, 0.6f, 0.0f);
    drawVoxel(0.0f, 7.8f, 0.0f, 2.5f, 1.2f, 2.5f, 0.2f, 0.7f, 0.0f);
    drawVoxel(0.0f, 8.8f, 0.0f, 1.2f, 1.0f, 1.2f, 0.3f, 0.8f, 0.0f);

    // SEMAK-SEMAK
    drawVoxel(1.2f, 0.3f, 1.2f, 0.8f, 0.8f, 0.8f, 0.0f, 0.45f, 0.0f);
    drawVoxel(-1.2f, 0.3f, -1.2f, 0.8f, 0.8f, 0.8f, 0.0f, 0.45f, 0.0f);

    glPopMatrix();
}

void drawBatu(float x, float y, float z, float scale) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);
    drawVoxel(0.0f, 0.5f, 0.0f, 1.5f, 0.8f, 1.2f, 0.5f, 0.5f, 0.5f);
    drawVoxel(0.5f, 0.4f, 0.5f, 1.2f, 0.6f, 1.0f, 0.45f, 0.45f, 0.45f);
    drawVoxel(-0.6f, 0.3f, -0.4f, 1.0f, 0.5f, 1.0f, 0.55f, 0.55f, 0.55f);
    glPopMatrix();
}

void drawAwan(float x, float y, float z, float scale) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);
    glDisable(GL_LIGHTING); // Biar warnanya solid putih
    drawVoxel(0.0f, 0.0f, 0.0f, 2.5f, 1.0f, 1.5f, 1.0f, 1.0f, 1.0f);
    drawVoxel(1.2f, 0.5f, 0.2f, 1.5f, 1.2f, 1.2f, 1.0f, 1.0f, 1.0f);
    drawVoxel(-1.2f, 0.3f, -0.2f, 1.8f, 1.2f, 1.3f, 1.0f, 1.0f, 1.0f);
    drawVoxel(0.5f, 0.6f, -0.5f, 1.5f, 1.5f, 1.5f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void drawStore(float cT) {
    float darkWoodR = 0.30f, darkWoodG = 0.18f, darkWoodB = 0.10f;
    float woodR = 0.46f, woodG = 0.30f, woodB = 0.16f;

    float t = (cT > 1.2f) ? 1.2f : cT;

    // FLOOR (Stays somewhat put, shaking slightly)
    glPushMatrix();
    drawVoxel(0.0f, 0.2f, 1.5f, 10.0f, 0.4f, 5.5f, 0.65f, 0.58f, 0.42f);
    glPopMatrix();

    // BACK WALL
    glPushMatrix();
    if (t > 0) { float y = -5.0f * t * t; if(y < -3.0f) y = -3.0f; glTranslatef(0, y, t * -3.0f); glRotatef(t * -30.0f, 1, 0, 0); }
    drawVoxel(0.0f, 3.0f, -1.5f, 9.0f, 6.0f, 0.7f, 0.26f, 0.17f, 0.09f);
    glPopMatrix();

    // MAIN PILLARS
    glPushMatrix();
    if (t > 0) { float y = -5.0f * t * t; if(y < -3.0f) y = -3.0f; glTranslatef(-t * 2.0f, y, t * -2.0f); glRotatef(t * -40.0f, 1, 0, 1); }
    drawVoxel(-4.4f, 3.2f, 2.2f, 0.9f, 6.5f, 0.9f, darkWoodR, darkWoodG, darkWoodB);
    glPopMatrix();

    glPushMatrix();
    if (t > 0) { float y = -5.0f * t * t; if(y < -3.0f) y = -3.0f; glTranslatef(t * 2.0f, y, t * -2.0f); glRotatef(t * -40.0f, 1, 0, -1); }
    drawVoxel(4.4f, 3.2f, 2.2f, 0.9f, 6.5f, 0.9f, darkWoodR, darkWoodG, darkWoodB);
    glPopMatrix();

    // INNER PILLARS
    glPushMatrix();
    if (t > 0) { float y = -5.0f * t * t; if(y < -2.0f) y = -2.0f; glTranslatef(-t * 1.5f, y, t * -2.5f); glRotatef(t * -50.0f, 1, 0, 1); }
    drawVoxel(-1.7f, 3.0f, 1.6f, 0.5f, 5.0f, 0.5f, darkWoodR, darkWoodG, darkWoodB);
    glPopMatrix();

    glPushMatrix();
    if (t > 0) { float y = -5.0f * t * t; if(y < -2.0f) y = -2.0f; glTranslatef(t * 1.5f, y, t * -2.5f); glRotatef(t * -50.0f, 1, 0, -1); }
    drawVoxel(1.7f, 3.0f, 1.6f, 0.5f, 5.0f, 0.5f, darkWoodR, darkWoodG, darkWoodB);
    glPopMatrix();

    // TOP BEAMS & SIGN BOARD
    glPushMatrix();
    if (t > 0) { float y = 2.0f * t - 8.0f * t * t; if(y < -5.0f) y = -5.0f; glTranslatef(0, y, t * -2.0f); glRotatef(t * -90.0f, 1, 0, 0); }
    drawVoxel(0.0f, 6.1f, 2.0f, 9.4f, 0.7f, 0.8f, woodR, woodG, woodB);
    drawVoxel(0.0f, 5.4f, 1.2f, 8.5f, 0.4f, 0.6f, 0.33f, 0.20f, 0.10f);
    drawVoxel(0.0f, 5.9f, 2.5f, 6.8f, 1.3f, 0.35f, 0.40f, 0.24f, 0.12f);
    drawVoxel(0.0f, 6.35f, 2.7f, 6.9f, 0.12f, 0.08f, 0.65f, 0.46f, 0.22f);
    glPopMatrix();

    // LEAF ROOF
    glPushMatrix();
    if (t > 0) { float y = 3.0f * t - 6.0f * t * t; if(y < -6.0f) y = -6.0f; glTranslatef(0, y, t * -3.0f); glRotatef(t * -45.0f, 1, 0, 0); }
    drawVoxel(0.0f, 7.0f, 1.8f, 10.5f, 1.2f, 4.0f, 0.12f, 0.42f, 0.08f);
    drawVoxel(0.0f, 7.9f, 1.5f, 9.0f, 0.9f, 3.0f, 0.16f, 0.52f, 0.10f);
    drawVoxel(0.0f, 8.5f, 1.2f, 7.5f, 0.7f, 2.2f, 0.20f, 0.60f, 0.14f);
    glPopMatrix();

    // LEFT SHELVES
    glPushMatrix();
    if (t > 0) { float y = 1.0f * t - 8.0f * t * t; if(y < -2.0f) y = -2.0f; glTranslatef(-t * 2.0f, y, t * -1.0f); glRotatef(t * 70.0f, 0, 0, 1); glRotatef(t * 60.0f, 1, 0, 0); }
    drawVoxel(-2.9f, 2.0f, 1.3f, 2.0f, 0.12f, 1.6f, woodR, woodG, woodB);
    drawVoxel(-2.9f, 3.8f, 1.3f, 2.0f, 0.12f, 1.6f, woodR, woodG, woodB);
    drawFruitPile(-3.4f, 2.45f, 1.2f, 0.92f, 0.24f, 0.12f);
    drawFruitPile(-2.8f, 2.45f, 1.2f, 0.95f, 0.65f, 0.10f);
    drawFruitPile(-3.2f, 4.2f, 1.2f, 0.20f, 0.70f, 0.20f);
    glPopMatrix();

    // RIGHT SHELVES
    glPushMatrix();
    if (t > 0) { float y = 1.0f * t - 8.0f * t * t; if(y < -2.0f) y = -2.0f; glTranslatef(t * 2.0f, y, t * -1.0f); glRotatef(t * -70.0f, 0, 0, 1); glRotatef(t * 60.0f, 1, 0, 0); }
    drawVoxel(2.9f, 2.0f, 1.3f, 2.0f, 0.12f, 1.6f, woodR, woodG, woodB);
    drawVoxel(2.9f, 3.8f, 1.3f, 2.0f, 0.12f, 1.6f, woodR, woodG, woodB);
    drawFruitPile(2.3f, 2.45f, 1.2f, 0.92f, 0.22f, 0.10f);
    drawFruitPile(2.9f, 2.45f, 1.2f, 0.95f, 0.70f, 0.12f);
    drawFruitPile(3.2f, 4.2f, 1.2f, 0.90f, 0.82f, 0.18f);
    glPopMatrix();

    // FRONT CRATES
    glPushMatrix();
    if (t > 0) { float y = 2.0f * t - 10.0f * t * t; if(y < -0.5f) y = -0.5f; glTranslatef(-t * 2.0f, y, t * 2.0f); glRotatef(t * 120.0f, 1, 1, 0); }
    drawWoodCrate(-4.2f, 0.45f, 3.4f);
    glPopMatrix();

    glPushMatrix();
    if (t > 0) { float y = 2.0f * t - 10.0f * t * t; if(y < -0.5f) y = -0.5f; glTranslatef(t * 2.0f, y, t * 2.0f); glRotatef(t * 120.0f, -1, 1, 0); }
    drawWoodCrate(3.8f, 0.45f, 3.4f);
    glPopMatrix();
    
    // 2 Telur Dino yang selamat di reruntuhan toko
    if (t > 0) {
        drawTelur(-1.0f, 1.0f);
        drawTelur(1.2f, 0.5f);
    }
}

void drawTRex(float stepAngle, bool isTalking = false) {
    glPushMatrix();
    glTranslatef(0.0f, fabs(sin(stepAngle)) * 0.15f, 0.0f);
    // Bagian Tubuh Utama
    drawVoxel(0.0f, 0.0f, 0.0f, 3.0f, 1.6f, 1.8f, 0.4f, 0.9f, 0.0f);
    // Leher
    drawVoxel(1.4f, 0.9f, 0.0f, 1.0f, 1.0f, 1.2f, 0.4f, 0.9f, 0.0f);
    
    // Kepala
    glPushMatrix();
    float jawAngle = 0.0f;
    if (isTalking) {
        float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        jawAngle = (sin(time * 15.0f) * 0.5f + 0.5f) * -20.0f; // Buka tutup mulut
    }
    
    // Rahang Atas (Mata & Moncong atas)
    drawVoxel(2.2f, 2.0f, 0.0f, 2.2f, 1.0f, 1.6f, 0.4f, 0.9f, 0.0f, true);
    
    // Taring Atas
    drawVoxel(2.6f, 1.5f, 0.7f, 0.15f, 0.3f, 0.15f, 0.9f, 0.9f, 0.9f); // Kanan belakang
    drawVoxel(3.1f, 1.5f, 0.7f, 0.15f, 0.3f, 0.15f, 0.9f, 0.9f, 0.9f); // Kanan depan
    drawVoxel(2.6f, 1.5f, -0.7f, 0.15f, 0.3f, 0.15f, 0.9f, 0.9f, 0.9f); // Kiri belakang
    drawVoxel(3.1f, 1.5f, -0.7f, 0.15f, 0.3f, 0.15f, 0.9f, 0.9f, 0.9f); // Kiri depan
    
    // Rahang Bawah
    glPushMatrix();
    glTranslatef(1.1f, 1.5f, 0.0f); // Titik putar rahang
    glRotatef(jawAngle, 0, 0, 1);
    glTranslatef(-1.1f, -1.5f, 0.0f);
    drawVoxel(2.2f, 1.3f, 0.0f, 2.0f, 0.4f, 1.4f, 0.4f, 0.9f, 0.0f, false);
    
    // Taring Bawah
    drawVoxel(2.9f, 1.5f, 0.6f, 0.15f, 0.3f, 0.15f, 0.9f, 0.9f, 0.9f); // Kanan
    drawVoxel(2.9f, 1.5f, -0.6f, 0.15f, 0.3f, 0.15f, 0.9f, 0.9f, 0.9f); // Kiri
    glPopMatrix();
    
    glPopMatrix();

    // Ekor
    drawVoxel(-2.0f, -0.2f, 0.0f, 1.6f, 0.8f, 1.2f, 0.3f, 0.7f, 0.0f);

    float posX[4] = {-0.9f, -0.9f, 1.0f, 1.0f};
    float posZ[4] = {0.7f, -0.7f, 0.7f, -0.7f};
    
    for(int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(posX[i], -0.8f, posZ[i]); 
        float ayun;
        if (i == 0 || i == 3) ayun = sin(stepAngle * 2.0f) * 20.0f; 
        else ayun = -sin(stepAngle * 2.0f) * 20.0f;
        glRotatef(ayun, 0, 0, 1);
        drawVoxel(0, -0.5f, 0, 0.8f, 1.0f, 0.8f, 0.4f, 0.9f, 0.0f); // Kaki
        drawVoxel(0, -1.2f, 0, 0.9f, 0.4f, 0.9f, 0.25f, 0.25f, 0.25f); // Sepatu
        glPopMatrix();
    }
    glPopMatrix();
}

void drawQuetzalcoatlus(float wingAngle, bool isTalking = false) {
    glPushMatrix();
    glTranslatef(0.0f, sin(wingAngle * 0.5f) * 0.5f, 0.0f); // Bobbing naik turun

    // 1. TUBUH UTAMA (Oranye)
    drawVoxel(0.0f, 0.0f, 0.0f, 2.5f, 1.2f, 1.2f, 1.0f, 0.5f, 0.0f);

    // 2. LEHER SANGAT PANJANG
    drawVoxel(1.2f, 0.6f, 0.0f, 0.8f, 1.2f, 0.8f, 1.0f, 0.5f, 0.0f);
    drawVoxel(1.8f, 1.5f, 0.0f, 0.7f, 1.5f, 0.7f, 1.0f, 0.5f, 0.0f);
    drawVoxel(2.4f, 2.8f, 0.0f, 0.6f, 1.8f, 0.6f, 1.0f, 0.5f, 0.0f);

    // KEPALA
    glPushMatrix();
    float jawAngle = 0.0f;
    if (isTalking) {
        float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        jawAngle = (sin(time * 15.0f) * 0.5f + 0.5f) * -20.0f;
    }

    drawVoxel(2.8f, 3.8f, 0.0f, 1.2f, 1.0f, 0.8f, 1.0f, 0.5f, 0.0f, true); // Kepala
    drawVoxel(4.5f, 3.7f, 0.0f, 3.5f, 0.4f, 0.6f, 1.0f, 0.8f, 0.0f);       // Paruh atas

    // Rahang bawah
    glPushMatrix();
    glTranslatef(2.8f, 3.5f, 0.0f); 
    glRotatef(jawAngle, 0, 0, 1);
    glTranslatef(-2.8f, -3.5f, 0.0f);
    drawVoxel(4.2f, 3.4f, 0.0f, 3.0f, 0.3f, 0.5f, 1.0f, 0.8f, 0.0f); // Paruh bawah
    glPopMatrix();
    
    // Jambul belakang
    drawVoxel(2.0f, 4.4f, 0.0f, 0.4f, 1.2f, 0.4f, 1.0f, 0.7f, 0.0f);
    
    glPopMatrix(); // End Kepala

    // 4. EKOR
    drawVoxel(-1.8f, 0.0f, 0.0f, 1.2f, 0.4f, 0.6f, 1.0f, 0.5f, 0.0f);

    // 5. SAYAP
    float flap = sin(wingAngle) * 30.0f;
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.6f);
    glRotatef(flap, 1, 0, 0);
    drawVoxel(0.0f, 0.0f, 2.0f, 2.0f, 0.2f, 4.0f, 1.0f, 0.6f, 0.1f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.2f, -0.6f);
    glRotatef(-flap, 1, 0, 0);
    drawVoxel(0.0f, 0.0f, -2.0f, 2.0f, 0.2f, 4.0f, 1.0f, 0.6f, 0.1f);
    glPopMatrix();

    glPopMatrix();
}

void drawTriceratops(float stepAngle, bool isTalking = false) {
    glPushMatrix();
    float bobbing = fabs(sin(stepAngle)) * 0.12f;
    glTranslatef(0.0f, bobbing, 0.0f);
    // Tubuh Utama
    drawVoxel(0.0f, 0.0f, 0.0f, 3.5f, 2.0f, 2.0f, 0.8f, 0.1f, 0.1f);
    // Leher
    drawVoxel(1.8f, 0.5f, 0.0f, 1.0f, 1.2f, 1.5f, 0.8f, 0.1f, 0.1f);
    
    // Kepala
    glPushMatrix();
    glRotatef(sin(stepAngle) * 2.0f, 0, 0, 1);
    
    float jawAngle = 0.0f;
    if (isTalking) {
        float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        jawAngle = (sin(time * 15.0f) * 0.5f + 0.5f) * -20.0f; // Mulut terbuka ke bawah
    }
    
    drawVoxel(2.3f, 1.5f, 0.0f, 0.3f, 2.5f, 2.5f, 0.85f, 0.3f, 0.0f); // Rumbat
    
    // Rahang Atas
    drawVoxel(2.7f, 1.0f, 0.0f, 1.5f, 1.0f, 1.4f, 0.8f, 0.1f, 0.1f, true); // Wajah
    drawVoxel(3.2f, 0.6f, 0.0f, 1.0f, 0.6f, 1.0f, 0.8f, 0.1f, 0.1f); // Moncong
    drawVoxel(2.9f, 1.6f, 0.4f, 0.3f, 0.8f, 0.3f, 0.9f, 0.8f, 0.6f); // Cula
    drawVoxel(2.9f, 1.6f, -0.4f, 0.3f, 0.8f, 0.3f, 0.9f, 0.8f, 0.6f);
    drawVoxel(3.5f, 1.0f, 0.0f, 0.3f, 0.5f, 0.3f, 0.9f, 0.8f, 0.6f);
    
    // Rahang Bawah
    glPushMatrix();
    glTranslatef(1.95f, 0.6f, 0.0f); // Titik putar rahang bawah
    glRotatef(jawAngle, 0, 0, 1);
    glTranslatef(-1.95f, -0.6f, 0.0f);
    drawVoxel(2.7f, 0.3f, 0.0f, 1.3f, 0.4f, 1.2f, 0.8f, 0.1f, 0.1f); // Wajah bawah
    drawVoxel(3.2f, 0.15f, 0.0f, 0.8f, 0.3f, 0.8f, 0.8f, 0.1f, 0.1f); // Moncong bawah
    glPopMatrix();
    
    glPopMatrix();
    
    // Ekor
    glPushMatrix();
    glTranslatef(-1.75f, 0.2f, 0.0f);
    glRotatef(sin(stepAngle * 0.5f) * 5.0f, 0, 1, 0);
    drawVoxel(-0.75f, 0.0f, 0.0f, 2.5f, 0.8f, 1.0f, 0.8f, 0.1f, 0.1f);
    glPopMatrix();
    
    // Kaki
    float legX[4] = {-1.0f, -1.0f, 1.2f, 1.2f};
    float legZ[4] = {0.7f, -0.7f, 0.7f, -0.7f};
    for(int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(legX[i], -0.6f, legZ[i]); 
        float ayun;
        if (i == 0 || i == 3) ayun = sin(stepAngle * 1.5f) * 20.0f;
        else ayun = -sin(stepAngle * 1.5f) * 20.0f;
        glRotatef(ayun, 0, 0, 1);
        drawVoxel(0, -0.6f, 0, 0.8f, 1.2f, 0.8f, 0.8f, 0.1f, 0.1f);
        drawVoxel(0, -1.2f, 0, 0.9f, 0.4f, 0.9f, 0.3f, 0.3f, 0.3f);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawText2D(const char* text, float x, float y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluOrtho2D(0, w, 0, h);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // Calculate text width
    int textLen = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        textLen += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    
    // Background for text
    glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x + textLen + 10, y - 10);
    glVertex2f(x + textLen + 10, y + 25);
    glVertex2f(x - 10, y + 25);
    glEnd();
    glDisable(GL_BLEND);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    float trexX = -20.0f, trexZ = 0.0f;
    float triceX = 25.0f, triceZ = 0.0f;
    float triceRotY = 180.0f; // Menghadap ke T-Rex secara default
    float quetzalX = 50.0f, quetzalY = 20.0f;
    float storeX = 0.0f, storeY = 0.0f, storeZ = 0.0f;
    float storeCT = 0.0f;
    float stepAngleTRex = 0.0f;
    float stepAngleTricera = 0.0f;
    float wingAngle = t * 15.0f;

    // Time-based State Machine for Scene 3 Animation (60 seconds)
    if (t < 12.0f) {
        // Scene 1: T-Rex berjalan mencari makanan
        trexX = -20.0f + (t / 12.0f) * 16.0f; 
        stepAngleTRex = t * 8.0f;
    } else if (t < 25.0f) {
        // Scene 2: Kekacauan di Food Store
        trexX = -4.0f;
        storeCT = t - 12.0f;
        stepAngleTRex = 0.0f; 
    } else if (t < 42.0f) {
        // Scene 3A: Triceratops merasakan goncangan, lalu Quetzalcoatlus datang
        trexX = -4.0f;
        storeCT = 13.0f; 
        triceX = 25.0f; // Diam di tempat
        triceRotY = 0.0f; // Menghadap Quetzalcoatlus (+X)
        stepAngleTricera = 0.0f;
        
        float flyT = t - 25.0f;
        quetzalX = 50.0f - flyT * 4.0f; 
        quetzalY = 15.0f - flyT * 2.5f; 
        if (quetzalY < 2.5f) quetzalY = 2.5f; // Terbang sejajar Triceratops
        if (quetzalX < 33.0f) quetzalX = 33.0f; // Berhenti sedikit lebih jauh agar sayap tidak menembus
    } else if (t < 48.0f) {
        // Scene 3B: Triceratops berbalik dan berlari kencang
        trexX = -4.0f;
        storeCT = 13.0f; 
        float runT = t - 42.0f; // Waktu berlari (6 detik)
        if (runT < 0.5f) {
            triceRotY = 0.0f + runT * 2.0f * 180.0f; // Berputar 180 derajat dalam 0.5 detik
            triceX = 25.0f; 
            stepAngleTricera = 0.0f;
        } else {
            triceRotY = 180.0f;
            float moveT = runT - 0.5f;
            triceX = 25.0f - (moveT / 5.5f) * 17.0f; // Lari 17 unit dalam 5.5 detik
            stepAngleTricera = moveT * 25.0f; // Animasi kaki sangat cepat
        }
        quetzalX = 29.0f + runT * 8.0f; // Quetzal kabur lebih cepat
        quetzalY = 2.5f + runT * 6.0f;
    } else {
        // Scene 4: Percakapan
        trexX = -4.0f;
        storeCT = 13.0f;
        triceX = 8.0f;
        triceRotY = 180.0f;
    }

    // Camera State Machine
    float camX, camY, camZ;
    float lookX, lookY, lookZ;
    
    if (t < 6.0f) {
        camX = trexX - 4.0f; camY = 1.0f; camZ = trexZ + 4.0f;
        lookX = trexX; lookY = 1.0f; lookZ = trexZ;
    } else if (t < 12.0f) {
        camX = trexX + 8.0f; camY = 1.0f; camZ = trexZ + 6.0f;
        lookX = trexX; lookY = 3.0f; lookZ = trexZ;
    } else if (t < 15.0f) {
        camX = -10.0f; camY = 8.0f; camZ = 15.0f;
        lookX = 0.0f; lookY = 2.0f; lookZ = 0.0f;
    } else if (t < 18.0f) {
        camX = trexX + 2.0f; camY = 5.0f; camZ = trexZ + 5.0f;
        lookX = trexX + 2.0f; lookY = 4.0f; lookZ = trexZ;
    } else if (t < 21.0f) {
        camX = 10.0f; camY = 6.0f; camZ = 12.0f;
        lookX = -2.0f; lookY = 1.0f; lookZ = 0.0f;
    } else if (t < 25.0f) {
        camX = 0.0f; camY = 3.0f; camZ = 8.0f;
        lookX = 0.0f; lookY = 0.0f; lookZ = 0.0f;
    } else if (t < 42.0f) {
        // Komunikasi Triceratops & Quetzalcoatlus
        camX = triceX + 12.0f; camY = 5.0f; camZ = triceZ + 18.0f;
        lookX = triceX + 4.0f; lookY = 3.0f; lookZ = triceZ;
    } else if (t < 48.0f) {
        // Triceratops berlari dari Samping (Lebih cepat)
        camX = triceX + 2.0f; camY = 3.0f; camZ = triceZ + 12.0f;
        lookX = triceX; lookY = 2.0f; lookZ = triceZ;
    } else if (t < 54.0f) {
        // Over-the-shoulder POV Triceratops
        camX = triceX + 3.0f; camY = 3.0f; camZ = triceZ + 4.0f;
        lookX = trexX; lookY = 3.0f; lookZ = trexZ;
    } else if (t < 60.0f) {
        // Over-the-shoulder POV T-Rex
        camX = trexX - 4.0f; camY = 5.0f; camZ = trexZ + 5.0f;
        lookX = triceX; lookY = 2.0f; lookZ = triceZ;
    } else {
        camX = 2.0f; camY = 8.0f; camZ = 20.0f;
        lookX = 2.0f; lookY = 2.0f; lookZ = 0.0f;
    }

    // Shake effect (goncangan) saat T-Rex mendekati FoodStore (Kuat)
    if (t < 12.0f) {
        float intensity = 0.15f * (t / 12.0f); // Semakin dekat, semakin kuat goncangannya
        camX += ((rand() % 100) / 100.0f - 0.5f) * intensity;
        camY += ((rand() % 100) / 100.0f - 0.5f) * intensity;
        camZ += ((rand() % 100) / 100.0f - 0.5f) * intensity;
    }
    // Goncangan lemah saat Triceratops kebingungan (jauh dari tempat kejadian)
    else if (t >= 25.0f && t < 30.0f) {
        float intensity = 0.02f; // Lemah
        camX += ((rand() % 100) / 100.0f - 0.5f) * intensity;
        camY += ((rand() % 100) / 100.0f - 0.5f) * intensity;
        camZ += ((rand() % 100) / 100.0f - 0.5f) * intensity;
    }

    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0f, 1.0f, 0.0f);

    // RENDER GROUND
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glColor3f(0.45f, 0.63f, 0.28f);
    glVertex3f(-70.0f, 0.0f, -70.0f);
    glVertex3f(70.0f, 0.0f, -70.0f);
    glVertex3f(70.0f, 0.0f, 70.0f);
    glVertex3f(-70.0f, 0.0f, 70.0f);
    glEnd();
    glEnable(GL_LIGHTING);

    // RENDER LINGKUNGAN (Pohon, Batu, Awan)
    drawPohon(-15.0f, -15.0f);
    drawPohon(15.0f, -10.0f);
    drawPohon(-16.0f, 18.0f); 
    drawPohon(20.0f, 18.0f);  
    drawPohon(-25.0f, -5.0f);
    drawPohon(22.0f, -20.0f);
    // Tambahan objek agar lingkungan lebih hidup dan luas
    drawPohon(-35.0f, 10.0f);
    drawPohon(-30.0f, -25.0f);
    drawPohon(35.0f, 5.0f);
    drawPohon(40.0f, -15.0f);
    drawPohon(0.0f, -25.0f);
    drawPohon(-10.0f, -30.0f);

    drawBatu(-12.0f, 0.0f, 12.0f, 1.5f);
    drawBatu(18.0f, 0.0f, 8.0f, 1.0f);
    drawBatu(-20.0f, 0.0f, -12.0f, 2.0f);
    drawBatu(30.0f, 0.0f, -5.0f, 1.2f);
    drawBatu(-35.0f, 0.0f, -15.0f, 2.5f);

    // Langit (Awan)
    drawAwan(-20.0f, 20.0f, -30.0f, 2.0f);
    drawAwan(15.0f, 25.0f, -40.0f, 3.0f);
    drawAwan(40.0f, 18.0f, -20.0f, 2.5f);
    drawAwan(-40.0f, 22.0f, -10.0f, 2.8f);

    // RENDER FOOD STORE
    glPushMatrix();
    glTranslatef(storeX, storeY, storeZ);
    drawStore(storeCT);
    glPopMatrix();

    // RENDER FLYING FRUITS (Efek Kekacauan)
    if (t >= 12.0f) {
        float flyTime = t - 12.0f;
        float ft = (flyTime > 1.2f) ? 1.2f : flyTime; // berhenti setelah jatuh ke tanah
        
        // Buah 1 (Merah) - Kiri Depan
        glPushMatrix();
        glTranslatef(storeX - 3.0f - ft * 3.0f, storeY + 4.0f - ft * ft * 2.5f, storeZ + ft * 3.0f);
        glRotatef(ft * 400.0f, 1, 1, 0);
        drawFruitPile(0, 0, 0, 0.9f, 0.2f, 0.1f);
        glPopMatrix();
        
        // Buah 2 (Kuning/Oranye) - Kanan Depan
        glPushMatrix();
        glTranslatef(storeX + 2.0f + ft * 2.5f, storeY + 3.0f - ft * ft * 2.0f, storeZ + ft * 2.5f);
        glRotatef(ft * 300.0f, 0, 1, 1);
        drawFruitPile(0, 0, 0, 0.95f, 0.7f, 0.12f);
        glPopMatrix();

        // Buah 3 (Hijau) - Kiri Jauh
        glPushMatrix();
        glTranslatef(storeX - 1.0f - ft * 4.0f, storeY + 2.0f - ft * ft * 1.2f, storeZ + ft * 4.0f);
        glRotatef(ft * 500.0f, 1, 0, 1);
        drawFruitPile(0, 0, 0, 0.2f, 0.8f, 0.2f);
        glPopMatrix();

        // Buah 4 (Merah Kuning) - Tengah Depan
        glPushMatrix();
        glTranslatef(storeX + ft * 1.0f, storeY + 3.5f - ft * ft * 2.2f, storeZ + ft * 5.0f);
        glRotatef(ft * 250.0f, 1, 1, 1);
        drawFruitPile(0, 0, 0, 1.0f, 0.5f, 0.1f);
        glPopMatrix();

        // Buah 5 (Kuning Cerah) - Kanan Jauh
        glPushMatrix();
        glTranslatef(storeX + 1.0f + ft * 5.0f, storeY + 4.0f - ft * ft * 2.6f, storeZ + ft * 3.5f);
        glRotatef(ft * 450.0f, 0, 1, 0);
        drawFruitPile(0, 0, 0, 0.9f, 0.9f, 0.1f);
        glPopMatrix();
    }

    bool triceTalking = (t >= 26.0f && t < 31.0f) || (t >= 38.0f && t < 41.0f) || (t >= 48.0f && t < 54.0f);
    bool quetzalTalking = (t >= 34.0f && t < 38.0f);
    bool tRexTalking = (t >= 54.0f && t < 60.0f);

    // RENDER T-REX
    glPushMatrix();
    glTranslatef(trexX, 2.0f, trexZ);
    drawTRex(stepAngleTRex, tRexTalking);
    glPopMatrix();

    // RENDER TRICERATOPS
    if (t > 20.0f) {
        glPushMatrix();
        glTranslatef(triceX, 2.0f, triceZ);
        glRotatef(triceRotY, 0.0f, 1.0f, 0.0f); // Menghadap dinamis
        drawTriceratops(stepAngleTricera, triceTalking);
        glPopMatrix();
    }
    
    // RENDER QUETZALCOATLUS
    if (t >= 25.0f && t < 48.0f) {
        glPushMatrix();
        glTranslatef(quetzalX, quetzalY, triceZ + 1.0f); // Sejajarkan sumbu Z
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // Menghadap ke Triceratops (-X)
        drawQuetzalcoatlus(wingAngle, quetzalTalking);
        glPopMatrix();
    }

    // DIALOGUE TEXT
    if (t >= 26.0f && t < 31.0f) {
        drawText2D("Triceratops: Eh, goncangan apa ini? Tanah terasa bergetar...", 50, 50);
    } else if (t >= 34.0f && t < 38.0f) {
        drawText2D("Quetzalcoatlus: Gawat! T-Rex sedang menghancurkan Food Store di sana!", 50, 50);
    } else if (t >= 38.0f && t < 41.0f) {
        drawText2D("Triceratops: Apa?! Aku harus segera menghentikannya!", 50, 50);
    } else if (t >= 48.0f && t < 54.0f) {
        drawText2D("Triceratops: Berhenti! Kamu membuat kekacauan!", 50, 50);
    } else if (t >= 54.0f && t < 60.0f) {
        drawText2D("T-Rex: Aku hanya lapar!", 50, 50);
    }

    glutSwapBuffers();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    // Sky Blue Background
    glClearColor(0.4f, 0.7f, 1.0f, 1.0f); 

    GLfloat light_pos[] = { 15.0f, 25.0f, 10.0f, 1.0f };
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
    glutCreateWindow("Scene 3: Kekacauan di Food Store");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0); 
    
    glutMainLoop();
    
    return 0;
}


