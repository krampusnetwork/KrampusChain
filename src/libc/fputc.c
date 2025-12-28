#include <stdio.h>
#include <fileioc.h>

int __attribute__((weak)) fputc(int c, FILE *stream)
{
    int ret;

    if (stream == NULL)
    {
        return EOF;
    }

    if (stream == stdin)
    {
        stream->err = 1;
        return EOF;
    }
    else if (stream == stdout || stream == stderr)
    {
        ret = putchar(c);
    }
    else
    {
        ret = ti_PutC((char)c, stream->slot);
    }

    if (ret == EOF || ret != c)
    {
        stream->err = 1;
    }

    return ret;
}
