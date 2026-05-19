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
#include <GL/glut.h>
#include <cmath>

float t = 0.0f;
float camAngle = 0.0f;
float camDist = 25.0f;

bool walking = true;

void drawGround()
{
    glDisable(GL_LIGHTING);

    glColor3f(0.25f,0.55f,0.2f);

    glBegin(GL_QUADS);
    glVertex3f(-50,-2,-50);
    glVertex3f(50,-2,-50);
    glVertex3f(50,-2,50);
    glVertex3f(-50,-2,50);
    glEnd();

    glEnable(GL_LIGHTING);
}

void drawBody()
{
    glPushMatrix();

    glScalef(4.5,2.0,2.2);
    glutSolidSphere(1.0,40,40);

    glPopMatrix();
}

void drawTail()
{
    int seg=18;

    for(int i=0;i<seg;i++)
    {
        float k=(float)i/seg;

        glPushMatrix();

        glTranslatef(-4.0 - i*0.6,0,0);

        glRotatef(sin(t*2+i)*15,0,1,0);

        float r=0.9*(1-k);

        glScalef(r,r,r);

        glutSolidSphere(1.0,24,24);

        glPopMatrix();
    }
}

void drawNeck()
{
    int seg=16;

    for(int i=0;i<seg;i++)
    {
        float k=(float)i/seg;

        glPushMatrix();

        glTranslatef(3.0+i*0.55,1.0+i*0.35,0);

        glRotatef(15+sin(t*2+i)*6,0,0,1);

        float r=0.8*(1-k*0.3);

        glScalef(r,r,r);

        glutSolidSphere(1.0,24,24);

        glPopMatrix();
    }

    glPushMatrix();

    glTranslatef(3.0+seg*0.55,1.0+seg*0.35,0);

    glScalef(0.9,0.8,0.8);

    glutSolidSphere(1.0,30,30);

    glPopMatrix();
}

void drawLeg(float x,float z,bool front)
{
    glPushMatrix();

    glTranslatef(x,-1.6,z);

    float walk=walking?sin(t*3+(front?0:3))*20:0;

    glRotatef(walk,0,0,1);

    glPushMatrix();
    glTranslatef(0,1.0,0);
    glScalef(0.7,2.0,0.7);
    glutSolidSphere(1,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.2,0);
    glScalef(0.5,0.4,0.5);
    glutSolidSphere(1,20,20);
    glPopMatrix();

    glPopMatrix();
}

void drawTree()
{
    glColor3f(0.4,0.25,0.1);

    glPushMatrix();
    glTranslatef(8,0,8);
    glScalef(0.5,5,0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.1,0.6,0.2);

    glPushMatrix();
    glTranslatef(8,4,8);
    glutSolidSphere(2.5,30,30);
    glPopMatrix();
}

void drawBarosaurus()
{
    glColor3f(0.45,0.35,0.25);

    drawBody();
    drawTail();
    drawNeck();

    drawLeg(2.0,1.0,true);
    drawLeg(2.0,-1.0,true);

    drawLeg(-2.2,1.0,false);
    drawLeg(-2.2,-1.0,false);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    float camX=sin(camAngle)*camDist;
    float camZ=cos(camAngle)*camDist;

    gluLookAt(camX,7,camZ,0,0,0,0,1,0);

    drawGround();

    drawTree();

    glPushMatrix();

    if(walking)
    {
        glTranslatef(sin(t*0.5)*4,0,cos(t*0.5)*2);
        glRotatef(sin(t*0.3)*10,0,1,0);
    }

    drawBarosaurus();

    glPopMatrix();

    glutSwapBuffers();

    t+=0.02;
    camAngle+=0.002;
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60,(float)w/h,1,200);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key,int x,int y)
{
    if(key==' ')
        walking=!walking;

    if(key==27)
        exit(0);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);

    GLfloat pos[]={10,20,10,1};

    glLightfv(GL_LIGHT0,GL_POSITION,pos);

    glClearColor(0.55,0.75,0.95,1);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(1200,800);

    glutCreateWindow("Barosaurus 3D Animation");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
