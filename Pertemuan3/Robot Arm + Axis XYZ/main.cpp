

#include <GL/glut.h>
#include <stdlib.h>

// ================= VARIABEL =================
static int shoulder = 0;
static int elbow = 0;
static int finger1 = 0; 
static int finger2 = 0; 
static int wrist = 0; 

static int offset1[5] = {0,0,0,0,0};
static int offset2[5] = {0,0,0,0,0};

// ================= INIT =================
void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

// ================= DISPLAY =================
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // ===== AXIS XYZ (HARUS DI DALAM DISPLAY!) =====
    glBegin(GL_LINES);

    // X (MERAH)
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(3,0,0);

    // Y (HIJAU)
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,3,0);

    // Z (BIRU)
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,3);

    glEnd();

    glColor3f(1,1,1); // balik warna objek

    // ====== SHOULDER ======
    glTranslatef(-1.0,0.0,0.0);
    glRotatef((GLfloat)shoulder,0.0,0.0,1.0);

    // lengan atas
    glPushMatrix();
        glTranslatef(1.0,0.0,0.0);
        glScalef(2.0,0.4,1.0);
        glutWireCube(1.0);
    glPopMatrix();

    // ====== ELBOW ======
    glTranslatef(2.0,0.0,0.0);
    glRotatef((GLfloat)elbow,0.0,0.0,1.0);

    // lengan bawah
    glPushMatrix();
        glTranslatef(1.0,0.0,0.0);
        glScalef(2.0,0.4,1.0);
        glutWireCube(1.0);
    glPopMatrix();

    // ====== TELAPAK ======
    glTranslatef(2.0,0.0,0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);

    glPushMatrix();
        glScalef(0.6,0.5,1.2);
        glutWireCube(1.0);
    glPopMatrix();

    // ================= JARI =================
    float z_pos[] = {0.3, 0.1, -0.1, -0.3};

    // ===== 4 JARI =====
    for(int i = 0; i < 4; i++) {
        glPushMatrix();

        glTranslatef(0.3, 0.0, z_pos[i]);

        // ruas 1 
        glRotatef((GLfloat)(finger1 + offset1[i] + i*5), 0,0,1);

        glPushMatrix();
            glTranslatef(0.25,0,0);
            glScalef(0.5,0.12,0.12);
            glutWireCube(1.0);
        glPopMatrix();

        // ruas 2 
        glTranslatef(0.5,0,0);
        glRotatef((GLfloat)(finger2 + offset2[i] + i*3), 0,0,1);

        glPushMatrix();
            glTranslatef(0.2,0,0);
            glScalef(0.4,0.1,0.1);
            glutWireCube(1.0);
        glPopMatrix();

        glPopMatrix();
    }

    // ===== JEMPOL =====
    glPushMatrix();

        glTranslatef(0.1, -0.2, -0.4);

        glRotatef(-40, 0,0,1);
        glRotatef(20, 1,0,0);

        // ruas 1
        glRotatef((GLfloat)(finger1 + offset1[4]), 0,0,1);

        glPushMatrix();
            glTranslatef(0.2,0,0);
            glScalef(0.4,0.12,0.12);
            glutWireCube(1.0);
        glPopMatrix();

        // ruas 2
        glTranslatef(0.4,0,0);
        glRotatef((GLfloat)(finger2 + offset2[4]), 0,0,1);

        glPushMatrix();
            glTranslatef(0.15,0,0);
            glScalef(0.3,0.1,0.1);
            glutWireCube(1.0);
        glPopMatrix();

    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

// ================= RESHAPE =================
void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0,(GLfloat)w/(GLfloat)h,1.0,20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-6.0);
}

// ================= KEYBOARD =================
void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 's': shoulder += 5; break;
        case 'S': shoulder -= 5; break;

        case 'e': elbow += 5; break;
        case 'E': elbow -= 5; break;

        case 'q': finger1 += 5; break;
        case 'Q': finger1 -= 5; break;

        case 'w': finger2 += 5; break;
        case 'W': finger2 -= 5; break;

        case 'a': wrist += 5; break;
        case 'A': wrist -= 5; break;

        // ruas 1
        case '1': offset1[0]+=5; break;
        case '2': offset1[1]+=5; break;
        case '3': offset1[2]+=5; break;
        case '4': offset1[3]+=5; break;
        case '5': offset1[4]+=5; break;

        // ruas 2
        case 'z': offset2[0]+=5; break;
        case 'x': offset2[1]+=5; break;
        case 'c': offset2[2]+=5; break;
        case 'v': offset2[3]+=5; break;
        case 'b': offset2[4]+=5; break;

        case 'r':
            for(int i=0;i<5;i++){
                offset1[i]=0;
                offset2[i]=0;
            }
            break;

        case 27: exit(0);
    }

    glutPostRedisplay();
}

// ================= MAIN =================
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(700,600);
    glutInitWindowPosition(100,100);

    glutCreateWindow("Robot Arm + Axis XYZ");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
