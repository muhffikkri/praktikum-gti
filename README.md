# Grafika Komputer - OpenGL

Selamat datang di repository tugas Praktikum Grafika Komputer. Repository ini berisi implementasi berbagai objek primitif dan manipulasi grafis menggunakan **OpenGL** dan library **GLUT**.

## 🛠️ Lingkungan Pengembangan
- [cite_start]**IDE**: Dev-C++ 4.9.9.2 (atau versi terbaru) [cite: 16]
- [cite_start]**Library**: GLUT (OpenGL Utility Toolkit) versi 3.7.6+ [cite: 16]
- **Compiler**: MinGW

## 📂 Struktur Project
Project ini dibagi berdasarkan modul praktikum:

- `01-Instalasi/`: Panduan konfigurasi GLUT pada Dev-C++.
- `02-Primitif-Drawing/`:
    - `01-Jendela/`: Membuat jendela dasar dengan warna background.
    - [cite_start]`02-Titik/`: Implementasi `GL_POINTS` dengan ukuran tertentu[cite: 219].
    - [cite_start]`03-Garis/`: Implementasi `GL_LINES` dengan ketebalan garis[cite: 250, 255].
    - [cite_start]`04-Segitiga/`: Membuat segitiga dengan interpolasi warna (degradasi)[cite: 278, 309].
    - [cite_start]`05-SegiEmpat/`: Menggambar segiempat penuh menggunakan `glRectf`[cite: 310].

## 🚀 Cara Menjalankan
1. [cite_start]Pastikan library `glut32.dll` sudah terpasang di direktori sistem Windows (`System32` atau `SysWOW64`) [cite: 143-145].
2. [cite_start]Salin folder `include` dan `lib` dari paket GLUT ke folder instalasi Dev-C++ [cite: 146-154].
3. [cite_start]Buka file `.dev` atau buat project baru di Dev-C++ dengan template **Multimedia > glut** [cite: 157-159].
4. [cite_start]Tekan `F9` untuk melakukan *Compile & Run*[cite: 180].

## 📍 Catatan Penting
- [cite_start]**Koordinat**: Titik pusat $(0,0,0)$ berada di tengah layar[cite: 246].
- [cite_start]**Sumbu Z**: Gunakan tanda negatif agar objek berada di dalam layar dan dapat dilihat[cite: 249].
- [cite_start]**Format Warna**: Menggunakan format RGB dengan nilai $0.0$ hingga $1.0$[cite: 244].