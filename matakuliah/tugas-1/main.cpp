#include <GL/glut.h>

// Ukuran Foto (m x n)
float m = 100.0f; 
float n = 100.0f;

// Ukuran Layar (u x v)
int u = 800;
int v = 600;

// Fungsi Transformasi X: Foto ke Layar
float transformX(float x_foto) {
    return x_foto * (u / m);
}

// Fungsi Transformasi Y: Foto ke Layar (Kartesius ke Top-Left)
float transformY(float y_foto) {
    return (float)v - (y_foto * (v / n));
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.5f, 0.0f); 
        glVertex2f(transformX(5),  transformY(0));  
        glVertex2f(transformX(10), transformY(0));  
        glVertex2f(transformX(10), transformY(15)); 
        glVertex2f(transformX(5),  transformY(15)); 
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f); 
        glVertex2f(transformX(20), transformY(0));  
        glVertex2f(transformX(20), transformY(20)); 
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, u, v, 0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(u, v);
    glutCreateWindow("Transformasi Koordinat Foto");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

