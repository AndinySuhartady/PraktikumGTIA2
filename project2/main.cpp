#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include <GL/glut.h>

#include <stdlib.h>


void Jendela(void)
{
    // membersihkan layar dan men-set dalam format warna
    glClear(GL_COLOR_BUFFER_BIT);

    // memastikan seluruh perintah tereksekusi
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Biru");
    glutDisplayFunc(Jendela);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glutMainLoop();
    return 0;
}
