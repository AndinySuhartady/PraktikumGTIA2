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

// Ukuran foto
float m = 100.0f;
float n = 100.0f;

// Ukuran layar
int u = 800;
int v = 600;

float offset = 0.0f;

// Transformasi koordinat X
float transformX(float x_foto){
    return x_foto * (u / m);
}

// Transformasi koordinat Y
float transformY(float y_foto){
    return v - (y_foto * (v / n));
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // Persegi panjang warna pink
    glColor3f(1.0f, 0.75f, 0.80f);
    glBegin(GL_QUADS);
        glVertex2f(transformX(5+offset), transformY(0));
        glVertex2f(transformX(10+offset), transformY(0));
        glVertex2f(transformX(10+offset), transformY(15));
        glVertex2f(transformX(5+offset), transformY(15));
    glEnd();

    // Garis warna pink
    glColor3f(1.0f, 0.75f, 0.80f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(transformX(20), transformY(0));
        glVertex2f(transformX(20), transformY(20));
    glEnd();

    glFlush();
}

// fungsi animasi
void update(){
    offset += 0.05f;

    if(offset > 20)
        offset = 0;

    glutPostRedisplay();
}

void init(){
    glClearColor(0.1f,0.1f,0.2f,1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,u,v,0);
}

int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(u,v);
    glutCreateWindow("Animasi Transformasi Koordinat");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(update);

    glutMainLoop();

    return 0;
}
