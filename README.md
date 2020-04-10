# SoalShiftSISOP20_modul3_T17
Nama Anggota Kelompok T17 :
  1. Faza Murtadho [05311840000034]
  2. Rindi Kartika Sari [05311840000013]

## Soal Shift Modul 3 dan Penyelesaian Soal Shift Modul 3
### Soal 4
* #### Soal 4A
  Buatlah program C yang berisi program untuk melakukan perkalian dua buah matriks dengan ketentuan berikut ini : <br>
  A. Matriks pertama berordo __4 x 2__ <br>
  B. Matriks kedua berordo __2 x 5__ <br>
  C. Kedua matriks tersebut berisi angka 1 - 20 <br>
  #### Code : 
  #### Penyelesaian :
  * Untuk membantu jalannya program ini, maka digunakan beberapa _Library_ berikut ini :
    ```bash
    #include <stdio.h>
    #include <pthread.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    ```
  * Inisialisasi kedua matriks yang berisi angka 1 - 20 dengan ordo yang telah ditentukan yakni matriks pertama berordo __4 x 2__ ```int matA[4][2] = {{1, 1}, {2, 2},{1, 1},{2, 2}};``` dan matriks kedua berordo __2 x 5__ ```int matB[2][5] = {{1, 4, 1, 2, 1},{1, 2, 1, 4, 1}};``` serta ```int matC[4][5];``` yang akan menampung matriks hasil perkalian kedua matriks tersebut.
    ```bash
    int matA[4][2] = {{1, 1}, {2, 2},{1, 1},{2, 2}};
    int matB[2][5] = {{1, 4, 1, 2, 1},{1, 2, 1, 4, 1}};
    int matC[4][5];
    ```
  * Setelah inisialisasi matriks selesai, kita berikan struct yang berguna untuk _passing_ data ke dalam thread
    ```bash
    struct args {
    int i;
    int j;
    };
    ```
    Variabel ```i``` untuk menunjukkan baris, sedangkan variabel ```j``` untuk menunjukkan kolom.
  * Struct yang telah kita buat di atas akan kita passing ke dalam ```void *``` dan kemudian akan dilanjutkan untuk dimasukkan ke dalam fungsi
     ```bash 
     void *kali(void* arg) {
     int i = ((struct args*)arg)->i;
     int j = ((struct args*)arg)->j;
     ```
  * Dalam fungsi ```main``` terdapat ``` pthread_t tid[4][5];``` yang menunjukkan array dari thread bernama __tid__ yakni dengan _size_ __4 x 5__.
