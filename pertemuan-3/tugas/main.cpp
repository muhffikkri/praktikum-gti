#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535898 

struct color {
   float r, g, b;
};

// Definisi Warna dengan normalisasi 0-1 
color yellow = {255/255.0f, 242/255.0f, 0/255.0f};
color green  = {14/255.0f, 209/255.0f, 69/255.0f};
color blue   = {0/255.0f, 168/255.0f, 243/255.0f};
color grey   = {88/255.0f, 88/255.0f, 88/255.0f};
color white  = {255/255.0f, 255/255.0f, 255/255.0f};
color brown  = {136/255.0f, 68/255.0f, 20/255.0f};
color maroon = {136/255.0f, 0/255.0f, 27/255.0f};

// Fungsi jalan 
void roadway(void) {
    // Rumput Atas (Upper Sideway)
    glColor3f(green.r, green.g, green.b); 
    glRectf(-1.0f, -0.2f, 1.0f, -0.4f);
    
    // Jalan Aspal
    glColor3f(grey.r, grey.g, grey.b); 
    glRectf(-1.0f, -0.4f, 1.0f, -0.8f); 
    
    // Rumput Bawah (Lower Sideway)
    glColor3f(green.r, green.g, green.b); 
    glRectf(-1.0f, -0.8f, 1.0f, -1.0f);
    
    // Garis Jalan Putus-putus
    glColor3f(white.r, white.g, white.b); 
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
            glTranslatef(-1.0f + (i * 0.4f), -0.6f, 0.0f); 
            glRectf(0.0f, 0.02f, 0.2f, -0.02f); 
        glPopMatrix();
    }
}

// Fungsi Matahari 
void sun(void) {
    glPushMatrix(); 
        glTranslatef(-0.7f, 0.7f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(yellow.r, yellow.g, yellow.b); 
            for (int i = 0; i < 100; i++) {
                float angle = 2.0f * PI * i / 100; 
                glVertex2f(0.15f * cos(angle), 0.15f * sin(angle)); 
            }
        glEnd();
    glPopMatrix(); 
}

// Fungsi Awan (Cloud) 
void cloud(float posX, float posY) {
    glColor3f(blue.r, blue.g, blue.b); 
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
            glTranslatef(posX + (i * 0.1f), posY, 0.0f);
            glBegin(GL_POLYGON);
                for (int j = 0; j < 50; j++) {
                    float angle = 2.0f * PI * j / 50;
                    glVertex2f(0.12f * cos(angle), 0.1f * sin(angle));
                }
            glEnd();
        glPopMatrix();
    }
}

// Fungsi Pohon dengan daun elips 
void tree(float posX, float posY) {
    glPushMatrix();
        glTranslatef(posX, posY, 0.0f);
        glColor3f(brown.r, brown.g, brown.b);
        glRectf(-0.02f, 0.0f, 0.02f, 0.15f);
        
        glPushMatrix();
            glTranslatef(0.0f, 0.2f, 0.0f);
            glScalef(1.5f, 1.0f, 1.0f); 
            glBegin(GL_POLYGON);
                glColor3f(green.r, green.g, green.b);
                for (int i = 0; i < 50; i++) {
                    float angle = 2.0f * PI * i / 50;
                    glVertex2f(0.08f * cos(angle), 0.08f * sin(angle));
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

// Fungsi car 
void car(float posX, float posY) {
    glPushMatrix();
        glTranslatef(posX, posY, 0.0f);
        glScalef(0.4f, 0.4f, 1.0f);

        // 1. BODY UTAMA (Maroon)
        glColor3f(maroon.r, maroon.g, maroon.b);
        glRectf(-0.6f, 0.2f, 0.6f, -0.2f); 
        glRectf(-0.3f, 0.4f, 0.3f, 0.2f);  

        // 2. JENDELA / KACA MIRING (Biru Muda)
        glColor3f(blue.r, blue.g, blue.b); 
        glBegin(GL_TRIANGLES);
            glVertex2f(0.3f, 0.4f);  
            glVertex2f(0.3f, 0.2f);  
            glVertex2f(0.5f, 0.2f);  

            glVertex2f(-0.3f, 0.4f); 
            glVertex2f(-0.3f, 0.2f); 
            glVertex2f(-0.5f, 0.2f); 
        glEnd();

        // 3. RODA (Hitam)
        glColor3f(0.0f, 0.0f, 0.0f);
        float rodaPos[2] = {-0.35f, 0.35f};
        for(int i = 0; i < 2; i++) {
            glPushMatrix();
                glTranslatef(rodaPos[i], -0.2f, 0.0f);
                glBegin(GL_POLYGON);
                    for(int j = 0; j < 30; j++) {
                        float angle = 2.0f * PI * j / 30;
                        glVertex2f(0.12f * cos(angle), 0.12f * sin(angle));
                    }
                glEnd();
            glPopMatrix();
        }
    glPopMatrix();
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT); 

    sun(); // Kiri Atas
    cloud(0.5f, 0.7f);  // Kanan Atas
    cloud(0.0f, 0.5f);  // Tengah Atas

    roadway(); // Di bagian bawah

    // 3 Pohon di Rumput Atas
    tree(-0.7f, -0.35f); tree(-0.2f, -0.35f); tree(0.3f, -0.35f);
    
    // 2 Pohon di Rumput Bawah
    tree(-0.5f, -0.95f); tree(0.5f, -0.95f);

    car(0.0f, -0.55f); // Mobil di tengah jalan

    glFlush(); 
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Pemandangan Mobil");
    glutDisplayFunc(RenderScene);
    
    // Warna langit biru cerah
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); 
    
    glutMainLoop();
    return 0;
}
