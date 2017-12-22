#include <stdio.h>
#include <stdlib.h>

#include "vcl.h"
#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"

int
init_function(const struct vrt_ctx *ctx, struct vmod_priv *priv,
    enum vcl_event_e e)
{
  if (e != VCL_EVENT_LOAD)
    return (0);

  /* init what you need */
  return (0);
}

const char *
vmod_escape(const struct vrt_ctx *ctx, const char *str, ...)
{
  char *b, *e;
  unsigned u;
  va_list ap;

  CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
  CHECK_OBJ_NOTNULL(ctx->ws, WS_MAGIC);
  u = WS_Reserve(ctx->ws, 0);
  e = b = ctx->ws->f;
  e += u;
  va_start(ap, str);
  while (b < e && str != vrt_magic_string_end) {
    while (b < e && str && *str) {
      if (*str == '\b' || *str == '\n' || *str == '\r'
          || *str == '\t' || *str == '\f' || *str == '"' 
          || *str == '\\' || *str == '/') { 
        *b++ = '\\';
        *b++ = *str++;
      } else {
        *b++ = *str++;
      }
    }
    str = va_arg(ap, const char *);
  }
  if (b < e)
    *b = '\0';
  b++;
  if (b > e) {
    WS_Release(ctx->ws, 0);
    return (NULL);
  } else {
    e = b;
    b = ctx->ws->f;
    WS_Release(ctx->ws, e - b);
    return (b);
  }
}
