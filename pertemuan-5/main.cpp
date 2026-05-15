#include <stdlib.h> // standard definitions
#include <stdio.h>  // C I/O (for sprintf)
#include <math.h>   // standard definitions
#include <GL/glut.h> // GLUT

double rotAngle = 10;  // rotation angle
double rotAngle1 = 10; // rotation angle

//------------------------------------------------------------------
// init
// Sets up some default OpenGL values.
//------------------------------------------------------------------
void init()
{
    glClearColor(0, 0, 0, 0); // background color
    glClearDepth(1.0);        // background depth value

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000); // setup a perspective projection

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 0.0, 5.0, // eye position
        0.0, 0.0, 0.0, // lookat position
        0.0, 1.0, 0.0  // up direction
    );
}

//------------------------------------------------------------------
// display callback function
//------------------------------------------------------------------
void display()
{
    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    glPushMatrix();

    glRotated(rotAngle, 0, 1, 0);
    glRotated(rotAngle1, 1, 0, 0);

    glEnable(GL_COLOR_MATERIAL);

    glColor3f(1.0, 0.1, 0.1);

    glutSolidTeapot(1);

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

//------------------------------------------------------------------
// keyboard callback function
//------------------------------------------------------------------
void keyboard(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 'w':
            rotAngle += 10;
            break;

        case 'a':
            rotAngle1 += 10;
            break;

        case 's':
            rotAngle1 -= 10;
            break;

        case 'd':
            rotAngle -= 10;
            break;

        case 'q':
            exit(0);
    }

    glutPostRedisplay();
}

//------------------------------------------------------------------
// main program
//------------------------------------------------------------------
int main()
{
    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_DEPTH |
        GLUT_RGB
    );

    glutCreateWindow("GLUT Example");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}

// 1. Yang harus dilakukan untuk menggerakkan objek dengan keyboard
// Pertama membuat pemetaan keyword terlebih dahulu, kedua mengubah nilai variabel, dan menggambar ulang layar
// 2. Fungsi gluLookAt untuk mengatur posisi dan titik yang dilihat oleh kamera
// 3. Projection dan modelview sama sama digunakan untuk menampilkan objek 3D ke layar yang 2D
// Projection menentukan sudut pandang, jarak pandang, dan efek perspektif sehingga memungkinkan membuat objek jauh terlihat lebih kecil
// Modelview digunakan untuk mengatur posisi kamera dan transformasi objek