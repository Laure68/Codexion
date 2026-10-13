*This project CODEXION has been created as part of the 42 curriculum by lmeny*

# <h1 style="color:#ff2bd6">CODEXION ⏱ </h1>

## <h2 style ="color:#00d9ff">“Description”</h2>

- Codexion is a project written in C. 
- **It's a simulation of coders who share dongles.**
- The coders sit 🪑 in circle. 
- There is one dongle 🎙 between each pair of coders.
- One coder must compiling, debugging, refactoring and no burned out.
- To compile, a coder needs two dongles🎙🎙.
- After compiling, he debugs.
- After debugging, he refactors.
- After refactoring, he starts again.
- If a coder wait too long without compiling (time_to_burnout), 
he burns out and the simulation must stop.
- Else the simulation stop when every coder has compiled enough times (number_of_compiles_required).

- For this project we must uses threads and mutex and variable condition for sharing dongles.
- (explanation in this readme on part : "Blocking cases handled" and "Thread synchronization mechanisms"). 
- An arbiter chooses who gets dongles, with two schedulers: Fifo (first in first out) or edf (Earliest Deadline First).


## <h2 style ="color:#00d9ff">“Instructions”</h2>

|					|									        |
| ----------------	|  ------------------------------------------   |
|`Program Name`		|codexion									    |
|`Files to Submit`	|Makefile at the root, *.c and *.h				 |
|					|in the folder of your choice				        |
|`Makefile`			|NAME, all, clean, fclean, re					    |
|`Arguments`		     |number_of_coders							    |
|					|time_to_burnout time_to_compile				    |
|					|time_to_debug								      |
|					|time_to_refactor number_of_compiles_required	  |
|					|dongle_cooldown scheduler					|
|`External Function`|pthread_create, pthread_join, pthread_mutex_init,|
|`Autorized`		|pthread_mutex_lock,						|
|					|pthread_mutex_unlock, pthread_mutex_destroy,	|
|					|pthread_cond_init,							|
|					|pthread_cond_wait, pthread_cond_timedwait,		|
|					|pthread_cond_signal,						|
|					|pthread_cond_broadcast, pthread_cond_destroy,	|
|					|gettimeofday, clock_gettime,					|
|					|usleep, write, malloc, free, printf, fprintf,	|
|					|strcmp, strlen, atoi, memset					|
|`Libft authorized`	|No										|
|`Description`		|Coders with threads and mutexes (C)			|
|					|										|

```
Example of simulation run:
0 1 has taken a dongle
2 1 has taken a dongle
2 1 is compiling
202 1 is debugging
402 1 is refactoring
405 2 has taken a dongle
406 2 has taken a dongle
406 2 is compiling
606 2 is debugging
806 2 is refactoring
900 3 has taken a dongle
902 3 has taken a dongle
902 3 is compiling
1102 3 is debugging
1302 3 is refactoring
```

### <h3 style="color:#39ff14">Usage:</h3>
### <h3 style="color:#b026ff">Run with Makefile</h3>

```bash
make all    # build the program
make fclean # remove object files and the program
make clean  # remove object files
make re     # rebuild everything
```

### <h3 style="color:#b026ff">Run manually</h3>

```bash
order explanation :
./codexion [number_of_coders] [time_to_burnout] [time_to_compile][time_to_debug] 
[time_to_refactor][number_of_compiles_required] [dongle_cooldown] [scheduler]

./codexion 5 800 200 100 100 3 50 fifo
./codexion 5 800 200 100 100 3 50 edf

# grep -E + cut + uniq -c : Show how many times each action happens, all in one list.
./codexion 5 2000 200 200 200 10 0 fifo | grep -E "compiling|debugging|refactoring|dongle|burned" | cut -d' ' -f3- | sort | uniq -c

# grep -c: Count how many times one action happens 
./codexion 5 2000 200 200 200 10 0 fifo | grep -c "is compiling"
./codexion 5 2000 200 200 200 10 0 fifo | grep -c "is debugging"
./codexion 5 2000 200 200 200 10 0 fifo | grep -c "is refactoring"
./codexion 5 2000 200 200 200 10 0 fifo | grep -c "has taken a dongle"
./codexion 5 2000 200 200 200 10 0 fifo | grep -c "burned out"

# valgrind Check that there no memory leakss
valgrind --leak-check=full --show-leak-kinds=all ./codexion 5 2000 200 100 100 3 50 fifo

# helgrind Check that there no data races or locks problen between threads.
valgrind --tool=helgrind ./codexion 5 2000 200 100 100 3 50 fifo
```

