#include<stdio.h>
#include<sys/shm.h>
#include<pthread.h>
#include<sys/ipc.h>
#include<stdlib.h>
#define X 4
#define Y 2
#define Z 5

#define NUM_THREADS X * Z

int (*value)[10];

int A[X][Y] = {{0,1},
               {2,3},
               {4,5},
               {6,7}
              };
int B[Y][Z] = {{1,1,1,1,1}, 
               {1,1,1,1,1}
              };
struct var
{
    //baris dan kolom
	int i;
	int j; 
};
void *runner(void *ptr);

int main(int argc, char **argv)
{
	int i, j;
	int thread_counter = 0;
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int[10][10]), IPC_CREATE | 0666);
    value = shmat(shmid, 0, 0);
    