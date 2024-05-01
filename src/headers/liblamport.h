#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define N 3

typedef struct __mutex_thread{
    int choosing;
    int ticket;
} __mutex_thread;

int max_ticket();

void lamport_mutex_init();

void lamport_mutex_lock(int thread_id);

void lamport_mutex_unlock(int thread_id);

