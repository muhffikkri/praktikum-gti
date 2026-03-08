#include <gl/glut.h>

// Fungsi untuk mengatur apa yang akan digambar di jendela
void Jendela(void) {
    // Membersihkan layar dan men-set buffer warna ke nilai yang ditentukan di glClearColor
    glClear(GL_COLOR_BUFFER_BIT); 
    
    // Memastikan semua perintah grafis yang dikirim segera dieksekusi oleh sistem 
    glFlush(); 
}

int main(int argc, char* argv[]) {
    // Inisialisasi GLUT 
    glutInit(&argc, argv); 
    
    // Menentukan ukuran jendela (lebar 640, tinggi 480) 
    glutInitWindowSize(640, 480); 
    
    // Menentukan mode tampilan: Single Buffer dan format warna RGBA 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    
    // Membuat jendela dengan judul "biru"
    glutCreateWindow("biru"); 
    
    // Menentukan fungsi callback untuk menggambar
    glutDisplayFunc(Jendela); 
    
    // Mengatur warna latar belakang jendela (R=0, G=0, B=1, Alpha=1) -> Biru 
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); 
    
    // Memulai loop utama GLUT agar jendela tetap terbuka
    glutMainLoop(); 
    return 0;
}
