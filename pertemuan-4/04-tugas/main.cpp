#include <windows.h> 
#include <GL/glut.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
static int shoulder = 0, elbow = 0; // Sudut sendi 
static int palm = 0, finger = 0;

/**
 * Penjelasan cara kerja 
 * Ada 4 transformasi yang terjadi
 * 1. koordinat dari dunia disimpan terlebih dahulu pada glPushMatrix. Koordinat tersebut ditranslasikan pada sumbu x sejauh -1, kemudian bahu akan dirotasikan pada sumbu tersebut sebesar variabel yang diubah dengan keyboard. Koordinat dikembalikan lagi ke titik asal. 
 * 2. koordinat dari bahu disimpan terlebih dahulu kemudian menyiapkan gambar lengan atas dengan glScaelf sebesar x: 2, y: 4, dan z: 1. Setelah lengan atas digambar maka kembali lagi ke koordinat bahu.
 * 3. Pindah kembali ke ujung lengan atas (siku) dan gerakan siku dengan glRotatef sebesar variabel yang diubah dengan keyboard. Translasikan untuk menyiapkan koordinat membuat lengan bawah
 * 4. Simpan koordinat siku dan gambar lengan bawah sebesar x: 2, y: 4, dan z: 1. Gambar lengan bawah dan kembali ke siku
 * 5. Pindah ke ujung lengan bawah dan rotasi kan telapak tangan, translasi sejauh 0.25 pada sumbu x untuk menyiapkan posisi gambar telapak tangan. Gambar telapak tangan dan kembali ke koordinat bahu
 * 6. Pindah ke ujung telapak tangan dan gunakan for loop untuk menggambar jari. Pertama, koordinat ditranslasikan pada sumbu z dari -0.35 hingga 0.35. Kemudian tiap tiap koordinat tersebut akan digambar jari sebesar x: 0.4 y: 0.15, dan z: 0.2
 * 7. Matriks kemudian dikembalikan lagi satu persatu hingga ke koordinat dunia dengan glPopMatrix
 * 8. Pada kode ini juga menggunakan glutSwapBuffers dan glutPostRedisplay agar canvas bisa digambar terus menerus ketika terjadi perubahan
 */

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // Simpan koordinat dunia 
        glTranslatef(-1.0, 0.0, 0.0);
        glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0); // Gerakkan bahu 
        glTranslatef(1.0, 0.0, 0.0);
        
        glPushMatrix(); // Simpan koordinat bahu
            glScalef(2.0, 0.4, 1.0);
            glutWireCube(1.0); // Gambar lengan atas 
        glPopMatrix(); // Kembali ke koordinat bahu 
        
        glTranslatef(1.0, 0.0, 0.0);
        glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0); // Gerakkan siku 
        glTranslatef(1.0, 0.0, 0.0);
        
        glPushMatrix(); // Simpan koordinat siku
            glScalef(2.0, 0.4, 1.0);
            glutWireCube(1.0); // Gambar lengan bawah 
        glPopMatrix();
            
        glTranslatef(1.0, 0.0, 0.0); // Pindah ke ujung lengan bawah
        glRotatef((GLfloat) palm, 0.0, 0.0, 1.0); // Rotasi telapak
        glTranslatef(0.25, 0.0, 0.0); // Pivot telapak

        glPushMatrix(); // Simpan koordinat telapak tangan
            glScalef(0.5, 0.6, 1.0);
            glutWireCube(1.0); // Gambar telapak tangan
        glPopMatrix(); // Kembali ke koordinat bahu 
        
        glTranslatef(0.25, 0.0, 0.0); // Pindah ke ujung telapak (pangkal jari)
            
        for(int i = -1; i <= 1; i++) {
            glPushMatrix();
                // Geser posisi jari agar sejajar (Z-axis)
                glTranslatef(0.0, 0.0, i * 0.35); 
                
                // Rotasi masing-masing jari
                glRotatef((GLfloat) finger, 0.0, 0.0, 1.0);
                glTranslatef(0.2, 0.0, 0.0); // Pivot jari
                
                glPushMatrix();
                    glScalef(0.4, 0.15, 0.2); // Ukuran jari berbentuk balok
                    glutWireCube(1.0);
                glPopMatrix();
            glPopMatrix();
        }
        
    glPopMatrix(); // Kembali ke koordinat dunia 
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Kontrol Bahu & Siku
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        
        // Tambahan Kontrol Telapak & Jari
        case 'p': palm = (palm + 5) % 360; break;
        case 'P': palm = (palm - 5) % 360; break;
        case 'f': finger = (finger + 5) % 360; break;
        case 'F': finger = (finger - 5) % 360; break;
        
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLdouble) w/(GLdouble) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0); // Mundurkan kamera agar lengan terlihat
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Gunakan DOUBLE buffer untuk animasi
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lengan Bergerak - Fikri");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
