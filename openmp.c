#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define M 1000
#define K 1000
#define N 1000

int A[M][K];
int B[K][N];
int C[M][N];

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

    // Set up timer
    struct timeval start_time, end_time;

    // Calculate serial time
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

    // Test with 1 processor
    omp_set_num_threads(1);
    gettimeofday(&start_time, NULL);
    #pragma omp parallel for
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end_time, NULL);
    double execution_time_1 = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    double speedup_1 = serial_time / execution_time_1;
    printf("Execution time with 1 processor: %f seconds\n", execution_time_1);
    printf("Speedup with 1 processor: %f\n", speedup_1);

    // Test with 2 processors
    omp_set_num_threads(2);
    gettimeofday(&start_time, NULL);
    #pragma omp parallel for
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end_time, NULL);
    double execution_time_2 = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    double speedup_2 = serial_time / execution_time_2;
    printf("Execution time with 2 processors: %f seconds\n", execution_time_2);
    printf("Speedup with 2 processors: %f\n", speedup_2);
// Test with 3 processors
omp_set_num_threads(3);
gettimeofday(&start_time, NULL);
#pragma omp parallel for
for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < K; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}
gettimeofday(&end_time, NULL);
double execution_time_3 = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
double speedup_3 = serial_time / execution_time_3;
printf("Execution time with 3 processors: %f seconds\n", execution_time_3);
printf("Speedup with 3 processors: %f\n", speedup_3);

// Calculate efficiency
double efficiency_1 = speedup_1 / 1.0;
double efficiency_2 = speedup_2 / 2.0;
double efficiency_3 = speedup_3 / 3.0;

printf("Efficiency with 1 processor: %f\n", efficiency_1);
printf("Efficiency with 2 processors: %f\n", efficiency_2);
printf("Efficiency with 3 processors: %f\n", efficiency_3);

return 0;
}
   
