/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeny <lmeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 10:29:41 by lmeny             #+#    #+#             */
/*   Updated: 2026/10/05 10:31:48 by lmeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

