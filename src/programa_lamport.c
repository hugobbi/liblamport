#include "headers/liblamport.h"
#include "headers/constants.h"
#include <pthread.h>

int a = 0;

static void * thread_process(void *arg)
{
        int i, j = *((int *) arg); 
        printf("Hello! I'm thread %d!\n", j);
        
        //dormir();
        lamport_mutex_lock(j);
        printf("I'm thread %d and I'm entering my critical region!\n", j);        
        for(i = 0 ; i < 3000000 ; i++){
            a++;
        }
        printf("%d\n", a);
        printf("I'm thread %d and I'm leaving my critical region!\n", j);
        lamport_mutex_unlock(j);
}

int main(int argc, char **argv)
{
    int thread_num, ret;
    pthread_t tinfo_process[N];
    int tinfo_id[N];
    pthread_attr_t attr;
    int *res;
    
    ret = pthread_attr_init(&attr);

    lamport_mutex_init();
    
    for (thread_num = 0; thread_num < N; thread_num++) {
	    tinfo_id [thread_num] = thread_num;
	    ret = pthread_create(&tinfo_process[thread_num], &attr, &thread_process, &tinfo_id[thread_num]);
    }

    ret = pthread_attr_destroy(&attr);
    
    for (thread_num = 0; thread_num < N; thread_num++) {
    	ret = pthread_join(tinfo_process[thread_num], NULL);
    	printf("Joined with thread id %d\n", thread_num);

    	//free(res);
    }

    exit(EXIT_SUCCESS);
}