#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int row_sum(int * element, int n) {
        int i, sum = 0;
        for (i=0; i < n; i++)
                sum += element[i];
        return sum;
}

int col_sum(int * element, int n) {
        int i, sum = 0, nn = n*n;
        for (i=0; i < nn; i+=n)
                sum += element[i];
        return sum;
}

int diag_sum(int * element, int n, int fwd) {
        int i, sum = 0, nn = n*n;
        if (fwd) {
                for (i=(n-1)*n; i == n-1; i=i-n+1) {
                        sum += element[i];
                }
        } else {
                for (i=0; i < nn; i=i+n+1) {
                        sum += element[i];
                }
        }
        return sum;
}

int *gen_magic_sqr(int n) {

        if ((n < 3) || (7 < n)) {
                printf("Select dimension n, where 2 < n < 8\nDefault is 3\n");
        }


        // allocate n*n array of int
        int * a = calloc(n*n, sizeof(int));

        if (!a) return a;

        // randomize prng seed
        int seed = (int) getpid();
        printf("Random number seed is %d.\n", seed);
        srand(seed);

        int * p = a;
        int nn = n * n;
        int m = (n * (nn + 1)) / 2;
        printf("Magic sum for %d*%d square is %d.\n", n, n, m);

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int row_sum(int * element, int n) {
        int i, sum = 0;
        for (i=0; i < n; i++)
                sum += element[i];
        return sum;
}

int col_sum(int * element, int n) {
        int i, sum = 0, nn = n*n;
        for (i=0; i < nn; i+=n)
                sum += element[i];
        return sum;
}

int diag_sum(int * element, int n, int fwd) {
        int i, sum = 0, nn = n*n;
        if (fwd) {
                for (i=(n-1)*n; i == n-1; i=i-n+1) {
                        sum += element[i];
                }
        } else {
                for (i=0; i < nn; i=i+n+1) {
                        sum += element[i];
                }
        }
        return sum;
}

int *gen_magic_sqr(int n) {

        if ((n < 3) || (7 < n)) {
                printf("Select dimension n, where 2 < n < 8\nDefault is 3\n");
        }


        // allocate n*n array of int
        int * a = calloc(n*n, sizeof(int));

        if (!a) return a;

        // randomize prng seed
        int seed = (int) getpid();
        printf("Random number seed is %d.\n", seed);
        srand(seed);

        int * p = a;
        int nn = n * n;
        int m = (n * (nn + 1)) / 2;
        printf("Magic sum for %d*%d square is %d.\n", n, n, m);

        // populate the magic square by picking random numbers in range [1,n*n]
        // numbers cannot appear more than once
        // sum each row, column, or diagonal as soon as it is filled
        // if sum not equal to magic sum, start over
        // (not an efficient method because of retries and backtracking)

        volatile int i = 0;
        int j;
        time_t duration = time();
        while (i < nn) {
                // pick random integer in range [1,nn]
                a[i] = rand() % nn + 1;

                for (j = 0; j < i; j++) {
                        if (a[j] == a[i]) continue;
                }

                if (n-1 == i / n) {
                        j = i % n;
                        if (0 == j) {
                                // completed "forward" diagonal
                                if (diag_sum( &a[i], n, 1 ) != m) {
                                        // start over
                                        i = 0;
                                        continue;
                                }

                        } else if (n-1 == j) {
                                // completed other diagonal
                                if (diag_sum( &a[i], n, 0 ) != m) {
                                        // start over
                                        i = 0;
                                        continue;
                                }
                        }

                        // completed a column
                        if (col_sum( &a[i%n], n ) != m) {
                                // start over
                                i = 0;
                                continue;
                        }
                }

                i++;

                if (0 == i % n) {
                        // completed a row
                        if (row_sum( &a[i-n], n ) != m) {
                                // start over
                                i = 0;
                                continue;
                        }
                }
        }
        duration = time() - duration;
        printf("Generation time was %ul seconds.\n", (unsigned int)duration);

        return a;
}


int main(int argc, char **argv) {

        int n = 3;              // dimension of the magic square (default 3)
        int *sqr=NULL;          // n*n magic square

        if (1 < argc) {
                n = strtol(argv[1], NULL, 10);
                printf("Generate a magic square of dimension %d\n", n);
        }
        sqr = gen_magic_sqr(n);

        if (sqr) {
                int i, nn = n*n;
                int *p;
                for (p=sqr, i=0; i < nn; i++, p++) {
                        printf("%d,", *p);
                        if (n-1 == i % n)
                                printf("\n");
                }
        }
        return 0;
}
