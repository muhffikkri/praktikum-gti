# Grafika Komputer - OpenGL

Selamat datang di repository tugas Praktikum Grafika Komputer. Repository ini berisi implementasi berbagai objek primitif dan manipulasi grafis menggunakan **OpenGL** dan library **GLUT**.

## 🛠️ Lingkungan Pengembangan

- **IDE**: Dev-C++ 4.9.9.2 (atau versi terbaru)
- **Library**: GLUT (OpenGL Utility Toolkit) versi 3.7.6+
- **Compiler**: MinGW

## 📂 Struktur Project

Project ini dibagi berdasarkan modul praktikum:

- `pertemuan-2/`: Primitif Drawing
  - `01-window/`: Membuat jendela dasar dengan warna background.
  - `02-point/`: Implementasi `GL_POINTS` dengan ukuran tertentu.
  - `03-line/`: Implementasi `GL_LINES` dengan ketebalan garis.
  - `04-triangle/`: Membuat segitiga dengan interpolasi warna (degradasi).
  - `05-rectangle/`: Menggambar segiempat penuh menggunakan `glRectf`.

## 🚀 Cara Menjalankan

1. Pastikan library `glut32.dll` sudah terpasang di direktori sistem Windows (`System32` atau `SysWOW64`).
2. Salin folder `include` dan `lib` dari paket GLUT ke folder instalasi Dev-C++.
3. Buka file `.dev` atau buat project baru di Dev-C++ dengan template **Multimedia > glut**.
4. Tekan `F9` untuk melakukan _Compile & Run_.

## 📍 Catatan Penting

- **Koordinat**: Titik pusat $(0,0,0)$ berada di tengah layar.
- **Sumbu Z**: Gunakan tanda negatif agar objek berada di dalam layar dan dapat dilihat.
- **Format Warna**: Menggunakan format RGB dengan nilai $0.0$ hingga $1.0$.
