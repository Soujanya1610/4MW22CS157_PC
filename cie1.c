#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int isPrime(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    int sqrtNum = (int)sqrt(num);
    for (int i = 3; i <= sqrtNum; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n = 20;
    int serialCount = 0;
    int parallelCount = 0;

    // Serial version
    double startSerial = omp_get_wtime();
    for (int i = 1; i <= n; i++) {
        if (isPrime(i)) {
            serialCount++;
        }
    }
    double endSerial = omp_get_wtime();

    // Parallel version with dynamic scheduling
    double startParallel = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:parallelCount)
    for (int i = 1; i <= n; i++) {
        if (isPrime(i)) {
            parallelCount++;
        }
    }
    double endParallel = omp_get_wtime();

    // Output results
    printf("n=%d\n",n);
    printf("Serial Count of primes = %d\n", serialCount);
    printf("Parallel Count of primes = %d\n", parallelCount);
    printf("Execution time (serial): %f seconds\n", endSerial - startSerial);
    printf("Execution time (parallel): %f seconds\n", endParallel - startParallel);

    return 0;
}