# SoalShiftSISOP20_modul3_T17
Nama Anggota Kelompok T17 :
  1. Faza Murtadho [05311840000034]
  2. Rindi Kartika Sari [05311840000013]

## Soal Shift Modul 3 dan Penyelesaian Soal Shift Modul 3
### Soal 3
Buatlah program C yang berjalan untuk mengategorikan file dengan memindahkan file ke dalam folder yang sesuai dengan ekstensinya yang folder hasilnya terdapat di _working directory_ ketika program tersebut dijalankan. Program ini memiliki ketentuan untuk beberapa opsi yang tersedia yakni :
```-f``` untuk kategorisasi file yang telah ditentukan 
```-d``` untuk kategorisasi di folder yang telah ditentukan
```\*``` untuk kategorisasi di folder dimana program tersebut berada
  #### Code : https://github.com/rindikar/SoalShiftSISOP20_modul3_T17/blob/master/soal3.c
  #### Penyelesaian :
  * Untuk membantu jalannya program ini, maka digunakan beberapa _Library_ berikut ini :
    ```bash
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <ctype.h>
    #include <dirent.h>
    #include <pthread.h>
    #include <errno.h>
    ```
  * Kemudian, dibuatlah sebuah code untuk mendapatkan nama dari file tersebut
    ```bash
    char *getFileName(char *fName, char buff[]) {
        char *token = strtok(fName, "/");
        while (token != NULL) {
          sprintf(buff, "%s", token);
          token = strtok(NULL, "/");
        }
    }
    ```
  * Selain nama dari setiap file didapatkan, ekstensi dari file tersebut juga harus didapatkan sebagai kunci untuk melakukan kategorisasi
    ```bash
    char *getExtension(char *fName, char buff[]) {
        char buffFileName[1337];
        char *token = strtok(fName, "/");
        while (token != NULL) {
          sprintf(buffFileName, "%s", token);
          token = strtok(NULL, "/");
        }
     ```
  * Jika ekstensi dari file tersebut telah didapatkan, maka ekstensi tersebut akan ditampilkan ke dalam ```buffer```.
  * Namun, jika terdapat sebuah file yang tidak memiliki ekstensi ```count <= 1``` maka ```buffer``` akan berisi __unknown__. Pengecekan terhadap file yang tidak memiliki ekstensi dilakukan oleh code berikut ini :
    ```bash
     if (count <= 1) {
        strcpy(buff, "unknown");
     }

     return buff;
     ```  
  * Kemudian, dilakukan pembuatan direktori baru dengan fungsi ```mkdir( )``` yang berada didalam fungsi ```void dirChecking``` di bawah ini :
    ```bash
    void dirChecking(char buff[]) {
      DIR *dr = opendir(buff);
      if (ENOENT == errno) {
        mkdir(buff, 0775);
        closedir(dr);
      }
    }
    ```
    Nama direktori baru tersebut sesuai dengan nama yang tersimpan dalam ```buffer```.
  * Lalu, program akan melakukan pengecekan terhadap eksistensi dan bentuk file sesuai dengan argumen yang diinputkan oleh _user_
    ```bash
    if (access(buffFrom, F_OK) == -1) {
      printf("File %s tidak ada\n", buffFrom);
      pthread_exit(0);
    }
    DIR* dir = opendir(buffFrom);
    if (dir) {
      printf("file %s berupa folder\n", buffFrom);
      pthread_exit(0);
    }
    closedir(dir);
    ```
  * Pemanggilan terhadap fungsi ```getFileName( )``` yang mendapatkan nama file dengan nama file yang tersimpan dalam ```buffer``` kemudian ke ```buffFileName```. Selain itu, juga dilakukan pemanggilan terhadap fungsi ```getExtension( )``` untuk mengambil setiap __ext__ yang berada di ```buffFrom```.
  * Dalam fungsi ```main``` terdapat beberapa fungsi untuk melakukan pengecekan untuk setiap argumen yang diinputkan. 
    ```bash 
    int main(int argc, char *argv[]) {
      if (argc == 1) {
        printf("Argument kurang\n");
        exit(1);
      }
    ```
    Code di atas akan menampilkan __"Argumen Kurang"__ apabila argumen yang diberikan tidaklah berjumlah dua argumen. Dalam program ini, _user_ diminta untuk menginputkan dua argumen yakni ```argc``` dan ```argv```.
  * Selain itu, apabila argumen yang diinputkan oleh _user_ tidak sesuai dengan ketentuan argumen yang diminta oleh soal maka program akan menampilkan bahwa __"Argumen tidak ada"__ atau __"Argumen salah"__. Code berikut untuk argumen ```-f``` dan argumen ```*```:
    ```bash
    if (strcmp(argv[1], "-f") != 0 && strcmp(argv[1], "*") != 0 && strcmp(argv[1], "-d")) {
      printf("Argument tidak ada\n");
      exit(1);
    }

    if (strcmp(argv[1], "-f") == 0) {
      if (argc <= 2) {
        printf("Argument salah\n");
        exit(1);
    }
    pthread_t tid[argc-2];
    for (int i = 2; i < argc; i++) {
      pthread_create(&tid[i-2], NULL, &routine, (void *)argv[i]);
    }
    for (int i = 2; i < argc; i++) {
      pthread_join(tid[i-2], NULL);
    }
    exit(0);
    }

    char *directory;
    if (strcmp(argv[1], "*") == 0) {
      if (argc != 2) {
        printf("Argument salah\n");
        exit(1);
      }
    ```
    Dalam code di atas juga dilakukan pembuatan __thread__.
  * Untuk code berikut ini untuk argumen ```-d``` :
    ```bash
    if (strcmp(argv[1], "-d") == 0) {
      if (argc != 3) {
        printf("Argument salah\n");
        exit(1);
      }
      DIR* dir = opendir(argv[2]);
      if (dir) {
        directory = argv[2];
      } else if (ENOENT == errno) {
        printf("Directory tidak ada\n");
        exit(1);
      }
      closedir(dir);
    }
    ```
    Selain hal di atas, digunakan _handler_ untuk argumen ```*``` dan argumen ```-d```. ```opendir( )``` akan membuka setiap direktori dan kemudian dimasukkan ke dalam variabel ```dir``` agar nantinya dapat dilakukan pengecekan. 
  * Perlu diketahui bahwa untuk menyimpan _absolute path_ dan variabel iterasi, kita telah membuat ```buffer```. Nilai ```tid``` telah diatur sejumlah nilai pada ```counter``` per direktori untuk thread yang dibuat.
    ```bash
    pthread_t tid[file_count];
    char buff[file_count][1337];
    int iter = 0;

    dir = opendir(directory);
    while ((entry = readdir(dir)) != NULL) {
      if (entry->d_type == DT_REG) {
        sprintf(buff[iter], "%s/%s", directory, entry->d_name);
        iter++;
      }
    }
    closedir(dir);
    ```
  * Akan terus terjadi proses _Looping_ sejumlah file yang telah tersimpan di dalam ```buffer```. Perlu diingat bahwa sebelum menjalankan program ini pada thread, kita harus melakukan penyimpanan _absolute path_ dari setiap file. Dan pada code berikut ini juga terdapat code untuk membuat thread yakni ```pthread_create(&tid[i], NULL, &routine, (void *)test);```
    ```bash 
    for (int i = 0; i < file_count; i++) {
      char  *test = (char*)buff[i];
      printf("%s\n", test);
      pthread_create(&tid[i], NULL, &routine, (void *)test);
    }
    ```
  * Pada akhir code terdapat pula proses _Looping_ yang akan melakukan proses _join_ untuk setiap thread yang telah dibuat.
    ```bash
    for (int i = 0; i < file_count; i++) {
      pthread_join(tid[i], NULL);
    }
    ```
