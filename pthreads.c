#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define M 1000
#define K 1000
#define N 1000
#define NUM_THREADS 4

int A[M][K];
int B[K][N];
int C[M][N];

typedef struct {
    int thread_id;
} thread_data;

void *matrix_multiply_thread(void *arg) {
    thread_data *data = (thread_data *)arg;
    int thread_id = data->thread_id;
    int rows_per_thread = M / NUM_THREADS;
    int start_row = thread_id * rows_per_thread;
    int end_row = (thread_id + 1) * rows_per_thread;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Initialize input matrices
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            A[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = rand() % 100;
        }
    }

    // Calculate serial time
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end_time, NULL);
    double serial_time = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Serial time: %f seconds\n", serial_time);

    // Initialize pthreads
    pthread_t threads[NUM_THREADS];
    thread_data data[NUM_THREADS];
    gettimeofday(&start_time, NULL);

    // Create threads
    for (int t = 0; t < NUM_THREADS; t++) {
        data[t].thread_id = t;
        pthread_create(&threads[t], NULL, matrix_multiply_thread, (void *)&data[t]);
    }

    // Join threads
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    gettimeofday(&end_time, NULL);
    double execution_time_1 = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    double speedup_1 = serial_time / execution_time_1;
    double efficiency_1 = speedup_1 / 1.0;
    printf("Execution time with 1 thread: %f seconds\n", execution_time_1);
    printf("Speedup with 1 thread: %f\n", speedup_1);
    printf("Efficiency with 1 thread: %f\n",efficiency_1);
    gettimeofday(&start_time, NULL);
for (int t = 0; t < NUM_THREADS; t++) {
    data[t].thread_id = t;
    pthread_create(&threads[t], NULL, matrix_multiply_thread, (void *)&data[t]);
}
for (int t = 0; t < NUM_THREADS; t++) {
    pthread_join(threads[t], NULL);
}
gettimeofday(&end_time, NULL);
double execution_time_2 = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
double speedup_2 = serial_time / execution_time_2;
double efficiency_2 = speedup_2 / 2.0;
printf("Execution time with 2 threads: %f seconds\n", execution_time_2);
printf("Speedup with 2 threads: %f\n", speedup_2);
printf("Efficiency with 2 threads: %f\n", efficiency_2);

// Test with 3 threads
gettimeofday(&start_time, NULL);
for (int t = 0; t < NUM_THREADS; t++) {
    data[t].thread_id = t;
    pthread_create(&threads[t], NULL, matrix_multiply_thread, (void *)&data[t]);
}
for (int t = 0; t < NUM_THREADS; t++) {
    pthread_join(threads[t], NULL);
}
gettimeofday(&end_time, NULL);
double execution_time_3 = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
double speedup_3 = serial_time / execution_time_3;
double efficiency_3 = speedup_3 / 3.0;
printf("Execution time with 3 threads: %f seconds\n", execution_time_3);
printf("Speedup with 3 threads: %f\n", speedup_3);
printf("Efficiency with 3 threads: %f\n", efficiency_3);

return 0;
}
