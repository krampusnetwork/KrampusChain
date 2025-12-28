#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

static char const * const errno_strings[] = {
    "no error",
    "EPERM",
    "EINVAL",
    "EIO",
    "EDOM",
    "ERANGE",
    "EILSEQ",
    /* C++ errno */
    "E2BIG",
    "EACCES",
    "EADDRINUSE",
    "EADDRNOTAVAIL",
    "EAFNOSUPPORT",
    "EAGAIN",
    "EALREADY",
    "EBADF",
    "EBADMSG",
    "EBUSY",
    "ECANCELED",
    "ECHILD",
    "ECONNABORTED",
    "ECONNREFUSED",
    "ECONNRESET",
    "EDEADLK",
    "EDESTADDRREQ",
    "EEXIST",
    "EFAULT",
    "EFBIG",
    "EHOSTUNREACH",
    "EIDRM",
    "EINPROGRESS",
    "EINTR",
    "EISCONN",
    "EISDIR",
    "ELOOP",
    "EMFILE",
    "EMLINK",
    "EMSGSIZE",
    "ENAMETOOLONG",
    "ENETDOWN",
    "ENETRESET",
    "ENETUNREACH",
    "ENFILE",
    "ENOBUFS",
    "ENODATA",
    "ENODEV",
    "ENOENT",
    "ENOEXEC",
    "ENOLCK",
    "ENOLINK",
    "ENOMEM",
    "ENOMSG",
    "ENOPROTOOPT",
    "ENOSPC",
    "ENOSR",
    "ENOSTR",
    "ENOSYS",
    "ENOTCONN",
    "ENOTDIR",
    "ENOTEMPTY",
    "ENOTRECOVERABLE",
    "ENOTSOCK",
    "ENOTSUP",
    "ENOTTY",
    "ENXIO",
    "EOPNOTSUPP",
    "EOVERFLOW",
    "EOWNERDEAD",
    "EPIPE",
    "EPROTO",
    "EPROTONOSUPPORT",
    "EPROTOTYPE",
    "EROFS",
    "ESPIPE",
    "ESRCH",
    "ETIME",
    "ETIMEDOUT",
    "ETXTBSY",
    "EWOULDBLOCK",
    "EXDEV",
};

static char unknown_errno_string[32];

#define errno_strings_count (sizeof(errno_strings) / sizeof(errno_strings[0]))

char* strerror(int errnum) {
    if ((unsigned int)errnum >= errno_strings_count) {
        snprintf(unknown_errno_string, sizeof(unknown_errno_string), "unknown error %d", errnum);
        return unknown_errno_string;
    }
    return (char*)errno_strings[errnum];
}

void perror(const char *str) {
    if (str != NULL && *str != '\0') {
        fputs(str, stderr);
        fputs(": ", stderr);
    }
    fputs(strerror(errno), stderr);
    fputc('\n', stderr);
}
