#include <windows.h> 
#include <GL/glut.h>
#include <math.h>
#include <GL/glut.h>
static int shoulder = 0, elbow = 0; // Sudut sendi 

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
        glPopMatrix(); // Kembali ke koordinat siku 
        
    glPopMatrix(); // Kembali ke koordinat dunia 
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; glutPostRedisplay(); break; // Bahu naik 
        case 'S': shoulder = (shoulder - 5) % 360; glutPostRedisplay(); break; // Bahu turun 
        case 'e': elbow = (elbow + 5) % 360; glutPostRedisplay(); break;       // Siku naik 
        case 'E': elbow = (elbow - 5) % 360; glutPostRedisplay(); break;       // Siku turun 
        case 27: exit(0); break; // Tombol ESC untuk keluar 
    }
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