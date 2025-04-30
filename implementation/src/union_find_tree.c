#include <stdlib.h>

#include "union_find_tree.h"

uf_node_t* make_set(int data) {
    uf_node_t* set = (uf_node_t*)malloc(sizeof(uf_node_t));

    if(set == NULL) {
        return NULL;
    }

    set->rank   = 0;
    set->data   = data;
    set->parent = set;

    return set;
}

uf_node_t* union_sets(uf_node_t* x, uf_node_t* y) {
    uf_node_t* s1 = find_set(x);
    uf_node_t* s2 = find_set(y);

    if(s1 != s2 && s2 != NULL) {
        s2->parent = s1;
    }

    return s1;
}

uf_node_t* find_set(uf_node_t* x) {
    if(x == NULL) {
        return NULL;
    }

    if(x->parent != x) {
        return find_set(x->parent);
    }
    return x;
}

uf_node_t* union_sets_path_compression(uf_node_t* x, uf_node_t* y) {
    uf_node_t* s1 = find_set_path_compression(x);
    uf_node_t* s2 = find_set_path_compression(y);

    if(s1 != NULL && s2 != NULL && s1 != s2) {
        s2->parent = s1;
    }

    return s1;
}

uf_node_t* find_set_path_compression(uf_node_t* x) {
    if(x == NULL) {
        return NULL;
    }

    if(x->parent != x) {
        x->parent = find_set_path_compression(x->parent);
    }
    return x->parent;
}

uf_node_t* union_sets_pcr(uf_node_t* x, uf_node_t* y) {
    uf_node_t* s1 = find_set_path_compression(x);
    uf_node_t* s2 = find_set_path_compression(y);

    if(s1 == NULL || s2 == NULL || s1 == s2) {

        return s1;

    } else if(s1->rank < s2->rank) {
        
        s1->parent = s2;
        return s2;

    } else {

        s2->parent = s1;
        if(s1->rank == s2->rank) {
            s1->rank++;
        }
        return s1;
    }

}