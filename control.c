#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>

union semun{
  int val ;
  struct semid_ds *buf;
  unsigned short * array;
  struct seminfo *_buf;
};

int main(int argc, char * argv []){
  int key = ftok("control.c",12);
  int semkey;
  int shmkey;
  int semconfig;
  int shmconfig;
  int fd;
  if(strcmp(argv[1],"-c") == 0){
    shmkey = shmget(key, 1024 ,IPC_CREAT | IPC_EXCL | 0644);
    semkey = semget(key, 1 , IPC_CREAT | IPC_EXCL | 0644);
    fd = open("./story.txt", O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0644);
    union semun su;
    semconfig = semctl( semkey, 0 ,SETVAL, su);
    su.val = 1;
    printf("Works\n");
  }
  else if(strcmp(argv[1], "-r") == 0 ){
    char story [100000];
    shmkey = shmget(key , 1024, 0);
    semkey = semget(key , 1 , 0);
    fd = open("./story.txt", O_RDONLY, 0644);
    shmconfig = shmctl(shmkey, IPC_RMID, 0);
    semconfig = semctl(semkey, 0, IPC_RMID);
    int bytes = read (fd, story, 99999);
    printf("%s\n", story);
  }
  else if(strcmp(arg[1] , "-v") == 0){
    char story [100000];
    fd = open ("./story.txt", O_RDONLY,0644);
    int bytes = read(fd ,story ,99999);
    printf("%s\n",story);
  }
    
    
}
