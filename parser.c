#include "codexion.h"




/*parser.c
├── parse_args()        → fonction principale du parser
├── check_numbers()     → vérifie positif et entier
├── check_scheduler()   → vérifie fifo ou edf
├── check_coders()      → vérifie minimum 2 coders
└── ft_atoi_strict()    → conversion string → int sécurisée droit a atoi donc pas besoin de cette fonction 
parser.c
├── parse_args()        → main parser function
├── check_numbers()     → verify positive integers
├── check_scheduler()   → verify fifo or edf
├── check_coders()      → verify minimum 2 coders
└── ft_atoi_strict()    → safe string → int conversion*/


/*1. Nombre d'arguments correct (exactement 8)
2. Tous les nombres sont positifs (pas négatifs)
3. Tous les nombres sont des entiers (pas de lettres)
4. Scheduler = "fifo" ou "edf" uniquement
5. number_of_coders >= 2 (besoin de 2 dongles minimum)*/