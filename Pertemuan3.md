Robot Arm 3D dengan Visualisasi Sumbu XYZ
Identitas
Nama: Andiny Kaherany Suhartady
NIM: 24060124140194
Bahasa Pemrograman: C++
Library: OpenGL, GLUT
Deskripsi Program

Program ini merupakan simulasi Robot Arm 3D yang dibuat menggunakan OpenGL dan GLUT. Program menampilkan sebuah lengan robot (robotic arm) dalam bentuk wireframe (kerangka) beserta visualisasi sumbu koordinat Cartesian (X, Y, dan Z).

Simulasi ini bertujuan untuk memperlihatkan konsep:

Pemodelan objek 3D.
Transformasi geometri (translasi, rotasi, dan skala).
Hierarchical Modeling (pemodelan bertingkat).
Sistem koordinat 3D menggunakan sumbu XYZ.
Dasar kinematika robot (robot arm).

Robot arm tersusun dari beberapa bagian yang saling terhubung, sehingga ketika salah satu bagian berotasi, bagian lainnya ikut bergerak sesuai hubungan parent-child. Konsep ini merupakan dasar dari pemodelan lengan robot pada aplikasi robotika dan animasi komputer.


Tampilan Program

Program menampilkan:

Basis (base) robot.
Lengan utama (upper arm).
Bagian ujung (end effector/gripper).
Sumbu koordinat XYZ.

Contoh tampilan:

Posisi awal robot arm.
Rotasi lengan robot.
Perubahan orientasi terhadap sumbu koordinat.
Penjelasan Sumbu XYZ

Pada grafika komputer dan robotika, sistem koordinat yang digunakan adalah Cartesian Coordinate System yang terdiri dari tiga sumbu:

1. Sumbu X (Merah)
Menunjukkan arah kanan-kiri.
Nilai positif (+X) menuju ke kanan.
Nilai negatif (-X) menuju ke kiri.

Pada program ini, sumbu X digambarkan dengan garis merah.

2. Sumbu Y
Menunjukkan arah depan-belakang.
Dalam sistem koordinat robotika, sumbu Y biasanya digunakan sebagai arah lateral (kiri-kanan terhadap robot).

3. Sumbu Z (Hijau)
Menunjukkan arah atas-bawah.
Nilai positif (+Z) menuju ke atas.
Nilai negatif (-Z) menuju ke bawah.

Pada program ini, sumbu Z digambarkan dengan garis hijau.


<img width="1082" height="961" alt="Screenshot (807)" src="https://github.com/user-attachments/assets/1e0aade9-a46e-4b0e-89b1-457cc2cc6aac" />
<img width="1085" height="964" alt="Screenshot (808)" src="https://github.com/user-attachments/assets/4ab9f2cc-6cf2-4aea-b5bc-16ee9ad28bfc" />
<img width="1056" height="955" alt="Screenshot (806)" src="https://github.com/user-attachments/assets/ef3b8c63-a79a-4822-8085-c4088daf919c" />
<img width="1045" height="942" alt="Screenshot (795)" src="https://github.com/user-attachments/assets/6f249cb9-5444-460f-af9b-810a896f20f1" />
<img width="1051" height="942" alt="Screenshot (793)" src="https://github.com/user-attachments/assets/4ea23fec-6cf9-4215-a761-77aa31bf0bd4" />
<img width="1042" height="942" alt="Screenshot (794)" src="https://github.com/user-attachments/assets/eba6f814-1cb8-4f9f-8be9-f45f8ecaaaf4" />
