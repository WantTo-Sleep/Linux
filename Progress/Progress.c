#include "Progress.h"

void ProgressBar()
{
    char bar[101] = { 0 };

    int cnt = 0;
    while (cnt <= 100)
    {
        printf("[%-100s][%d%%]\r", bar, cnt);
        fflush(stdout);

        bar[cnt++] = '#';
        usleep(100000);
    }
    printf("\n"); 
}
