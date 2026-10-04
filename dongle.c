








typedef struct s_dongle
{
    int id;
    pthread_mutex_t mutex;
    long last_released_time;
    long dongle_cooldown;
}   t_dongle;



#include "codexion.h"

/*dongle_init()        → initialize dongle + mutex*/
void dongle_init(t_dongle *dongle, t_simulation *data, int index)
{
    dongle->id = index;
    pthread_mutex_init(&dongle->mutex, NULL);
    dongle->dongle_cooldown = data->dongle_cooldown;
    dongle->last_released_time = 0;
}

/*dongle_take()        → lock + check availability + take*/

/* dongle_release()     → release + start cooldown timer*/

/*check_cooldown()    → check if cooldown has passed*/
temps_actuel - last_released_time >= dongle_cooldown

/*dongle_destroy()     → destroy mutex + free*/