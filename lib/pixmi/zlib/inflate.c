/* inflate.c -- zlib interface to inflate modules
 * Copyright (C) 1995-1998 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h 
 */

#include "zlib.h"
#include "zutil.h"
#include "infblock.h"
#include "stdlib.h"
#include "adler32.h" // for CRC

struct inflate_blocks_state {int dummy;}; /* for buggy compilers */

typedef enum {
      METHOD,   /* waiting for method byte */
      FLAG,     /* waiting for flag byte */
      DICT4,    /* four dictionary check bytes to go */
      DICT3,    /* three dictionary check bytes to go */
      DICT2,    /* two dictionary check bytes to go */
      DICT1,    /* one dictionary check byte to go */
      DICT0,    /* waiting for inflateSetDictionary */
      BLOCKS,   /* decompressing blocks */
      CHECK4,   /* four check bytes to go */
      CHECK3,   /* three check bytes to go */
      CHECK2,   /* two check bytes to go */
      CHECK1,   /* one check byte to go */
      DONE,     /* finished check, done */
      BAD}      /* got an error--stay here */
inflate_mode;

/* inflate private state */
struct internal_state {

  /* mode */
  inflate_mode  mode;   /* current inflate mode */

  /* mode dependent information */
  union {
    unsigned int method;        /* if FLAGS, method byte */
    struct {
      unsigned long was;                /* computed check value */
      unsigned long need;               /* stream check value */
    } check;            /* if CHECK, check values to compare */
    unsigned int marker;        /* if BAD, inflateSync's marker bytes count */
  } sub;        /* submode */

  /* mode independent information */
  int  nowrap;          /* flag for no wrapper */
  unsigned int wbits;           /* log2(window size)  (8..15, defaults to 15) */
  inflate_blocks_statef 
    *blocks;            /* current inflate_blocks state */

};


int  inflateReset(z)
z_streamp z;
{
  if (z == NULL || z->state == NULL)
    return Z_STREAM_ERROR;
  z->total_in = z->total_out = 0;
  z->msg = NULL;
  z->state->mode = z->state->nowrap ? BLOCKS : METHOD;
  inflate_blocks_reset(z->state->blocks, z, NULL);
  //Tracev((stderr, "inflate: reset\n"));
  return Z_OK;
}


int  inflateEnd(z)
z_streamp z;
{
  if (z == NULL || z->state == NULL || z->zfree == NULL)
    return Z_STREAM_ERROR;
  if (z->state->blocks != NULL)
    inflate_blocks_free(z->state->blocks, z);
  ZFREE(z, z->state);
  z->state = NULL;
  //Tracev((stderr, "inflate: end\n"));
  return Z_OK;
}


int  inflateInit2_(z, w, version, stream_size)
z_streamp z;
int w;
const char *version;
int stream_size;
{
  if (version == NULL || version[0] != ZLIB_VERSION[0] ||
      stream_size != sizeof(z_stream))
      return Z_VERSION_ERROR;

  /* initialize state */
  if (z == NULL)
    return Z_STREAM_ERROR;
  z->msg = NULL;
  if (z->zalloc == NULL)
  {
    z->zalloc = zcalloc;
    z->opaque = (void*)0;
  }
  if (z->zfree == NULL) z->zfree = zcfree;
  if ((z->state = (struct internal_state  *)
       ZALLOC(z,1,sizeof(struct internal_state))) == NULL)
    return Z_MEM_ERROR;
  z->state->blocks = NULL;

  /* handle undocumented nowrap option (no zlib header or check) */
  z->state->nowrap = 0;
  if (w < 0)
  {
    w = - w;
    z->state->nowrap = 1;
  }

  /* set window size */
  if (w < 8 || w > 15)
  {
    inflateEnd(z);
    return Z_STREAM_ERROR;
  }
  z->state->wbits = (unsigned int)w;

  /* create inflate_blocks state */
  if ((z->state->blocks =
      inflate_blocks_new(z, z->state->nowrap ? NULL : adler32, (unsigned int)1 << w))
      == NULL)
  {
    inflateEnd(z);
    return Z_MEM_ERROR;
  }
  //Tracev((stderr, "inflate: allocated\n"));

  /* reset state */
  inflateReset(z);
  return Z_OK;
}


int  inflateInit_(z, version, stream_size)
z_streamp z;
const char *version;
int stream_size;
{
  return inflateInit2_(z, DEF_WBITS, version, stream_size);
}


#define NEEDBYTE {if(z->avail_in==0)return r;r=f;}
#define NEXTBYTE (z->avail_in--,z->total_in++,*z->next_in++)

