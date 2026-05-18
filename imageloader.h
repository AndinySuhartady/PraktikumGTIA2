//Andiny Khaerany Suhartady
//24060124140194


/*
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * File untuk tutorial "Putting It All Together"
 * pada OpenGL tutorial di:
 * www.videotutorialsrock.com
 */

#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED

// Merepresentasikan sebuah gambar
class Image {

public:

    Image(char* ps, int w, int h);
    ~Image();

    /*
     * Array pixel dengan format:
     * (R1, G1, B1, R2, G2, B2, ...)
     *
     * Menunjukkan warna setiap pixel pada gambar.
     * Nilai warna berada pada rentang 0 - 255.
     *
     * Array dimulai dari pixel kiri bawah,
     * kemudian bergerak ke kanan sampai akhir baris,
     * lalu naik ke baris berikutnya, dan seterusnya.
     *
     * Format ini sesuai dengan format yang digunakan OpenGL.
     */

    char* pixels;

    int width;
    int height;
};

// Membaca file gambar bitmap (.bmp)
Image* loadBMP(const char* filename);

#endif
