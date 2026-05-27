#include "BCD.h"
#include <string.h>
#include <time.h>

//randomness

void rng_init(void) {
    static BOOL seeded = FALSE;
    if (!seeded) {
        srand((unsigned)time(NULL));
        seeded = TRUE;
    }
}

int random_int(int min, int max) {
    rng_init(); // fixed seeding thingy
    return min + rand() % (max - min + 1);
}

//memory 
static void **arena_list = NULL;
static size_t arena_cap = 0;
static size_t arena_len = 0;

void *balloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "balloc: out of memory\n");
        exit(EXIT_FAILURE);
    }
    arena_track(ptr);
    return ptr;
}

void *bcalloc(size_t count, size_t size) {
    void *ptr = calloc(count, size);
    if (!ptr) {
        fprintf(stderr, "bcalloc: out of memory\n");
        exit(EXIT_FAILURE);
    }
    arena_track(ptr);
    return ptr;
}

void *brealloc(void *ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    void *new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        fprintf(stderr, "brealloc: out of memory\n");
        exit(EXIT_FAILURE);
    }
    arena_track(ptr);
    return new_ptr;
}

void bfree(void *ptr) {
    if (ptr == NULL)
    {
        arena_free_all();
    }
    
    free(ptr);
}

void arena_track(void *ptr) { 
    if (arena_len >= arena_cap) {
        arena_cap = arena_cap == 0 ? 32 : arena_cap * 2;
        arena_list = realloc(arena_list, arena_cap * sizeof(void*)); 
    }
    arena_list[arena_len++] = ptr;
}
void arena_free_all(void) {
    for (size_t i = 0; i < arena_len; i++) {
        free(arena_list[i]);
    }
    free(arena_list);
    arena_list = NULL;
    arena_len = arena_cap = 0;
}


//input output

char *ReadStringFromUser(size_t cap) {
    char *buf = balloc(cap);

    if (!fgets(buf, cap, stdin)) {
        bfree(buf);
        return NULL;
    }

    size_t len = strlen(buf);

    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        len--;
    }

    return brealloc(buf, len + 1);
}

//macros and such

void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int sizeofbyte(int howmanybytes) {
    return howmanybytes * (int)sizeof(Byte);
}