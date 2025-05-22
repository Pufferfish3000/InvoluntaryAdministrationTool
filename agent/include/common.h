#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NDEBUG
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define DPRINTF(fmt, ...)                                                                          \
    do                                                                                             \
    {                                                                                              \
        (void)fprintf(stderr, "[%s] %s:%d " fmt, __FILENAME__, __func__, __LINE__, ##__VA_ARGS__); \
        (void)fprintf(stderr, "\n");                                                               \
    } while (0)

#else
#define DPRINTF(fmt, ...)

#endif /*NDEBUG*/

#define NFREE(ptr)  \
    do              \
    {               \
        free(ptr);  \
        ptr = NULL; \
    } while (0)

#endif /*COMMON_H*/