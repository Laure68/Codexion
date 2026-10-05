











#include "codexion.h"

/* parse_args()        → check( ac, args)*/
int parse_args(int ac, char *av[], t_simulation *data)
{
    if (ac!=9)
    {
        fprintf(stderr, "too or less args\n");
        return (1);
    }
    if (check_numbers(av) != 0)
        return (1);
    if (check_coders(av) != 0)
        return (1);
    if (check_scheduler(av) != 0)
        return (1);
    return (parse_args_data(av, data));
}

/*parse_args_data    -> complete data with args*/
int parse_args_data(char *av[], t_simulation *data)
{
    data->number_of_coders = atoi(av[1]);
    data->time_to_burnout = atoi(av[2]);
    data->time_to_compile = atoi(av[3]);
    data->time_to_debug = atoi(av[4]);
    data->time_to_refactor = atoi(av[5]);
    data->number_of_compiles_required = atoi(av[6]);
    data->dongle_cooldown = atoi(av[7]);
    if (strcmp(av[8], "fifo") ==0 )
        data->scheduler = FIFO;
    else 
        data->scheduler = EDF;
    data->number_of_dongles = data->number_of_coders;
    return (0);
}

/*check_numbers()     → verify positive integers*/
int check_numbers(char *av[])
{
    int i;
    i = 1;
    while (i <= 7)
        if (atoi (av[i]) < 0)
        {
            fprintf(stderr, "negative number\n");
            return (1);
        }
        else
            i++;
    return (0);
}


/*check_scheduler()   → verify fifo or edf*/
int check_scheduler(char *av[])
{
    if (strcmp(av[8], "fifo") != 0 && strcmp(av[8], "edf") != 0)
    {
        fprintf(stderr, "wrong scheduler\n");
        return (1);
    }
    return (0);
}

/* check_coders()      → verify minimum 2 coders*/
int check_coders(char *av[])
{
    if (atoi (av[1]) <= 1)
    {
        fprintf(stderr, "minimum 2 coders\n");
        return (1);
    }
    return (0);
}
