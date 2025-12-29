#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) fgetc(FILE *stream)
{
    int c;

    if (stream == NULL)
    {
        return EOF;
    }

    if (stream == stdout ||
        stream == stderr)
    {
        stream->err = 1;
        return EOF;
    }
    else if (stream == stdin)
    {
        c = getchar();
    }
    else
    {
        c = ti_GetC(stream->slot);
    }

    if (c == EOF)
    {
        stream->eof = 1;
    }

    return c;
}
