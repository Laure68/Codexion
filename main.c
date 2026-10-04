#include "codexion.h"



int	main(int ac, char **av)
{
	t_simulation data; 
    if (parse_args(ac, av, &data) != 0)
        return (1);
    
}

/*main.c
├── main()              → chef d'orchestre
├── init_simulation()   → initialise t_simulation
├── launch_threads()    → crée threads coders + monitor
├── join_threads()      → attend la fin de tous les threads
└── clean_simulation()  → libère la mémoire*/



1. appel de parse_args()        → valide et lit les args
2. init_simulation()   → initialise t_simulation
3. launch_threads()    → crée threads coders + monitor
4. join_threads()      → attend la fin de tous les threads
5. clean_simulation()  → libère la mémoire
