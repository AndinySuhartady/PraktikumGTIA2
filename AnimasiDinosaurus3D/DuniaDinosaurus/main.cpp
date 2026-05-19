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

// ================= VOXEL =================
void drawVoxel(float x,float y,float z,
               float sx,float sy,float sz,
               float r,float g,float b,
               bool eye=false)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(sx,sy,sz);

    glColor3f(r,g,b);
    glutSolidCube(1.0);

    if(eye){
        glDisable(GL_LIGHTING);
        glColor3f(0,0,0);
        glPushMatrix();
        glTranslatef(0.3f,0.2f,0.51f);
        glScalef(0.2f,0.2f,0.05f);
        glutSolidCube(1);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }

    glPopMatrix();
}

// ================= DINO HIJAU =================
void dinoHijau(){
    glPushMatrix();
    glTranslatef(-6,1.2f,0); // naikkan ke atas tanah

    float bob = fabs(sin(stepAngle))*0.15;
    glTranslatef(0,bob,0);

    drawVoxel(0,0,0,3,1.6,1.8,0.4,0.9,0);
    drawVoxel(1.4,0.9,0,1,1,1.2,0.4,0.9,0);
    drawVoxel(2.2,1.8,0,2.2,1.4,1.6,0.4,0.9,0,true);
    drawVoxel(-2,-0.2,0,1.6,0.8,1.2,0.3,0.7,0);

    float x[4]={-0.9,-0.9,1,1};
    float z[4]={0.7,-0.7,0.7,-0.7};

    for(int i=0;i<4;i++){
        glPushMatrix();
        glTranslatef(x[i], 0.0f, z[i]);

        float ayun=(i==0||i==3)?sin(stepAngle*2)*20:-sin(stepAngle*2)*20;
        glRotatef(ayun,0,0,1);

        drawVoxel(0,-0.5,0,0.8,1,0.8,0.4,0.9,0);
        drawVoxel(0,-1.2,0,0.9,0.4,0.9,0.3,0.3,0.3);
        glPopMatrix();
    }

    glPopMatrix();
}

// ================= TRICERATOPS (UPGRADE) =================
void triceratops(){
    glPushMatrix();
    glTranslatef(6,1.2f,0); // biar napak tanah

    float bob = fabs(sin(stepAngle))*0.12;
    glTranslatef(0,bob,0);

    // tubuh
    drawVoxel(0,0,0,3.5,2,2,0.8,0.1,0.1);
    drawVoxel(1.8,0.5,0,1,1.2,1.5,0.8,0.1,0.1);

    // kepala (ikut gerak)
    glPushMatrix();
    glRotatef(sin(stepAngle)*2,0,0,1);

    drawVoxel(2.3,1.5,0,0.3,2.5,2.5,0.85,0.3,0);
    drawVoxel(2.7,0.8,0,1.5,1.4,1.4,0.8,0.1,0.1,true);
    drawVoxel(3.2,0.4,0,1,1,1,0.8,0.1,0.1);

    // tanduk
    drawVoxel(2.9,1.6,0.4,0.3,0.8,0.3,0.9,0.8,0.6);
    drawVoxel(2.9,1.6,-0.4,0.3,0.8,0.3,0.9,0.8,0.6);
    drawVoxel(3.5,1.0,0,0.3,0.5,0.3,0.9,0.8,0.6);

    glPopMatrix();

    // EKOR (baru)
    glPushMatrix();
    glTranslatef(-1.8,0.2,0);
    glRotatef(sin(stepAngle*0.5)*5,0,1,0);
    drawVoxel(-0.8,0,0,2.5,0.8,1,0.8,0.1,0.1);
    glPopMatrix();

    // kaki
    float x[4]={-1,-1,1.2,1.2};
    float z[4]={0.7,-0.7,0.7,-0.7};

    for(int i=0;i<4;i++){
        glPushMatrix();
        glTranslatef(x[i], 0.0f, z[i]);

        float ayun=(i==0||i==3)?sin(stepAngle*1.5)*20:-sin(stepAngle*1.5)*20;
        glRotatef(ayun,0,0,1);

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

    gluLookAt(15,10,15, 0,0,0, 0,1,0);

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
	dinoHijau();
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

    glutSwapBuffers();
}

// ================= TIMER =================
void timer(int v){
    stepAngle += 0.08f;
    wingAngle += 0.12f;

    glutPostRedisplay();
    glutTimerFunc(16,timer,0);
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
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1024,768);
    glutCreateWindow("Dunia DinosaurusLengkap FINAL");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);

    glutMainLoop();
    return 0;
}






