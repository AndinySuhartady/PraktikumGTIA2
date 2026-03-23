

#include <GL/glut.h>

#include <stdlib.h>


void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_POLYGON);

        glColor3f(0.0,0.0,0.0);
        glVertex3f(-0.5,-0.5,-3.0);

        glColor3f(1.0,0.0,0.0);
        glVertex3f(0.5,-0.5,-3.0);

        glColor3f(0.0,0.0,1.0);
        glVertex3f(0.5,0.5,-3.0);

    glEnd();

    glFlush(); // selesai rendering
}

void Reshape(int x, int y)
{
    if (y == 0 || x == 0) return;

    // Mengatur proyeksi
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // sudut 40, near 0.5, far 20
    gluPerspective(40.0, (GLdouble)x/(GLdouble)y, 0.5, 20.0);

    glMatrixMode(GL_MODELVIEW);

    // gunakan seluruh window
    glViewport(0,0,x,y);
}

int main(int argc, char **argv)
{
    // inisialisasi GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300,300);

    glutCreateWindow("Intro OpenGL");

    // warna background
    glClearColor(0.0,0.0,0.0,0.0);

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);

    glutMainLoop();

    return 0;
}
