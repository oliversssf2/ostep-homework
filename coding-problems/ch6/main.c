#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <stdio.h>


long measure_n_readzero(long n) {
    char buf;

    struct timeval begin_t;
    struct timeval end_t;

    int res = gettimeofday(&begin_t, NULL);
    assert(res == 0);    

    for (size_t i = 0; i < n; i++) {
        read(STDIN_FILENO, &buf, 0);        
    }

    res = gettimeofday(&end_t, NULL);
    assert(res == 0);

    long interval_usec = ((end_t.tv_sec - begin_t.tv_sec)*1000000) + (end_t.tv_usec - begin_t.tv_usec);
    return interval_usec;
}

int main(int argc, char* argv[]) {
    long tmp;
    long num_ops = 1;
    for (int i = 0; i < 20; i++) {
        num_ops = num_ops << 1;
        tmp = measure_n_readzero(num_ops);
        printf("It took %ld microseconds for %ld read zero operations\n", tmp, num_ops);
    }
    exit(EXIT_SUCCESS);
}