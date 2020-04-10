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
  * Banyak fungsi yang terdapat dalam ```main```, untuk _code_ berikut ini :
    ```bash
    for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      struct args *index = (struct args *)malloc(sizeof(struct args));
      index->i = i;
      index->j = j;
      pthread_create(&tid[i][j], NULL, &kali, (void *)index);
    }
    ```
    Pada ```struct args *index = (struct args *)malloc(sizeof(struct args));```ini akan membuat _object_ dari ```struct args``` bernama __index__ dan sekaligus melakukan pengalokasian memori sebesar _size_ dari ```struct args```. <br>
    Setelah pengalokasian memori, ```index->i = i;``` akan mengatur nilai i pada _object_ dari ```struct args``` bernama __index__ dengan __nilai i__. Hal ini juga dilakukan pada nilai j, ``` index->j = j;``` yang akan mengatur nilai j pada _object_ dari ```struct args``` bernama __index__ dengan __nilai j__. <br>
    Kemudian, ```pthread_create(&tid[i][j], NULL, &kali, (void *)index);``` membuat thread pada array dari thread bernama __tid__ pada __nilai i__ dan __nilai j__ dengan memanggil fungsi __kali__ dengan parameter __index__. <br>  
  * Dilanjutkan dengan menggabungkan semua thread yang ada 
    ```bash
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        pthread_join(tid[i][j], NULL);
      }
    }
    ```
  * Hasil perkalian kedua buah matriks dalam matriks C akan ditampilkan pada layar
    ```bash
    printf("Matriks :\n");
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        printf("%4d", matC[i][j]);
      }
    printf("\n");
    }
  * Membuat Shared Memory ID sesuai dengan key yang telah ditentukan ```key_t key = 1337;``` yakni ```1337```.
  * _Code_ berikut akan membuat Shared Memory ```shmid``` dengan _size_ dari matriks C ```sizeof(matC)``` dengan ```key``` _private key_ (kunci pribadi) dan pada Shared Memory ini mengizinkan adanya ```0666``` _read and write_. 
    ```bash
    int shmid = shmget(key, sizeof(matC), IPC_CREAT | 0666);
    ```
  * Shared Memory berhasil dialokasikan, tetapi belum menjadi bagian dari _Address Space_. Oleh karena itu, kita gunakan ```shmat``` untuk menjadikan Shared Memory tersebut bagian dari _Address Space_. 
    ```bash
    value = shmat(shmid, NULL, 0);
    ```
