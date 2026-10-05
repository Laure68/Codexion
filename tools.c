











#include codexion.h

/*returns the actual time tv.tv_sec → sec tv.tv_usec → microsec*/
long get_time_ms(void)
{
    struct timeval    tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}