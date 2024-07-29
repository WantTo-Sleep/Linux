#pragma once
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define PATHNAME "/home/sjx/Linux/process_communicate/shared_memory"
#define PROJ_ID 12

int createShm(size_t size)
{
    umask(0);
    key_t key = ftok(PATHNAME, PROJ_ID);
    // printf("key: %d\n", key);
    int id = shmget(key, size, IPC_CREAT | IPC_EXCL | 0600);
    if (id == -1)
    {
        perror("createShm");
        exit(-1);
    }
    return id;
}

int getShm(size_t size)
{
    key_t key = ftok(PATHNAME, PROJ_ID);
    int id = shmget(key, size, IPC_CREAT);
    if (id == -1)
    {
        perror("createShm");
        exit(-1);
    }
    return id;
}