#### Output :
  ![modul3-soal3](https://user-images.githubusercontent.com/49342639/79041530-ce476200-7c1a-11ea-9cdb-3b492434e797.jpg)
    
### Soal 4
* #### Soal 4A
  Buatlah program C yang berisi program untuk melakukan perkalian dua buah matriks dengan ketentuan berikut ini : <br>
  A. Matriks pertama berordo __4 x 2__ <br>
  B. Matriks kedua berordo __2 x 5__ <br>
  C. Kedua matriks tersebut berisi angka 1 - 20 <br>
  #### Code : https://github.com/rindikar/SoalShiftSISOP20_modul3_T17/blob/master/FIX-soal4/4a.c
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
    ```
  * Membuat Shared Memory ID sesuai dengan key yang telah ditentukan ```key_t key = 1337;``` yakni ```1337```.
  * _Code_ berikut akan membuat Shared Memory ```shmid``` dengan _size_ dari matriks C ```sizeof(matC)``` dengan ```key``` _private key_ (kunci pribadi) dan pada Shared Memory ini mengizinkan adanya ```0666``` _read and write_. 
    ```bash
    int shmid = shmget(key, sizeof(matC), IPC_CREAT | 0666);
    ```
  * Shared Memory berhasil dialokasikan, tetapi belum menjadi bagian dari _Address Space_. Oleh karena itu, kita gunakan ```shmat``` untuk menjadikan Shared Memory tersebut bagian dari _Address Space_. 
    ```bash
    value = shmat(shmid, NULL, 0);
    ```
  #### Output :
  ![modul3-4a](https://user-images.githubusercontent.com/49342639/79041683-d2c04a80-7c1b-11ea-866c-bd3a02a030be.jpg)
  
* #### Soal 4B
  #### Code : https://github.com/rindikar/SoalShiftSISOP20_modul3_T17/blob/master/FIX-soal4/4b.c
  #### Penyelesaian :
  * Untuk mendukung jalannya program ini, pasti kita menggunaka _Library_ berikut ini :
    ```bash
    #include <stdio.h>
    #include <pthread.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    ```
  * Kemudian, karena pada program __soal 4b__ ini berhubungan dengan program pada __soal 4a__ karena pada program __soal 4b__ ini akan mengambil matriks hasil perkalian yang telah kita dapatkan dari program pada __soal 4a__ di atas. Oleh karena itu, kita inisialisasikan terlebih dahulu sebuah matriks yang merupakan matriks hasil perkalian dari program __soal 4a__ dengan ```int matrix[4][5];``` dan sebuah matriks lagi yang akan menampilkan hasil faktorialnya ```long hasil[4][5];```.
    ```bash
    int matrix[4][5];
    long hasil[4][5];
    ```
 * Setelah inisialisasi matriks selesai, kita berikan struct yang berguna untuk _passing_ data ke dalam thread
    ```bash
    struct args {
      int i;
      int j;
    };
    ```
 * Struct yang telah kita buat di atas akan kita passing ke dalam ```void *``` dan kemudian akan dilanjutkan untuk dimasukkan ke dalam fungsi untuk mencari hasil faktorialnya.
    ```bash
    void *factorial(void* arg) {
      int i = ((struct args*)arg)->i;
      int j = ((struct args*)arg)->j;
      long hasilEl = 1;
      for (int n = 1; n <= matrix[i][j]; n++) hasilEl += (long)n;
      hasil[i][j] = hasilEl;
    }
    ```
  * Membuat Shared Memory ID sesuai dengan key yang telah ditentukan ```key_t key = 1337;``` yakni ```1337```.
  * _Code_ berikut akan membuat Shared Memory ```shmid``` dengan _size_ dari matriks C ```sizeof(matC)``` dengan ```key``` _private key_ (kunci pribadi) dan pada Shared Memory ini mengizinkan adanya ```0666``` _read and write_. 
    ```bash
    int shmid = shmget(key, 80, IPC_CREAT | 0666);
    ```
  * Shared Memory berhasil dialokasikan, tetapi belum menjadi bagian dari _Address Space_. Oleh karena itu, kita gunakan ```shmat``` untuk menjadikan Shared Memory tersebut bagian dari _Address Space_. 
    ```bash
    value = shmat(shmid, NULL, 0);
    ```
  * Dalam fungsi ```main``` terdapat ``` pthread_t tid[4][5];``` yang menunjukkan array dari thread bernama __tid__ yakni dengan _size_ __4 x 5__.
  * Banyak fungsi yang terdapat dalam ```main```, untuk _code_ berikut ini :
    ```bash
    for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      struct args *index = (struct args *)malloc(sizeof(struct args));
      index->i = i;
      index->j = j;
      pthread_create(&tid[i][j], NULL, &factorial, (void *)index);
    }
  }
    ```
   Pada ```struct args *index = (struct args *)malloc(sizeof(struct args));```ini akan membuat _object_ dari ```struct args``` bernama __index__ dan sekaligus melakukan pengalokasian memori sebesar _size_ dari ```struct args```. <br>
    Setelah pengalokasian memori, ```index->i = i;``` akan mengatur nilai i pada _object_ dari ```struct args``` bernama __index__ dengan __nilai i__. Hal ini juga dilakukan pada nilai j, ``` index->j = j;``` yang akan mengatur nilai j pada _object_ dari ```struct args``` bernama __index__ dengan __nilai j__. <br>
    Kemudian, ```pthread_create(&tid[i][j], NULL, &factorial, (void *)index);``` membuat thread pada array dari thread bernama __tid__ pada __nilai i__ dan __nilai j__ dengan memanggil fungsi __factorial__ dengan parameter __index__. <br>  
 * Dilanjutkan dengan menggabungkan semua thread yang ada 
    ```bash
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        pthread_join(tid[i][j], NULL);
      }
    }
    ```
  * Hasil factorial dari matriks hasil perkalian pada program __soal 4a__ akan ditampilkan pada layar
    ```bash
    printf("Matriks :\n");
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
          printf("%20ld", hasil[i][j]);
        }
        printf("\n");
      }

    }
    ```
  #### Output : 
  ![modul3-4b](https://user-images.githubusercontent.com/49342639/79042140-66dfe100-7c1f-11ea-8fbe-f9f2145c0851.jpg)
  
* #### Soal 4c
  Buatlah program C yang akan mengetahui jumlah file yang berada pada suatu folder di direktori saat kita menjalankan program ini dengan menggunakan ```ls | wc -1``` dimana program ini tidak berhubungan dengan program yang diminta pada soal 4A dan 4B di atas. Program ini memiliki satu ketentuan yakni : <br>
  A. Harus menggunakan __IPC Pipes__
  #### Code : https://github.com/rindikar/SoalShiftSISOP20_modul3_T17/blob/master/FIX-soal4/4c.c
  #### Penyelesaian :
  * Untuk mendukung jalannya program ini, kita tidak lupa untuk menggunakan _Library_ di antaranya sebagai berikut :
    ```bash
    #include<stdio.h>
    #include<stdlib.h>
    #include<unistd.h>
    #include<sys/types.h>
    #include<string.h>
    #include<sys/wait.h>
    ```
  * Dikarenakan adanya ketentuan untuk menggunakan __IPC Pipes__, maka kita perlu mendeklarasikan pipes tersebut 
    ```bash
    int main() {
    int fd[2];
    ```
    ```fd``` merupakan _file descriptor_, lalu _file descriptor_ harus berjumlah 2 karena pipes hanya memiliki 2 ujung yakni __ujung 0__ untuk fungsi _read_ dan __ujung 1__ untuk fungsi _write_.
  * Lalu, pada code di bawah ini :
    ```bash
     pid = fork();
     if (pid == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
      }
      while(wait(NULL) > 0);

      dup2(fd[0], 0);
      close(fd[1]);
      char *argv[] = {"wc", "-l", NULL};
      execv("/usr/bin/wc", argv);

      }
      ```
      Fungsi ```dup2( )``` berfungsi untuk melakukan penduplikasian _file descriptor_ yang terbuka ke _desciptor_ yang lain. Sehingga pada command ```dup2(fd[1], 1);``` berfungsi untuk melakukan duplikasi output / _copy_ output. Tidak lupa juga untuk menutup kedua _file descriptor_ yaitu pada _read(0)_ ```close(fd[0]);``` dan _write(1)_ ```close(fd[1]);```. Untuk menampilkan hasil yang telah dibaca pada direktori tersebut digunakan ```execv("/bin/ls", argv);```.<br>
      Kemudian, input pada 0 diganti dengan iput dari pipes ```dup2(fd[0], 0);```. Dan tidak lupa juga untuk menutup kedua _file descriptor_ yaitu pada _read(0)_ ```close(fd[0]);``` dan _write(1)_```close(fd[1]);```. Selanjutnya, melakukan fungsi ```execv("/usr/bin/wc", argv);```.
  #### Output :  
  ![modul3-4c](https://user-images.githubusercontent.com/49342639/79041605-4a41aa00-7c1b-11ea-9403-6f5fc56483c2.jpg)
     
