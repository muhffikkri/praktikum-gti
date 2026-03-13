#include <gl/glut.h>

void SegiEmpat(void) {
    // Membersihkan buffer warna
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Melakukan translasi (geser sumbu x sebesar -0.50 dan y sebesar 0.50) 
    glTranslatef(-0.50, 0.50, 0.0);
    
    // Mengatur warna menjadi merah 
    glColor3f(1.0f, 0.0f, 0.0f);
    
    // Menggambar segiempat dengan koordinat relatif terhadap sumbu baru 
    glRectf(-0.18, 0.18, 0.18, -0.18);
    
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Translasi Segi Empat");
    glutDisplayFunc(SegiEmpat);
    
    // Warna latar belakang biru 
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    
    glutMainLoop();
    return 0;
}
