#include "log.h"
#include "main.h"

void Log(char *fmt, ...)
{
    char buffer[512];
    memset(buffer, 0, 512);

    va_list args;
    va_start(args, fmt);
    vsprintf_s(buffer, 512, fmt, args);
    va_end(args);
    printf(buffer);
    printf("\n");
}