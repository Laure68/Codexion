#include "codexion.h"


/*dongle.c
├── dongle_init()        → initialize dongle + mutex
├── dongle_take()        → lock + check availability + take
├── dongle_release()     → release + start cooldown timer
├── dongle_cooldown()    → check if cooldown has passed
└── dongle_destroy()     → destroy mutex + free*/