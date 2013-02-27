/*
  Logging routines / macros
  Written by Noel Cower

  See LICENSE.md for license information
*/

#include "snow/logging/log.hh"
#include <stdarg.h>
#include <stdlib.h>

#if defined(s_fatal_error) && USE_FATAL_ERROR_IMPL

#if defined(__cplusplus)
extern "C"
{
#endif

void s_fatal_error_impl(const char *format, ...)
{
  va_list args;
  va_start(args, format);
#if S_PLATFORM_TOUCHPAD
  int length = vsprintf(format, args) + 1;
  char *str = (char *)malloc(size(char) * length);
  va_end(args);
  va_start(args, format);
  vsnprintf(str, length, format, args);
  va_end(args);
  PDL_Log("%s", str);
  free(str);
  PDL_Log("Aborting from fatal error.\n");
#else
  vfprintf(stderr, format, args);
  va_end(args);
  fprintf(stderr, "Aborting from fatal error.\n");
  fflush(stderr);
#endif
  abort();
} /* log_fatal */

#if defined(__cplusplus)
}
#endif

#endif // s_log_fatal && USE_LOG_FATAL_IMPL

