#include <GL/glut.h>

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); // Menghapus/reset matriks sebelumnya 
    
    glBegin(GL_POLYGON);
        glColor3f(0.0, 0.0, 0.0); glVertex3f(-0.5, -0.5, -3.0);
        glColor3f(1.0, 0.0, 0.0); glVertex3f(0.5, -0.5, -3.0);
        glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, 0.5, -3.0);
    glEnd();
    glFlush();
}

void Reshape(int x, int y) {
    if (y == 0 || x == 0) return; // Menghindari pembagian nol 
    
    glMatrixMode(GL_PROJECTION); // Mengatur matriks proyeksi 
    glLoadIdentity();
    // Sudut 40 derajat, aspek rasio, jarak dekat 0.5, jarak jauh 20.0  
    gluPerspective(40.0, (GLdouble)x/(GLdouble)y, 0.5, 20.0);
    
    glMatrixMode(GL_MODELVIEW); 
    glViewport(0, 0, x, y); // Luas area rendering di jendela 
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Intro");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape); // Fungsi callback saat jendela diubah ukurannya 
    glutMainLoop();
    return 0;
}