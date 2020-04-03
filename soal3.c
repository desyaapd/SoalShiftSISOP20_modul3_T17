#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<pthread.h>
#include<sys/wait.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

#define MAX 256
 

static void NamaFileStrip(char *NamaFile, char *NamaFileBaru, char *ext);
void* buatDir(void *data);
void* move(void *data);
void* thread(void *arg);

//struct

struct var
{
    char *nf[1];
    char *e[1];
    char *p[1];
    char *pa[1];
};


//Global Variable


int status;
pthread_t tid[3];


int main(int argc, char* argv[])
{
    // Declare variable
    char ext[5];
    char NamaFile[31];
    char NamaFileBaru[31];
    char pathawal[50];
    char pathakhir[50];
    char star[] = "*";
    char f[] = "-f";
    char d[] = "-d";

    int i = 2;

    //Arg = -f
    if (strcmp (argv[1],f) == 0)
    {
        //Looping arg
        for (; i < argc; i++)
        {
            //Memory Set
            memset(ext, 0, sizeof(ext));
          
            memset(NamaFile, 0, sizeof(NamaFile));
            memset(NamaFileBaru, 0, sizeof(NamaFileBaru));
    
            memset(pathawal, 0, sizeof(pathawal));
            memset(pathakhir, 0, sizeof(pathakhir));

            //Cari File Path dant Ext
            strcpy(NamaFile, argv[i]);
            NamaFileStrip(NamaFile, NamaFileBaru, ext);
            strcat(NamaFileBaru, ",");
            strcat(NamaFileBaru, ext);
            strcat(pathawal, "/home/xd/Desktop/Modul3/shift/");
            strcat(pathawal, NamaFileBaru);
            strcat(pathakhir, "/home/xd/Desktop/Modul3/");
            strcat(pathakhir, ext);
            strcat(pathakhir, "/");
            strcat(pathakhir, NamaFileBaru);

            // ditaruh dalam struct
            struct var *data = (struct var*) malloc (sizeof (struct var));
            
            *data -> e = ext;
            *data -> nf = NamaFileBaru;
            *data -> pa = pathakhir;
            *data -> p = pathawal;

            int t = 0;
            status = 0;

            //membuat thread
            while (t<2)
            {
                if(t==0){
                    pthread_create(&(tid[t]),NULL,&buatDir,(void *) data);
                } else {
                    pthread_create(&(tid[t]),NULL,&move,(void *) data);
                }
                pthread_join(tid[t],NULL);
                t++;
            }
        }
    }

     if (strcmp (argv[1],d) == 0)
    {

    }

    else (strcmp (argv[1],star) == 0)
    {

    }
 
 
    return 0;
}
 
static void NamaFileStrip(char *NamaFile, char *NamaFileBaru, char *ext)
{
    int PLocation;
    int i, j, nf, e, p;
 
    i = strlen(NamaFile) - 1;
 
    //Cari periode nama file awal
    while (i && NamaFile[i] != '.')
    {
        i--;
    }
 
    // if i > 0, Nama file ada periode
    if (i)
    {
        PLocation = i;
    }
    else
    {
        //Ga ad periode jd copynamafile
        PLocation = strlen(NamaFile);
 
        //Reset i untuk nyari separator
        i = strlen(NamaFile) - 1;
    }
 
    //Cari separator
    while (i && NamaFile[i] != '/')
    {
        if (NamaFile[i] != '/')
            i--;
    }
 
    //Kalo ga ad separatornya  mundur 1 char
    if (NamaFile[i] == '/')
        i++;
         
    nf = 0;
    
    //Copy file yang dari setelah separator
    while (i < PLocation)
    {
        NamaFileBaru[nf] = NamaFile[i];
        nf++;
        i++;
    }
    
    //copy ekstensi

    e = 0;
    j = strlen(NamaFile) - 1;
    while (i<j)
    {
        ext[e] = NamaFile[i+1];
        e++;
        i++;
    }
    
    NamaFileBaru[nf] = '\0';
    ext[e] = '\0';
}

void* buatDir(void *parameter)
{
    struct var *par = (struct var*) parameter;

    status = 1;

    mkdir(*par->e, 0777);

	return NULL;
}

void* move(void *parameter)
{
    struct var *par = (struct var*) parameter;

    while (status != 1)
    {

    }
    
    int ch;
    FILE *fp1, *fp2;

    fp1 = fopen(*par->p, "r");
    fp2 = fopen(*par->pa, "w");

    //ERRROR
    if (!fp1) {
            printf("Unable to open source file to read!!\n");
            fclose(fp2);
            return 0;
    }
    if (!fp2) {
            printf("Unable to open target file to write\n");
            return 0;
    }
    //Copy isi file ke target file
    while ((ch = fgetc(fp1)) != EOF) {
            fputc(ch, fp2);
    }

    //Tutup File
    fclose(fp1);
    fclose(fp2);
    //Remove source file
    remove(*par->p);

	return NULL;
}