## <h2 style="color:#00d9ff">"Project Structure"</h2>
### <h3 style="color:#39ff14">🏗️ STRUCTS</h3>

- **t_simulation:** 
- — The central hub of the program.
- Holds all the parameters needed to run the simulation
(number of coders, timings, flags) and gives every
thread access to shared resources (coders, dongles, arbiter).
- **t_coder:** 
- — Represents a single coder.
- Holds all the information specific to one coder :
its id, compile count, last compile time,
and pointers to its left and right dongles.
- **t_dongle:** 
- — Represents a single dongle (shared resource).
Holds its :
- availability (free or taken), 
- the last released time (last_released_time)
- the cooldown duration, 
- and a mutex to protect concurrent access.
- **t_arbiter:** 
- — The scheduler and notifier of the simulation.
- Manages the waiting queue (array coder_queue) of waiting coders.
- When coders wake up (via a condition variable 🔔), the
chosen policy (fifo or edf) decides which
coder gets the 2 dongles.

### <h3 style="color:#39ff14">📁 FICHIERS</h3>

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
### <h3 style="color:#39ff14">🔄 SÉQUENCE</h3>

```
|CODER (one thread each)     |   ARBITER (queue + condition)   | MONITOR (one thread)       |
|-----------------------     |   ---------------------------   | --------------------       |
|                            |                                 |                            |
|1. wants 2 dongles          |                                 |                            |
| -- push in queue ------->  | adds the coder to the queue     |                            |
|2. sleeps (cond_wait)       |                                 |                            |
|                            |                                 | every 1 ms:                |
|                            |                                 |- reads each coder's        |
|                            |                                 |  last_compile_time         |
|                            |                                 |- broadcast (wakes all)     |
|                            |  on every wake-up, the scheduler|                            |
|                            |  (fifo / edf) picks ONE winner  |                            |
|                            |  among the coders whose 2       |                            |
|                            | dongles are free (cooldown over)|                            |
|   <------ wake up -------- |  the others go back to sleep    |                            |
|3. winner takes 2 dongles   |                                 |                            |
|   "has taken a dongle"     |                                 |                            |
|   leaves the queue         |                                 |                            |
|4. compiles ("is compiling")|                                 |                            |
|   updates last_compile_time|                                 |                            |
|5. releases 2 dongles       |                                 |                            |
|   (cooldown starts)        |                                 |                            |
|   compile_count + 1        |                                 |                            |
|6. everybody compiled enough|                                 |                            |
|   yes -> flag_end = 1      |                                 |                            |
|   -- broadcast ----------->|  wakes all (dongles are free)   |                            |
|7. debugs ("is debugging")  |                                 |                            |
|8. refactors                |                                 |                            |
|("is refactoring")          |                                 |                            |
|9. goes back to step 1      |                                 |                            |
|                            |                                 |if now - last_compile_time  |
|                            |                                 |   > time_to_burnout:       |
|                            |                                 |- prints "burned out"       |
|                            |                                 |- flag_end = 1              |
|                            |                                 |- broadcast                 |
|END: flag_end = 1 -> coders leave their loop -> main joins the threads -> cleanup          |
```



## <h2 style ="color:#00d9ff">"Blocking cases handled"</h2>
### <h3 style="color:#b026ff">Deadlock: "everybody waits for everybody" </h3>

A coder takes both dongles at the same time, or none.
If he can't get the second one, he gives back the first one.
So nobody waits with one dongle in the hand, and nobody is stuck.

### <h3 style="color:#b026ff">Starvation: "The forgoten coder" </h3>
Every coder who waits is in a queue.
- `fifo`: the coder who arrived first goes first.
- `edf`: the coder closest to burnout goes first.
So every coder gets his turn.

### <h3 style="color:#b026ff">Cooldown : "The dongle Breaktime"</h3>

A dongle remembers when it was released (`last_released_time`).
It can be taken again only when enough time has passed (`dongle_cooldown`).

