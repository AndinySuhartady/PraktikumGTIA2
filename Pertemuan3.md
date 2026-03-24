Pertemuan 3 
Nama : Andiny Khaerany Suhartady 
Tanggal : 23/03/2026 
NIM : 24060124140194

1) Proyeksi

<img width="475" height="510" alt="Screenshot (804)" src="https://github.com/user-attachments/assets/bc0584ee-6606-4f80-9646-b50652b88a7c" />

2) Kubus Berotasi

<img width="456" height="495" alt="Screenshot (801)" src="https://github.com/user-attachments/assets/72533194-4969-4007-adce-3f05ca44fed8" />

3) Lengan Bergerak

<img width="1052" height="952" alt="Screenshot (802)" src="https://github.com/user-attachments/assets/383d41a5-6f92-448d-a38d-5762daf3ea01" />

4) Robot Arm
Dua Jari
<img width="1051" height="942" alt="Screenshot (793)" src="https://github.com/user-attachments/assets/2ea220cb-4117-49f2-abea-014384276ff4" />

<img width="1056" height="955" alt="Screenshot (806)" src="https://github.com/user-attachments/assets/67fbdea2-4259-422f-b09e-cbae493c3729" />

Jari telunjuk & tengah → lurus
Jari lain → menekuk
  Analisis XYZ:
  Rotasi Z (utama)
glRotatef(angle, 0,0,1);

Menekuk jari (flexion):
Jari telunjuk & tengah → rotasi kecil (≈ 0°)
Jari lain → rotasi besar (≈ 60°–90°)

Semua terjadi di bidang XY (rotasi sumbu Z)

Menengadah
<img width="1042" height="942" alt="Screenshot (794)" src="https://github.com/user-attachments/assets/e7e4ad9e-26ee-488f-b1ba-94eb35427332" />

<img width="1082" height="961" alt="Screenshot (807)" src="https://github.com/user-attachments/assets/ab0793f2-e877-4fa0-8bcc-f1e8962815a4" />

Telapak menghadap ke atas
Pergelangan diputar
  Analisis XYZ:
  Rotasi X 
glRotatef(angle, 1,0,0);

Membalik telapak ke atas
Rotasi terhadap sumbu X
Gerakan terjadi di bidang YZ


Mengepal
<img width="1045" height="942" alt="Screenshot (795)" src="https://github.com/user-attachments/assets/d8343617-4cc0-4fd3-88a8-864324306be7" />

<img width="1085" height="964" alt="Screenshot (808)" src="https://github.com/user-attachments/assets/6ae49120-bebe-4929-843a-24269b0b5ed1" />

Semua jari menekuk ke dalam
Telapak sedikit ikut rotasi
  Analisis XYZ:
  Rotasi Z (utama)
glRotatef(angle, 0,0,1);

Menekuk semua ruas jari
