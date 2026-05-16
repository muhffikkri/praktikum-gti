#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.14159265f

int bitmapHeight = 12;

float angle = 0.0, deltaAngle = 0.0, ratio; // Sudut perputaran mobil
float carX = 0.0f, carZ = 0.0f;             // Koordinat posisi mobil
float camOrbitAngle = 0.0f;                 // Sudut orbit kamera manual (Home/End)
float deltaCamAngle = 0.0f;                 // Mekanisme delta untuk rotasi kamera manual
float deltaMove = 0.0f;                     // Mekanisme delta untuk pergerakan mobil         
float carAngle = 0.0f;                      // Sudut rotasi mobil (dikendalikan deltaAngle)
int h, w;                                   // 

// Fungsi pembantu untuk membuat prisma segitiga 
void drawTrianglePrism(float width, float height, float length) {
    glBegin(GL_TRIANGLES);
    // Sisi Depan
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-width/2, -height/2, -length/2);
    glVertex3f(width/2, -height/2, -length/2);
    glVertex3f(0.0f, height/2, -length/2);
    // Sisi Belakang
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-width/2, -height/2, length/2);
    glVertex3f(width/2, -height/2, length/2);
    glVertex3f(0.0f, height/2, length/2);
    glEnd();

    glBegin(GL_QUADS);
    // Sisi Bawah
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-width/2, -height/2, -length/2);
    glVertex3f(width/2, -height/2, -length/2);
    glVertex3f(width/2, -height/2, length/2);
    glVertex3f(-width/2, -height/2, length/2);
    // Sisi Miring Kiri
    glNormal3f(-height, width/2, 0.0f);
    glVertex3f(-width/2, -height/2, -length/2);
    glVertex3f(0.0f, height/2, -length/2);
    glVertex3f(0.0f, height/2, length/2);
    glVertex3f(-width/2, -height/2, length/2);
    // Sisi Miring Kanan
    glNormal3f(height, width/2, 0.0f);
    glVertex3f(width/2, -height/2, -length/2);
    glVertex3f(0.0f, height/2, -length/2);
    glVertex3f(0.0f, height/2, length/2);
    glVertex3f(width/2, -height/2, length/2);
    glEnd();
}

void Reshape(int w1, int h1)
{
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;

    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk menggambar Jalan Raya dan Lingkungan Hijau
void Environment()
{
    // Lapangan Hijau di Sekitar Jalan
    glColor3f(0.1f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    // Sebelah kiri jalan
    glVertex3f(-100.0f, 0.0f, -500.0f);
    glVertex3f(-6.0f,   0.0f, -500.0f);
    glVertex3f(-6.0f,   0.0f,  500.0f);
    glVertex3f(-100.0f, 0.0f,  500.0f);
    // Sebelah kanan jalan
    glVertex3f(6.0f,    0.0f, -500.0f);
    glVertex3f(100.0f,  0.0f, -500.0f);
    glVertex3f(100.0f,  0.0f,  500.0f);
    glVertex3f(6.0f,    0.0f,  500.0f);
    glEnd();

    // Aspal Jalan Raya
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-6.0f, 0.01f, -500.0f);
    glVertex3f( 6.0f, 0.01f, -500.0f);
    glVertex3f( 6.0f, 0.01f,  500.0f);
    glVertex3f(-6.0f, 0.01f,  500.0f);
    glEnd();

    // Markah Jalan Raya (Garis Putih Putus-putus)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (float i = -500.0f; i < 500.0f; i += 15.0f) {
        glVertex3f(-0.15f, 0.02f, i);
        glVertex3f( 0.15f, 0.02f, i);
        glVertex3f( 0.15f, 0.02f, i + 7.0f);
        glVertex3f(-0.15f, 0.02f, i + 7.0f);
    }
    glEnd();
}