### <h3 style="color:#b026ff">Burnout detection : "The coder wait too long"</h3>

The monitor checks all coders every millisecond.
If a coder waited too long (`time_to_burnout`), the monitor prints "burned out" and stops the simulation.

### <h3 style="color:#b026ff">Logs : "Only one can print at a tiem"</h3>

Only one coder can print at a time (`mutex_print`), so lines are never mixed.
After the simulation ends, nothing is printed anymore.

## <h2 style ="color:#00d9ff">"Thread synchronization mechanisms"</h2>

In Codexion, many threads (the coders and the monitor) work at the same time and share the same data.
We must protect against data races or deadlocks (circular wait)
To do this, we use mutex (locks) and a condition variable (a way to sleep and wake up threads)

### <h3 style="color:#b026ff">Thread synchronization: who protects what</h3>

| Mutex | What it protects |
|---|---|
| `dongle->mutex` | One dongle: only one coder can take it at a time. |
| `coder->mutex` | The coder's last compile time and compile count. |
| `mutex_print` | The printing: one line at a time. |
| `mutex_end` | `flag_end` (the "stop" signal), read by everyone. |
| `arbiter->mutex` + `dongle_ready` | The waiting queue, and the sleep/wake up of coders. |

### <h3 style="color:#b026ff">How we avoid race conditions</h3>

Each shared variable has its own mutex.
We always `lock` before using it and `unlock` after.

### <h3 style="color:#b026ff">How coders and monitor talk</h3>

- The monitor reads each coder's last compile time (with the coder's mutex).
- When the simulation must stop, `flag_end` is set (with `mutex_end`).
- Then everyone is woken up with `pthread_cond_broadcast`, so all coders see the stop signal.

### <h3 style="color:#39ff14">Threads → Mutex → Conditions</h3>

### <h3 style="color:#007c91">Threads: </h3>

**`pthread_create`**
- In general: starts a new thread. It runs at the same time as the rest of the program.
- In Codexion: starts one thread for each coder (`coder_routine`) and one for the monitor (`monitor_routine`), in `launch_threads`.

**`pthread_join`**
- In general: waits until a thread is finished.
- In Codexion: `main` waits for all coders and the monitor before cleaning. This way, no thread uses memory that is already freed.

### <h3 style="color:#007c91">Mutex: </h3>

**`pthread_mutex_init`**
- In general: gets a mutex ready to be used.
- In Codexion: used for each mutex: `mutex_print` and `mutex_end` (`init_simulation`), each coder (`init_coders`), the arbiter (`init_arbiter`) and each dongle (`dongle_init`).

**`pthread_mutex_lock`**
- In general: takes the lock. If someone else has it, the thread waits.
- In Codexion: used before reading or changing shared data. Example: `mutex_end` in `get_flag_end`, `dongle->mutex` in `dongle_take`, `mutex_print` in `log_print`.

**`pthread_mutex_unlock`**
- In general: gives the lock back, so another thread can take it.
- In Codexion: used right after reading or changing the shared data. If we forget it, all the other threads wait forever.

**`pthread_mutex_destroy`**
- In general: cleans a mutex when we don't need it anymore.
- In Codexion: used in `clean_simulation` and `dongle_destroy`, only after all threads are finished.

### <h3 style="color:#007c91">Condition variable: </h3>

**`pthread_cond_init`**
- In general: gets a condition variable ready to be used.
- In Codexion: prepares `dongle_ready` of the arbiter, in `init_arbiter`.

**`pthread_cond_wait`**
- In general: gives the lock back and sleeps until someone wakes the thread up. Then it takes the lock again. We use it in a `while` loop, because being woken up does not mean the condition is true.
- In Codexion: in `heap_arbiter_push`, a coder sleeps on `dongle_ready` until it is his turn (fifo or edf) and his two dongles are free.

**`pthread_cond_broadcast`**
- In general: wakes up all the threads that are sleeping on a condition.
- In Codexion: in `heap_arbiter_wake`, used by a coder who finished compiling, by the monitor every millisecond, and by `set_flag_end`. We use broadcast (not signal) because the winner depends on the scheduler.

**`pthread_cond_destroy`**
- In general: cleans a condition variable when we don't need it anymore.
- In Codexion: used in `heap_arbiter_free`, after all threads are finished.

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
