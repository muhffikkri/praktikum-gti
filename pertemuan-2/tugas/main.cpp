#include <GL/glut.h>

void displayPrimitif(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix(); 
    glTranslatef(0.1f, -0.4f, 0.0f); 

    for (int i = 0; i < 8; i++) {
        // 1. MENGGAMBAR ANAK TANGGA (ORANYE)
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.5f, 0.0f); // Warna oranye
            glVertex2f(-0.7f + (i * 0.1f), 0.1f + (i * 0.1f)); // Kiri Atas
            glVertex2f(-0.5f + (i * 0.1f), 0.1f + (i * 0.1f)); // Kanan Atas
            glVertex2f(-0.5f + (i * 0.1f), 0.0f + (i * 0.1f)); // Kanan Bawah
            glVertex2f(-0.7f + (i * 0.1f), 0.0f + (i * 0.1f)); // Kiri Bawah
        glEnd();

        // 2. MENGGAMBAR GARIS HORIZONTAL DI TENGAH (PUTIH)
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f); // Warna putih
            
            float y_tengah = 0.05f + (i * 0.1f);
            
            // Titik awal garis (Kiri)
            glVertex2f(-0.7f + (i * 0.1f), y_tengah); 
            // Titik akhir garis (Kanan) - Y harus sama agar horizontal
            glVertex2f(-0.5f + (i * 0.1f), y_tengah); 
        glEnd(); 
    }
    
    glPopMatrix(); 
    glFlush(); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Latihan Pertemuan 2");
    glutDisplayFunc(displayPrimitif);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glutMainLoop();
    return 0;
}
