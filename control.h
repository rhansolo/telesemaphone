#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_KEY 123456
#define FILE_KEY 234567
#define SHM_SEM 0
#define FILE_SEM 1
#define SHM_SIZE 201
