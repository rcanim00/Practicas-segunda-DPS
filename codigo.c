#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 50
pthread_mutex_t lock;

void* worker(void* arg) {
    // Retraso para que el Main destruya el mutex antes que los hilos lleguen aquí
    usleep(100); 
    if (pthread_mutex_lock(&lock) == 0) {
        printf("Hilo %ld dentro\n", (long)arg);
        pthread_mutex_unlock(&lock);
    } else {
        printf("Error: Mutex inválido o destruido.\n");
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    for (long i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, worker, (void*)i);

    // VIOLACIÓN CON31-C: Destrucción masiva prematura
    //pthread_mutex_destroy(&lock); 
    //printf("[MAIN] Mutex DESTRUIDO mientras hilos siguen activos.\n");

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
  
    pthread_mutex_destroy(&lock); 
    return 0;
}
