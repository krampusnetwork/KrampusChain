#include <stdio.h>
#include <fileioc.h>
#include <stdint.h>

size_t __attribute__((weak)) fwrite(const void *__restrict ptr, size_t size, size_t count, FILE *__restrict stream)
{
    size_t ncount;

    if (stream == NULL)
    {
        return 0;
    }

    if (stream == stdin)
    {
        stream->err = 1;
        return 0;
    }

    if (size == 0 || count == 0)
    {
        return 0;
    }

    if (ptr == NULL)
    {
        return 0;
    }

    if (count > SIZE_MAX / size)
    {
        return 0;
    }

    if (stream == stdout ||
        stream == stderr)
    {
        const char *p = (const char *)ptr;
        size_t len = size * count;
        size_t num = 0;

        for (; len > 0; len--)
        {
            if (putchar(*p++) == EOF)
            {
                stream->err = 1;
                break;
            }
            num++;
        }

        return num / size;
    }

    ncount = ti_Write(ptr, size, count, stream->slot);
    if (ncount != count)
    {
        stream->err = 1;
    }

    return ncount;
}
