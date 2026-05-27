#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* Types */
typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define Word char
#define Byte unsigned char

/* RNG */
void rng_init(void); // picks a random seed
int random_int(int min, int max); //returns a random intiger

/* Memory */
void *balloc(size_t size); //Malloc but with automatic memory safeguards and arena tracking, Balloc(size_t size);
void *bcalloc(size_t count, size_t size);//calloc but with automatic memory safeguards and arena tracking, bcalloc(size_t size);
void *brealloc(void *ptr, size_t size);//realloc but with automatic memory safeguards and arrena tracling brealloc(void *ptr, size_t size);
void bfree(void *ptr);//URGENT: do NOT pass NULL accidently. it will free ALL your arena tracked pointers. basicly the free function, but iff you pass null to it it frees all the tracked pointers
void arena_track(void *ptr);//puts pointers into the arena list, dont need to do anythşng if you use BCD memory functions
void arena_free_all(void);//frees all pointers in arena, dont need to do anything if you just put null into bfree
void arena_track_realloc(void *oldptr, void *newptr);//arena track for brealloc
/* I/O */
char *ReadStringFromUser(size_t cap);//reads string from user, returns pointer to character array ReadStringFromUSer(size_T cap);
void swap_int(int *a, int *b); //swaps 2 intigers. swap_int(int *a, int *b);

/* Helpers */
int sizeofbyte(int howmanybytes); // takes size of byte, unnecesery since size of byte is alredy one. sizeofbyte(int howmanybytes),

/* Macros */
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(x, lo, hi) (MIN(MAX((x), (lo)), (hi)))
#define balloc_array(type, count) ((type *)balloc((count) * sizeof(type)))


/*typedef,define list*/
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    f32;
typedef double   f64;
#define null NULL;


