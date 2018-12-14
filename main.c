#include "control.h"

int main() {
    int segCreated = 0;
    int shmid;
    char *data;
    if ((shmid = shmget(SHM_KEY, SHM_SIZE, 0)) == -1) {
        printf("the shared memory segment has yet to be created\n");
        exit(1);
    }
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        printf("pointer failed to attach to segment\n");
        exit(1);
    }
    if (strcmp(data, "")) {
        printf("you last entered:  %s\n", data);
        segCreated= 1;
    }
    printf("what would you like to add?:\n");
    char input[SHM_SIZE];
    fgets(input, SHM_SIZE, stdin);
    input[strlen(input) - 1] = 0;
    int storyFile = open("story.txt", O_WRONLY, 0);
    if (storyFile == -1) {
        printf("file didn't open");
        exit(1);
    } 
    int shmsemd = semget(SHM_KEY, 2, 0);
    struct sembuf instr;
    instr.sem_num  = SHM_SEM;
    instr.sem_op = -1;
    instr.sem_flg = SEM_UNDO;
    semop(shmsemd, &instr, 1);
    strncpy(data, input, SHM_SIZE); 
    instr.sem_op = 1;
    semop(shmsemd, &instr, 1);
    int fsemd = semget(SHM_KEY, 2, 0);
    struct sembuf finstr;
    finstr.sem_num  = SHM_SEM;
    finstr.sem_op = -1;
    finstr.sem_flg = SEM_UNDO;
    semop(fsemd, &finstr, 1);
    if (lseek(storyFile, 0, SEEK_END) == -1) {
        printf("something happened");
        exit(1);
    }
    if (segCreated) {
        write(storyFile, "\n", 1);
    }
    write(storyFile, data, strlen(input));
    finstr.sem_op = 1;
    semop(fsemd, &finstr, 1);
}
