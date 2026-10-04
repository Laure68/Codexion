











#include "codexion.h"

/*monitor.c
├── monitor_routine()    → thread function (main loop)
├── check_coders()       → check each coder's last compile time
├── is_burned_out()      → returns 1 if time_to_burnout exceeded
└── print_burnout()      → prints burned out + calls check_end()*/