// Fungsi Utama Menggambar Mobil 3D Balok Bertumpuk
void GambarMobil3D()
{
    glPushMatrix();
    glTranslatef(carX, 0.5f, carZ);
    glRotatef(-carAngle, 0.0f, 1.0f, 0.0f);

    // Body utama mobil (1 Balok Panjang)
    glColor3f(0.8f, 0.1f, 0.1f); 
    glPushMatrix();
    glScalef(2.0f, 0.6f, 4.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Balok di bawah body (Menyisakan space kosong di tengah untuk ban)
    glColor3f(0.4f, 0.1f, 0.1f); 
    // Balok bawah bagian depan
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, -1.5f);
    glScalef(1.8f, 0.3f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Balok bawah bagian belakang
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 1.5f);
    glScalef(1.8f, 0.3f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Ban mobil (4 Kubus)
    glColor3f(0.05f, 0.05f, 0.05f); 
    float wheelSize = 0.6f;
    // Depan Kiri & Kanan
    glPushMatrix(); glTranslatef(-1.0f, -0.3f, -1.2f); glutSolidCube(wheelSize); glPopMatrix();
    glPushMatrix(); glTranslatef(1.0f, -0.3f, -1.2f);  glutSolidCube(wheelSize); glPopMatrix();
    // Belakang Kiri & Kanan
    glPushMatrix(); glTranslatef(-1.0f, -0.3f, 1.2f);  glutSolidCube(wheelSize); glPopMatrix();
    glPushMatrix(); glTranslatef(1.0f, -0.3f, 1.2f);   glutSolidCube(wheelSize); glPopMatrix();

    // Bagian atas mobil (1 Balok Panjang Tengah & 2 Prisma Segitiga)
    glColor3f(0.9f, 0.2f, 0.2f);
    // Balok Tengah Atas
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glScalef(1.6f, 0.6f, 1.8f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Prisma Depan (Kaca Depan)
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, -1.2f);
    glRotatef(90, 0.0f, 1.0f, 0.0f); 
    drawTrianglePrism(0.6f, 0.6f, 1.6f);
    glPopMatrix();

    // Prisma Belakang (Kaca Belakang)
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 1.2f);
    glRotatef(-90, 0.0f, 1.0f, 0.0f); 
    drawTrianglePrism(0.6f, 0.6f, 1.6f);
    glPopMatrix();

    // Spion (Balok kecil di kiri dan kanan)
    glColor3f(0.1f, 0.1f, 0.1f); 
    // Spion Kiri
    glPushMatrix();
    glTranslatef(-1.1f, 0.4f, -1.0f);
    glScalef(0.2f, 0.15f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Spion Kanan
    glPushMatrix();
    glTranslatef(1.1f, 0.4f, -1.0f);
    glScalef(0.2f, 0.15f, 0.15f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void display()
{
    if (deltaMove != 0.0f) { 
        carX += sin(carAngle * PI / 180.0f) * deltaMove;
        carZ -= cos(carAngle * PI / 180.0f) * deltaMove;
    }

    // Logika Rotasi Mobil di tempat menggunakan deltaAngle 
    if (deltaAngle) { 
        carAngle += deltaAngle;
    }

    // Logika Rotasi Kamera Orbit menggunakan deltaCamAngle 
    if (deltaCamAngle) { 
        camOrbitAngle += deltaCamAngle;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera selalu mengikuti bagian belakang-atas mobil 
    float camDist = 9.0f;   
    float camHeight = 3.5f; 
    
    // Sudut total kamera menggabungkan arah hadap mobil + rotasi kamera manual (Home/End)
    float totalCamAngle = carAngle + camOrbitAngle;

    float camX = carX - camDist * sin(totalCamAngle * PI / 180.0f);
    float camZ = carZ + camDist * cos(totalCamAngle * PI / 180.0f);
    float camY = camHeight;

    // Kamera membidik tepat ke arah poros tengah mobil (carX, 0.5f, carZ)
    gluLookAt(
        camX, camY, camZ,
        carX, 0.5f, carZ,
        0.0f, 1.0f, 0.0f
    );

    // Render Lingkungan Jalan & Objek Mobil
    Environment();
    GambarMobil3D();

    glutSwapBuffers();
    glFlush();
}

// Menangani Special Key saat ditekan 
void pressKey(int key, int x, int y)
{
    switch (key)
    {
        // Kontrol Translasi Maju Mundur Mobil 
        case GLUT_KEY_UP:
            deltaMove = 0.04f;  
            break;
        case GLUT_KEY_DOWN:
            deltaMove = -0.04f; 
            break;

        // Kontrol Rotasi Belok Mobil di Tempat
        case GLUT_KEY_LEFT:
            deltaAngle = -0.03f;
            break;
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.03f;
            break;

        // Kontrol Putar Kamera 
        case GLUT_KEY_HOME:
            deltaCamAngle = -0.02f; 
            break;
        case GLUT_KEY_END:
            deltaCamAngle = 0.02f;  
            break;
    }
}

// Menangani Special Key saat dielpas
void releaseKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            if (deltaMove > 0.0f) deltaMove = 0.0f;
            break;
        case GLUT_KEY_DOWN:
            if (deltaMove < 0.0f) deltaMove = 0.0f;
            break;
        case GLUT_KEY_LEFT:
            if (deltaAngle < 0.0f) deltaAngle = 0.0f;
            break;
        case GLUT_KEY_RIGHT:
            if (deltaAngle > 0.0f) deltaAngle = 0.0f;
            break;
        case GLUT_KEY_HOME:
            if (deltaCamAngle < 0.0f) deltaCamAngle = 0.0f; 
            break;
        case GLUT_KEY_END:
            if (deltaCamAngle > 0.0f) deltaCamAngle = 0.0f; 
            break;
    }
}

void keyboard(unsigned char k, int x, int y)
{
    if (k == 'q' || k == 'Q' || k == 27) { 
        exit(0);
    }
}

const GLfloat light_ambient[]  = {0.4f, 0.4f, 0.4f, 1.0f};
const GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {10.0f, 30.0f, 20.0f, 1.0f};

const GLfloat mat_ambient[]  = {0.6f, 0.6f, 0.6f, 1.0f};
const GLfloat mat_diffuse[]  = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat high_shininess[] = {50.0f};

void lighting()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f); 
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tugas Akhir M6: 3D Car Driving Environment");

    glutIgnoreKeyRepeat(1);

    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    
    glutKeyboardFunc(keyboard);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);

    lighting();
    init();

    glutMainLoop();
    return 0;
}