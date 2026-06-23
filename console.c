#include <stdio.h>
#include <stdarg.h>
#include "console.h"

#define ANSI_RESET "\x1b[0m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RED "\x1b[31m"
#define ANSI_CYAN "\x1b[36m"
#define ANSI_YELLOW "\x1b[33m"

void printTitle(const char *title)
{
    printf("%s===============================================%s\n", ANSI_CYAN, ANSI_RESET);
    printf("%s %s %s\n", ANSI_CYAN, title, ANSI_RESET);
    printf("%s===============================================%s\n", ANSI_CYAN, ANSI_RESET);
}

void printInfo(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("%s+-----------------------------------------------+%s\n", ANSI_YELLOW, ANSI_RESET);
    printf("%s| [INFO]  %s", ANSI_YELLOW, ANSI_RESET);
    vprintf(format, args);
    printf("%s+-----------------------------------------------+%s\n", ANSI_YELLOW, ANSI_RESET);
    va_end(args);
}

void printSuccess(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("%s+-----------------------------------------------+%s\n", ANSI_GREEN, ANSI_RESET);
    printf("%s| [SUCCESS] %s", ANSI_GREEN, ANSI_RESET);
    vprintf(format, args);
    printf("%s+-----------------------------------------------+%s\n", ANSI_GREEN, ANSI_RESET);
    va_end(args);
}

void printError(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("%s+-----------------------------------------------+%s\n", ANSI_RED, ANSI_RESET);
    printf("%s| [ERROR]   %s", ANSI_RED, ANSI_RESET);
    vprintf(format, args);
    printf("%s+-----------------------------------------------+%s\n", ANSI_RED, ANSI_RESET);
    va_end(args);
}
