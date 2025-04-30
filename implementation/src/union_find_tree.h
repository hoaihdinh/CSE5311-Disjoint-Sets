#ifndef __UNION_FIND_TREE__
#define __UNION_FIND_TREE__

typedef struct __uf_node_t__ uf_node_t;
struct __uf_node_t__ {
    int rank;
    int data;
    uf_node_t* parent;
};

uf_node_t* make_set(int data);

// basic union operation
uf_node_t* union_sets(uf_node_t* x, uf_node_t* y);

// basic find operation
uf_node_t* find_set(uf_node_t* x);

// union function that utilizes path compression
uf_node_t* union_sets_path_compression(uf_node_t* x, uf_node_t* y);
// find function that utilizes path compression 
uf_node_t* find_set_path_compression(uf_node_t* x);

// union function that utilizes path compression and union by rank
uf_node_t* union_sets_pcr(uf_node_t* x, uf_node_t* y);

#endif