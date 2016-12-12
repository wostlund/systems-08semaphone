#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
  int key = ftok("control.c",12);
  int semid, shmid;
  int shmkey = shmget(key, 4, IPC_CREAT | 0644);
  semid = semget(key, 1, IPC_EXCL | IPC_CREAT | 0644);
  struct sembuf su;
  su.sem_num = 0;
  su.sem_flg = SEM_UNDO;
  su.sem_op = -1;
  semop(semid, &su, 1);
  int* shm = shmat(shmkey, 0, 0);
  int file = open("story.txt", O_CREAT | O_RDONLY, 0644);
  char str[*shm + 1];

  lseek(file, -(*shm), SEEK_END );
  read(file, str, *shm);

  printf("\nLast Line: %s\nAdd a New One: ", str);

  char *a = (char *) calloc(1, 256);
  fgets(a, 255, stdin);
  printf("%s", a);
  int f = open("story.txt", O_APPEND | O_RDWR, 0644);
  write(f, a, strlen(a));
  //printf("\n\n\n\n%d", *shm);
  *shm = strlen(a);

  su.sem_op = 1;
  semop(semid, &su, 1);

  return 1;
}
