#include <GL/glut.h>
GLfloat xRotated, yRotated, zRotated; // Variabel rotasi 

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -4.0); // Geser mundur agar objek terlihat kamera 
    
    glRotatef(xRotated, 1.0, 0.0, 0.0); // Rotasi di sumbu X 
    glRotatef(yRotated, 0.0, 1.0, 0.0); // Rotasi di sumbu Y 
    glRotatef(zRotated, 0.0, 0.0, 1.0); // Rotasi di sumbu Z 
    
    glScalef(2.0, 1.0, 1.0);   // Penskalaan 
    glutWireCube(1.0);         // Menggambar kubus kerangka 
    glutSwapBuffers();         // Tukar buffer untuk animasi halus 
    glFlush();
}

void Idle(void) {
    xRotated += 0.3; // Increment nilai rotasi 
    yRotated += 0.1; 
    zRotated += -0.4; 
    Display(); // Gambar ulang 
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
