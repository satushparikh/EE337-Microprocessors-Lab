#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TESTS 1000000

long unsigned int p[2], q[2], r[3];
long unsigned int answer;
long unsigned int param[2];
long unsigned int p1, q1;

int main()
{
    double total_time = 0;
    srand(time(NULL));
    clock_t start = clock();
    for (int i = 0; i < NUM_TESTS; i++)
    {
        p1 = rand() % 10000 + 1;
        q1 = rand() % 10000 + 1;

        p[1] = p1 / 10;
        p[0] = p1 % 10;

        q[1] = q1 / 10;
        q[0] = q1 % 10;

        r[0] = p[0] * q[0];
        r[1] = (p[0] + p[1]) * (q[0] + q[1]);
        r[2] = p[1] * q[1];

        answer = r[0] + (r[1] - r[0] - r[2]) * 10 + r[2] * 100;

        
    }
    clock_t end = clock();
    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    // double average_time = total_time / NUM_TESTS;

    printf("Average time taken: %.8f seconds\n", time_elapsed);
    return 0;
}
