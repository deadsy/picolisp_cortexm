//-----------------------------------------------------------------------------
/*

Logging Functions

*/
//-----------------------------------------------------------------------------

#ifndef LOGGING_H
#define LOGGING_H

//-----------------------------------------------------------------------------

#include <stdarg.h>

//-----------------------------------------------------------------------------

#if defined(DEBUG)
  #define DBG0(...) log_printf(__VA_ARGS__)
#else
  #define DBG0(...)
#endif

//-----------------------------------------------------------------------------

int log_init(void);
void log_printf(char *format_msg, ...);

//-----------------------------------------------------------------------------

#endif // LOGGING_H

//-----------------------------------------------------------------------------