int  inflate(z, f)
z_streamp z;
int f;
{
  int r;
  unsigned int b;

  if (z == NULL || z->state == NULL || z->next_in == NULL)
    return Z_STREAM_ERROR;
  f = f == Z_FINISH ? Z_BUF_ERROR : Z_OK;
  r = Z_BUF_ERROR;
  while (1) switch (z->state->mode)
  {
    case METHOD:
      NEEDBYTE
      if (((z->state->sub.method = NEXTBYTE) & 0xf) != Z_DEFLATED)
      {
        z->state->mode = BAD;
        z->msg = (char*)"unknown compression method";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      if ((z->state->sub.method >> 4) + 8 > z->state->wbits)
      {
        z->state->mode = BAD;
        z->msg = (char*)"invalid window size";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      z->state->mode = FLAG;
    case FLAG:
      NEEDBYTE
      b = NEXTBYTE;
      if (((z->state->sub.method << 8) + b) % 31)
      {
        z->state->mode = BAD;
        z->msg = (char*)"incorrect header check";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      //Tracev((stderr, "inflate: zlib header ok\n"));
      if (!(b & PRESET_DICT))
      {
        z->state->mode = BLOCKS;
        break;
      }
      z->state->mode = DICT4;
    case DICT4:
      NEEDBYTE
      z->state->sub.check.need = (unsigned long)NEXTBYTE << 24;
      z->state->mode = DICT3;
    case DICT3:
      NEEDBYTE
      z->state->sub.check.need += (unsigned long)NEXTBYTE << 16;
      z->state->mode = DICT2;
    case DICT2:
      NEEDBYTE
      z->state->sub.check.need += (unsigned long)NEXTBYTE << 8;
      z->state->mode = DICT1;
    case DICT1:
      NEEDBYTE
      z->state->sub.check.need += (unsigned long)NEXTBYTE;
      z->adler = z->state->sub.check.need;
      z->state->mode = DICT0;
      return Z_NEED_DICT;
    case DICT0:
      z->state->mode = BAD;
      z->msg = (char*)"need dictionary";
      z->state->sub.marker = 0;       /* can try inflateSync */
      return Z_STREAM_ERROR;
    case BLOCKS:
      r = inflate_blocks(z->state->blocks, z, r);
      if (r == Z_DATA_ERROR)
      {
        z->state->mode = BAD;
        z->state->sub.marker = 0;       /* can try inflateSync */
        break;
      }
      if (r == Z_OK)
        r = f;
      if (r != Z_STREAM_END)
        return r;
      r = f;
      inflate_blocks_reset(z->state->blocks, z, &z->state->sub.check.was);
      if (z->state->nowrap)
      {
        z->state->mode = DONE;
        break;
      }
      z->state->mode = CHECK4;
    case CHECK4:
      NEEDBYTE
      z->state->sub.check.need = (unsigned long)NEXTBYTE << 24;
      z->state->mode = CHECK3;
    case CHECK3:
      NEEDBYTE
      z->state->sub.check.need += (unsigned long)NEXTBYTE << 16;
      z->state->mode = CHECK2;
    case CHECK2:
      NEEDBYTE
      z->state->sub.check.need += (unsigned long)NEXTBYTE << 8;
      z->state->mode = CHECK1;
    case CHECK1:
      NEEDBYTE
      z->state->sub.check.need += (unsigned long)NEXTBYTE;

      if (z->state->sub.check.was != z->state->sub.check.need)
      {
        z->state->mode = BAD;
        z->msg = (char*)"incorrect data check";
        z->state->sub.marker = 5;       /* can't try inflateSync */
        break;
      }
      //Tracev((stderr, "inflate: zlib check ok\n"));
      z->state->mode = DONE;
    case DONE:
      return Z_STREAM_END;
    case BAD:
      return Z_DATA_ERROR;
    default:
      return Z_STREAM_ERROR;
  }
#ifdef NEED_DUMMY_RETURN
  return Z_STREAM_ERROR;  /* Some dumb compilers complain without this */
#endif
}


int  inflateSetDictionary(z, dictionary, dictLength)
z_streamp z;
const unsigned char *dictionary;
unsigned int  dictLength;
{
  unsigned int length = dictLength;

  if (z == NULL || z->state == NULL || z->state->mode != DICT0)
    return Z_STREAM_ERROR;

  if (adler32(1L, dictionary, dictLength) != z->adler) return Z_DATA_ERROR;
  z->adler = 1L;

  if (length >= ((unsigned int)1<<z->state->wbits))
  {
    length = (1<<z->state->wbits)-1;
    dictionary += dictLength - length;
  }
  inflate_set_dictionary(z->state->blocks, dictionary, length);
  z->state->mode = BLOCKS;
  return Z_OK;
}


int  inflateSync(z)
z_streamp z;
{
  unsigned int n;       /* number of bytes to look at */
  unsigned char *p;     /* pointer to bytes */
  unsigned int m;       /* number of marker bytes found in a row */
  unsigned long r, w;   /* temporaries to save total_in and total_out */

  /* set up */
  if (z == NULL || z->state == NULL)
    return Z_STREAM_ERROR;
  if (z->state->mode != BAD)
  {
    z->state->mode = BAD;
    z->state->sub.marker = 0;
  }
  if ((n = z->avail_in) == 0)
    return Z_BUF_ERROR;
  p = z->next_in;
  m = z->state->sub.marker;

  /* search */
  while (n && m < 4)
  {
    static const unsigned char mark[4] = {0, 0, 0xff, 0xff};
    if (*p == mark[m])
      m++;
    else if (*p)
      m = 0;
    else
      m = 4 - m;
    p++, n--;
  }

  /* restore */
  z->total_in += p - z->next_in;
  z->next_in = p;
  z->avail_in = n;
  z->state->sub.marker = m;

  /* return no joy or set up to restart on a new block */
  if (m != 4)
    return Z_DATA_ERROR;
  r = z->total_in;  w = z->total_out;
  inflateReset(z);
  z->total_in = r;  z->total_out = w;
  z->state->mode = BLOCKS;
  return Z_OK;
}


/* Returns true if inflate is currently at the end of a block generated
 * by Z_SYNC_FLUSH or Z_FULL_FLUSH. This function is used by one PPP
 * implementation to provide an additional safety check. PPP uses Z_SYNC_FLUSH
 * but removes the length bytes of the resulting empty stored block. When
 * decompressing, PPP checks that at the end of input packet, inflate is
 * waiting for these length bytes.
 */
int  inflateSyncPoint(z)
z_streamp z;
{
  if (z == NULL || z->state == NULL || z->state->blocks == NULL)
    return Z_STREAM_ERROR;
  return inflate_blocks_sync_point(z->state->blocks);
}
