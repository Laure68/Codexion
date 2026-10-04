#include "codexion.h"

/*heap_arbiter.c
├── arbiter_init()
├── arbiter_push()
├── arbiter_pop()
├── arbiter_free()
└── arbiter_compare()   → 🎯 LA fonction clé !
                           fifo  : compare arrival time
                           edf   : compare deadline
                           lifo  : inverse of fifo
                           heap_arbiter.c
├── arbiter_init()       → initialize heap + mutex + cond
├── arbiter_push()       → add coder to heap
├── arbiter_pop()        → remove and return highest priority coder
├── arbiter_free()       → destroy mutex + cond + free
└── arbiter_compare()    → fifo / edf / lifo strategy*/