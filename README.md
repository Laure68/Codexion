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

### <h3 style="color:#39ff14">AI Assistance:</h3>

All code was written, understood, and validated by me.
AI was used as a learning tool, not a code generator.



## <h2 style="color:#00d9ff">Project Structure</h2>
- 🏗️ STRUCTS
- **t_simulation** — The central hub of the program.
Holds all the parameters needed to run the simulation
(number of coders, timings, flags) and gives every
thread access to shared resources (coders, dongles, arbiter).
- **t_coder** — Represents a single coder.
Holds all the information specific to one coder :
its id, compile count, last compile time,
and pointers to its left and right dongles.
- **t_dongle** — Represents a single dongle (shared resource).
Holds its availability state, cooldown timer,
and a mutex to protect concurrent access.
- **t_arbiter** — The scheduler and notifier of the simulation.
Manages the priority queue (heap) of waiting coders,
determines who gets the next dongle based on the
chosen policy (fifo or edf), and signals the
winning coder via a condition variable 🔔.

- 📁 FICHIERS
```
codexion/
├── main.c          → orchestrator
├── parser.c        → read and validate args
├── simulation.c    → init, launch, stop
├── coder.c         → coder lifecycle
├── dongle.c        → take, release, cooldown
├── monitor.c       → burnout detection
├── heap_arbiter.c  → priority queue + arbitrage (fifo/edf)
├── tools.c         → 
└── codexion.h      → structs and prototypes
```

- 🔄 SÉQUENCE
```
     ALL CODER                    HEAP_ARBITER                           MONITOR
│                          │                                         │                    │
|    want 2 dongles        │                                         │                    │
|                        ---->     go into heap                      │                    │
├    wait for a signal     │                                         │                    │
│                          |     notify -dongle free                 |                    │
│                          |     determin who has priority           |                    │
│     ⬆️ WAKE UP ⬆️       │       🔔 signal 🔔                     │                    │
|     take 2 dongles       │                                         │                    │
|     compile              │                                         |    watch           |
|     release 2 dongles    │                                         │                    │
|     notify arbiter      -->  dongle free(restart process priority) |                    |
|     debug                │                                         │                    │
|     refactor             │                                         │                    │
|                          │                                         |if burnout → stop ! │
└──   restart              │                                         |                    |
```

## <h2 style="color:#00d9ff">Usage:</h2>
### <h3 style="color:#39ff14">Run with Makefile</h3>

```bash
make all
make fclean
make clean
make re
```

### <h3 style="color:#39ff14">Run manually</h3>

```bash
./codexion 5 800 200 100 100 3 50 fifo
./codexion 5 800 200 100 100 3 50 edf
explanation :
./codexion [number_of_coders] [time_to_burnout] [time_to_compile]
           [time_to_debug] [time_to_refactor]
           [number_of_compiles_required] [dongle_cooldown] [scheduler]
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
