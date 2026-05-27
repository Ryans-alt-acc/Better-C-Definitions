#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

void *balloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "balloc: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void wait(int secconds){time_t start = time(NULL);
while (time(NULL) - start < secconds);}

void printfd(int intiger){printf("%d", intiger);}





