#include "control.h"

union semun {
    int val;
    struct semid_ds *buf; 
    unsigned short *array;
    struct seminfo *__buff;
};

int main(int argc, char *argv[]){
    char arg[5];
    int shmid;
    int shsemid;
    int fsemid;
    shsemid=semget(SHM_KEY,2,0);
    shmid=shmget(SHM_KEY, SHM_SIZE,0);
    if(argc<=1){
        printf("What function do you want to run? ");
        fgets(arg,5,stdin);
    }
    else{
        strncpy(arg,argv[1],5);
    }
    if(!strcmp(arg,"-c")){
        printf("Semaphore has been created\n");
        int storyfd=open("story.txt",O_CREAT, 0644);
        close(storyfd);
        shmid=shmget(SHM_KEY, SHM_SIZE, 0644 | IPC_CREAT);
        shsemid=semget(SHM_KEY,1,0644 | IPC_CREAT);
        fsemid=semget(FILE_KEY,1,0644 | IPC_CREAT);

        union semun s;
        s.val = 1;

        semctl(shsemid, 0, SETVAL, s);
        semctl(shsemid, 0, SETVAL, s);

    }
    if(!strcmp(arg,"-r")){
        printf("Semaphore has been removed\n");
        shmctl(shmid,IPC_RMID, NULL);
        printf("This was the story you removed: \n");
        int fd=open("story.txt",O_RDONLY);
        char * story=calloc(10000,sizeof(char));
        int readbytes=read(fd,story,10000);
        if(readbytes<0){
            printf("%s\n",strerror(errno));
        }
        printf("%s\n",story);
        close(fd);
        int storyfd=open("story.txt",O_TRUNC);
        close(storyfd);
        semctl(shsemid, 0, IPC_RMID);
        semctl(fsemid, 0, IPC_RMID);
        free(story);
        remove("story.txt");
    }

    if(!strcmp(arg,"-v")){
        printf("This is the story: \n");
        int fd=open("story.txt",O_RDONLY);
        char *story=calloc(10000,sizeof(char));
        int readbytes=read(fd,story,10000);
        if(readbytes<0){
            printf("%s\n",strerror(errno));
        }
        printf("%s\n",story);
        close(fd);
        free(story);
    }


}