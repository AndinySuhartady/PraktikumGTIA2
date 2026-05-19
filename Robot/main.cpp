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

#include <stdlib.h>

#include <GL/glut.h>

static int shoulder = 0;
static int elbow = 0;
static int palm = 0;
static int finger = 0;

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // ===== SHOULDER =====
    glTranslatef(-1.0,0.0,0.0);
    glRotatef((GLfloat)shoulder,0.0,0.0,1.0);
    glTranslatef(1.0,0.0,0.0);

    glPushMatrix();
    glScalef(2.0,0.4,1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // ===== ELBOW =====
    glTranslatef(1.0,0.0,0.0);
    glRotatef((GLfloat)elbow,0.0,0.0,1.0);
    glTranslatef(1.0,0.0,0.0);

    glPushMatrix();
    glScalef(2.0,0.4,1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // ===== PALM =====
    glTranslatef(1.0,0.0,0.0);
    glRotatef((GLfloat)palm,0.0,0.0,1.0);

    glPushMatrix();
    glScalef(0.6,0.3,0.8);
    glutWireCube(1.0);
    glPopMatrix();

    // ===== FINGER =====
    glTranslatef(0.4,0.0,0.0);
    glRotatef((GLfloat)finger,0.0,0.0,1.0);

    glPushMatrix();
    glScalef(0.8,0.2,0.2);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(65.0,(GLfloat)w/(GLfloat)h,1.0,20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-5.0);
}

void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 's':
            shoulder=(shoulder+5)%360;
            break;

        case 'S':
            shoulder=(shoulder-5)%360;
            break;

        case 'e':
            elbow=(elbow+5)%360;
            break;

        case 'E':
            elbow=(elbow-5)%360;
            break;

        case 'p':
            palm=(palm+5)%360;
            break;

        case 'P':
            palm=(palm-5)%360;
            break;

        case 'f':
            finger=(finger+5)%360;
            break;

        case 'F':
            finger=(finger-5)%360;
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

    glutInitWindowSize(700,600);
    glutCreateWindow("Robot Arm With Hand");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
