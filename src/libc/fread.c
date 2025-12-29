#include <stdio.h>
#include <fileioc.h>
#include <stdint.h>

size_t __attribute__((weak)) fread(void *ptr, size_t size, size_t count, FILE *__restrict stream)
{
    size_t ncount;

    if (stream == NULL)
    {
        return 0;
    }

    if (stream == stdout || stream == stderr)
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

    if (stream == stdin)
    {
        int c;
        char *p = ptr;
        size_t len = size * count;
        size_t nread = 0;

        for (; len > 0; len--)
        {
            if ((c = fgetc(stream)) == EOF)
            {
                break;
            }
            *p++ = c;
            nread++;
        }

        return nread / size;
    }

    uint16_t offset = ti_Tell(stream->slot);
    if (offset == UINT16_MAX)
    {
        stream->err = 1;
        return 0;
    }

    uint16_t size_bytes = ti_GetSize(stream->slot);
    if (size_bytes == UINT16_MAX)
    {
        stream->err = 1;
        return 0;
    }

    size_t remaining = (offset <= size_bytes) ? (size_t)(size_bytes - offset) : 0;
    size_t max_count = remaining / size;
    size_t req_count = count;

    if (req_count > max_count)
    {
        stream->eof = 1;
        req_count = max_count;
    }

    if (req_count == 0)
    {
        return 0;
    }

    ncount = ti_Read(ptr, size, req_count, stream->slot);
    if (ncount != req_count)
    {
        stream->err = 1;
    }

    return ncount;
}
