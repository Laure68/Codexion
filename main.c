#include "codexion.h"


/*main()               → orchestrator*/
int	main(int ac, char **av)
{
	t_simulation data; 
    if (parse_args(ac, av, &data) != 0)
        return (1);
    
}


/*launch_threads()     → creates coder threads + monitor*/

/*join_threads()       → waits for all threads to finish*/

/*clean_simulation()   → frees memory*/

