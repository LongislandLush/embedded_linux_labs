#include <stdio.h>

extern const char *leon_message(void);

int main(void)
{
    puts(leon_message());
    return 0;
}
