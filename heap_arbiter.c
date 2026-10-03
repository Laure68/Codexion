#include "codexion.h"

/*heap_arbiter.c
├── arbiter_init()
├── arbiter_push()
├── arbiter_pop()
├── arbiter_free()
└── arbiter_compare()   → 🎯 LA fonction clé !
                           fifo  : compare arrival time
                           edf   : compare deadline
                           lifo  : inverse of fifo*/