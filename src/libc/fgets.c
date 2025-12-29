#include <stdio.h>
#include <fileioc.h>

char* __attribute__((weak)) fgets(char *__restrict str, int num, FILE *__restrict stream)
{
    int c;
    char *p = str;

    if (stream == NULL)
    {
        return NULL;
    }

    if (str == NULL || num <= 0)
    {
        return NULL;
    }

    if (stream == stdout || stream == stderr)
    {
        stream->err = 1;
        return NULL;
    }

    if (num == 1)
    {
        *p = 0;
        return str;
    }

    for (; num > 1; num--)
    {
        if ((c = fgetc(stream)) == EOF)
        {
            break;
        }
        *p++ = c;
        if (c == '\n')
        {
            break;
        }
    }

    if (p == str)
    {
        return NULL;
    }

    *p = 0;

    return str;
}
