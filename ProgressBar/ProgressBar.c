#include "ProgressBar.h"

void ProgressBar()
{
    char bar[101] = { 0 };
    const char style[STYLE_MAX_NUM] = { '#', '>', '-' };

    int cnt = 0;
    while (cnt <= 100)
    {
        printf("[%-100s][%d%%]\r", bar, cnt);
        fflush(stdout);

        bar[cnt++] = style[STYLE_NUM];
        usleep(100000);
    }
    printf("\n"); 
}
