#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
int i_g = 0;

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
void* routine(void* arg) {
    sleep(1);
    int index = *(int*)arg;
    printf("%d ", primes[index]);
    free(arg);
    i_g++;
    //if (i_g == 10)
    // pthread_mutex_lock(&lock1);

    // pthread_mutex_lock(&lock1);
    return (NULL);
}

int main(int argc, char* argv[]) {
    pthread_t th[10];
    int i;
    for (i = 0; i < 10; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
        {
            perror("Failed to created thread");
        }
    }
    //pthread_mutex_lock(&lock1);
    // printf("dude");
    /* for (i = 0; i < 10; i++)
	{
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    } */    
    return 0;
}