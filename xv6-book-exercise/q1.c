// Chapter 1 Exercise
// 1. Write a program that uses UNIX system calls to “ping-pong” a byte between
// two processes over a pair of pipes, one for each direction. Measure the
// program’s performance, in exchanges per second.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
    long long count = 0;
    char buf;
    int parent_to_child[2];
    int child_to_parent[2];

    struct timeval start, end;
    gettimeofday(&start, NULL);

    pipe(parent_to_child);
    pipe(child_to_parent);
    switch (fork()) {
        case -1: {
            fprintf(stderr, "fork() failed");
        }
        case 0: {
            // childl process
            close(child_to_parent[0]);
            close(parent_to_child[1]);
            while (1) {
                write(child_to_parent[1], "x", 1);
                read(parent_to_child[0], &buf, 1);
            }
        }
        default: {
            // parent process
            close(parent_to_child[0]);
            close(child_to_parent[1]);
            while (1) {
                read(child_to_parent[0], &buf, 1);
                write(parent_to_child[1], "x", 1);
                count++;

                gettimeofday(&end, NULL);
                long ms = (end.tv_sec * 1000 + end.tv_usec / 1000) -
                          (start.tv_sec * 1000 + start.tv_usec / 1000);
                if (ms >= 1000) {
                    break;
                }
            }
        }
    }

    printf("%lld exchanges done\n", count);

    return 0;
}
