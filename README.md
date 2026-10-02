*This project CODEXION has been created as part of the 42 curriculum by lmeny*

# <h1 style="color:#ff2bd6">CODEXION ⏱ </h1>

## <h2 style ="color:#00d9ff">“Description”</h2>
### <h3 style="color:#39ff14"> TEXTE   </h3>

## <h2 style ="color:#00d9ff">“Instructions”</h2>
### <h3 style="color:#39ff14"> TEXTE </h3>

|					|													|
| ----------------	| ------------------------------------------------- |
|`Program Name`		|codexion										|
|`Files to Submit`	|Makefile at the root, *.c and *.h					|
|					|in the folder of your choice						|
|`Makefile`			|NAME, all, clean, fclean, re						|
|`Arguments`		|number_of_coders									|
|					|time_to_burnout time_to_compile					|
|					|time_to_debug										|
|					|time_to_refactor number_of_compiles_required		|
|					|dongle_cooldown scheduler							|
|`External Function`| pthread_create, pthread_join, pthread_mutex_init,	|
|					|pthread_mutex_lock,								|
|					|pthread_mutex_unlock, pthread_mutex_destroy,		|
|					|pthread_cond_init,									|
|					|pthread_cond_wait, pthread_cond_timedwait,			|
|					|pthread_cond_signal,								|
|					|pthread_cond_broadcast, pthread_cond_destroy,		|
|					|gettimeofday, clock_gettime,						|
|					|usleep, write, malloc, free, printf, fprintf,		|
|					|strcmp, strlen, atoi, memset						|
|`Libft authorized`	|No													|
|`Description`		|Coders with threads and mutexes (C)				|
|					|													|







## <h2 style ="color:#00d9ff">“Resources”</h2>
### <h3 style="color:#39ff14">Websites / Books:</h3>
- https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
- https://www.geeksforgeeks.org/linux-unix/mutex-lock-for-linux-thread-synchronization/
- https://www.geeksforgeeks.org/c/multithreading-in-c/
- https://www.geeksforgeeks.org/dsa/binary-heap/
- https://www.geeksforgeeks.org/dsa/level-order-tree-traversal/
- https://www.geeksforgeeks.org/dsa/array-representation-of-binary-heap/
- https://www.geeksforgeeks.org/dsa/priority-queue-set-1-introduction/
- https://www.geeksforgeeks.org/dsa/priority-queue-using-binary-heap/
- https://www.geeksforgeeks.org/dsa/heap-sort/
-
### <h3 style="color:#39ff14">AI Assistance:</h3>

All code was written, understood, and validated by me.
AI was used as a learning tool, not a code generator.



## <h2 style="color:#00d9ff">Project Structure</h2>

```
codexion/
├── main.c          → chef d'orchestre
├── parser.c        → lit et vérifie les args
├── simulation.c    → init, lancement, arrêt
├── coder.c         → cycle de vie du coder
├── dongle.c        → prise, relâche, cooldown
├── monitor.c       → détection burnout
├── heap.c          → priority queue (fifo/edf)
└── codexion.h      → structs et prototypes
```

## <h2 style ="color:#00d9ff">"Blocking cases handled"</h2>
A “Blocking cases handled” section describing all the concurrency issues ad-
dressed in your solution (e.g., deadlock prevention and Coffman’s conditions, star-
vation prevention, cooldown handling, precise burnout detection, and log serializa-
tion).


## <h2 style ="color:#00d9ff">"Thread synchronization mechanisms"</h2>
A “Thread synchronization mechanisms” section explaining the specific thread-
ing primitives used in your implementation (pthread_mutex_t, pthread_cond_t,
custom event implementation) and how they coordinate access to shared resources
(dongles, logging, monitor state). Include examples of how race conditions are
prevented and how thread-safe communication is achieved between coders and the
monitor.
