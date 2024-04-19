#include "lib.h"

/* Variaveis compartilhadas */
__mutex_thread mutex_data_structure[N];

int max_ticket() {
  int i, max = mutex_data_structure[0].ticket;
  for (i = 1; i < N; i++)
    max = mutex_data_structure[i].ticket > max ? mutex_data_structure[i].ticket : max;
}

void lamport_mutex_init() {
    int i;
    for(i = 0 ; i < N ; i++) {
        mutex_data_structure[i].choosing = 0;
        mutex_data_structure[i].ticket = 0;
    }
}

void lamport_mutex_lock(int thread_id) {
    int j;

    mutex_data_structure[thread_id].choosing = 1;
        mutex_data_structure[thread_id].ticket = max_ticket () + 1;
        mutex_data_structure[thread_id].choosing = 0;
    for (j = 0; j < N; j++) {
        while (mutex_data_structure[j].choosing) /* nao fazer nada */;
	    while (mutex_data_structure[j].ticket != 0 && ((mutex_data_structure[j].ticket < mutex_data_structure[thread_id].ticket) || (mutex_data_structure[j].ticket == mutex_data_structure[thread_id].ticket && j < thread_id))) /* nao fazer nada */;
     }
}

void lamport_mutex_unlock(int thread_id) {
    mutex_data_structure[thread_id].ticket = 0;
}
