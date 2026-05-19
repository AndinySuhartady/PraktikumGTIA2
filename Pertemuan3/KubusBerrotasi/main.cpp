

#include <GL/glut.h>

#include <stdlib.h>
#include <GL/glut.h>

GLfloat xRotated = 0.0;
GLfloat yRotated = 0.0;
GLfloat zRotated = 0.0;

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // memindahkan objek menjauh dari kamera
    glTranslatef(0.0,0.0,-4.0);

    // rotasi
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);

    // scaling
    glScalef(2.0,1.0,1.0);

    // gambar kubus
    glutWireCube(1.0);

    glutSwapBuffers();
}

void Reshape(int x, int y)
{
    if (x == 0 || y == 0) return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

void Idle(void)
{
    xRotated += 0.3;
    yRotated += 0.1;
    zRotated -= 0.4;

    glutPostRedisplay();   // update frame
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(300,300);
    glutCreateWindow("Cube Example");

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glClearColor(0.0,0.0,0.0,0.0);

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(Idle);

    glutMainLoop();

    return 0;
}
