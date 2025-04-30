#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "union_find_tree.h"

#define NUM_ELEMENTS 100000
#define NUM_OPS      100000

double calc_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

void benchmark_union_find(uf_node_t*(*union_fn)(uf_node_t*, uf_node_t*), uf_node_t*(*find_fn)(uf_node_t*), int* u1, int* u2, int* f) {
    uf_node_t** sets = malloc(sizeof(uf_node_t*)*NUM_ELEMENTS);

    struct timespec start, end;

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        sets[i] = make_set(i);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < NUM_OPS; i++) {
        union_fn(sets[u1[i]], sets[u2[i]]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("union_sets: %f ms\n", calc_diff(start, end));

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < NUM_OPS; i++) {
        find_fn(sets[f[i]]);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("find_set: %f ms\n", calc_diff(start, end));

    for(int i = 0; i < NUM_ELEMENTS; i++) {
        free(sets[i]);
    }
    free(sets);
}

int main() {
    srand(time(NULL));

    int *union_input_x = malloc(sizeof(int) * NUM_OPS);
    int *union_input_y = malloc(sizeof(int) * NUM_OPS);
    int *find_input = malloc(sizeof(int) * NUM_OPS);

    for(int i = 0; i < NUM_OPS; i++) {
        union_input_x[i] = rand() % NUM_ELEMENTS;
        union_input_y[i] = rand() % NUM_ELEMENTS;
        find_input[i] = rand() % NUM_ELEMENTS;
    }

    printf("Benchmarking Basic Union-Find:\n");
    benchmark_union_find(union_sets, find_set, union_input_x, union_input_y, find_input);
    printf("\n");

    printf("Benchmarking Union-Find with path compression:\n");
    benchmark_union_find(union_sets_path_compression, find_set_path_compression, union_input_x, union_input_y, find_input);
    printf("\n");

    printf("Benchmarking Union-Find with path compression and union by rank:\n");
    benchmark_union_find(union_sets_pcr, find_set_path_compression, union_input_x, union_input_y, find_input);
    printf("\n");
    
    return 0;
}
