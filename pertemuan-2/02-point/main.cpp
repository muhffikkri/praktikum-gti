#include <gl/glut.h>

void point(void) {
    glClear(GL_COLOR_BUFFER_BIT); 
    // Mengatur besar titik menjadi 5.0
    glPointSize(5.0f); 
    
    // Prosedur menggambar titik 
    glBegin(GL_POINTS); 
        // Warna merah (RGB) 
        glColor3f(1.0f, 0.0f, 0.0f); 
        // Posisi titik (X, Y, Z) 
        glVertex3f(0.25, 0.25, 0.0);
    glEnd(); 
    
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv); 
    glutInitWindowSize(640, 480); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutCreateWindow("Titik");
    glutDisplayFunc(point);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop(); 
    return 0; 
}
