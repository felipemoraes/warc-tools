
/* ------------------------------------------------------------------- */
/* Copyright (c) 2007-2008 Hanzo Archives Limited.                     */
/*                                                                     */
/* Licensed under the Apache License, Version 2.0 (the "License");     */
/* you may not use this file except in compliance with the License.    */
/* You may obtain a copy of the License at                             */
/*                                                                     */
/*     http://www.apache.org/licenses/LICENSE-2.0                      */
/*                                                                     */
/* Unless required by applicable law or agreed to in writing, software */
/* distributed under the License is distributed on an "AS IS" BASIS,   */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or     */
/* implied.                                                            */
/* See the License for the specific language governing permissions and */
/* limitations under the License.                                      */
/*                                                                     */
/* You may find more information about Hanzo Archives at               */
/*                                                                     */
/*     http://www.hanzoarchives.com/                                   */
/*                                                                     */
/* You may find more information about the WARC Tools project at       */
/*                                                                     */
/*     http://code.google.com/p/warc-tools/                            */
/* ------------------------------------------------------------------- */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <warc.h>

#include <wgzip.h>       /* WGzip */

#define makeString(m) (#m)


/* uncompress everything */
warc_u32_t callback (const warc_u8_t * buffer,
                     const warc_u32_t nbr, void * env)
{
  FILE * out = (FILE *) env;

  /* copy the uncompressed 'nbr' bytes to out */
  fwrite (buffer, 1, nbr, out);


  return (Z_CONTINUE_DECODING);
}

FILE * openReading (const char * fin)
{
  FILE * in;
  unless (in = fopen (fin, "r+b") )
  {
    fprintf (stderr, "error: cannot open file \"%s\" for reading\n",
             fin);
    return NIL;
  }

  return in;
}

FILE * openWriting (const char * fout)
{
  FILE * out;
  unless (out = fopen (fout, "w+b") )
  {
    fprintf (stderr, "error: cannot open file \"%s\" for binary writing\n",
             fout);
    return NIL;
  }

  return out;
}


int test1 (const char * fin)
{
  const char * t     = "TEST 1";
  const char * fout  = "compress_none.gz";
  FILE       * in    = NIL;
  FILE       * out   = NIL;
  void       * g     = NIL; /* WGzip object */
  warc_i32_t   ret   = 0;
  warc_u64_t   csize = 0;   /* compressed file size */

  fprintf (stdout, "%s>\n", t);

  /* empty string */
  g = bless (WGzip);
  assert (g);

  in = openReading (fin);
  assert (in);

  out = openWriting (fout);
  assert (out);


  ret = WGzip_compress (g, in, out, WARC_GZIP_NO_COMPRESSION, & csize);
  assert (!ret);
  fprintf (stderr, "\"%s\" compressed to \"%s\" [size: %llu] [mode: %s]\n",
           fin, fout, (unsigned long long) csize,
           makeString (WARC_GZIP_NO_COMPRESSION) );

  destroy (g);
  fclose (out);
  fclose (in);

  return 0;
}


int test2 (const char * fin)
{
  const char * t     = "TEST 2";
  const char * fout  = "compress_default.gz";
  FILE       * in    = NIL;
  FILE       * out   = NIL;
  void       * g     = NIL; /* WGzip object */
  warc_i32_t   ret   = 0;
  warc_u64_t   csize = 0;   /* compressed file size */

  fprintf (stdout, "%s>\n", t);

  /* empty string */
  g = bless (WGzip);
  assert (g);

  in = openReading (fin);
  assert (in);

  out = openWriting (fout);
  assert (out);


  ret = WGzip_compress (g, in, out, WARC_GZIP_DEFAULT_COMPRESSION, & csize);
  assert (! ret);
  fprintf (stdout, "\"%s\" compressed to \"%s\" [size: %llu] [mode: %s]\n",
           fin, fout, (unsigned long long) csize,
           makeString (WARC_GZIP_DEFAULT_COMPRESSION) );

  destroy (g);
  fclose (out);
  fclose (in);

  return 0;
}

int test3 (const char * fin)
{
  const char * t     = "TEST 3";
  const char * fout  = "compress_speed.gz";
  FILE       * in    = NIL;
  FILE       * out   = NIL;
  void       * g     = NIL; /* WGzip object */
  warc_u64_t   csize = 0;   /* compressed file size */

  fprintf (stdout, "%s>\n", t);

  /* empty string */
  g = bless (WGzip);
  assert (g);

  in = openReading (fin);
  assert (in);

  out = openWriting (fout);
  assert (out);


  WGzip_compress (g, in, out, WARC_GZIP_BEST_SPEED, & csize);
  fprintf (stderr, "\"%s\" compressed to \"%s\" [size: %llu] [mode: %s]\n",
           fin, fout, (unsigned long long) csize,
           makeString (WARC_GZIP_BEST_SPEED) );

  destroy (g);
  fclose (out);
  fclose (in);

  return 0;
}

int test4 (const char * fin)
{
  const char * t     = "TEST 4";
  const char * fout  = "compress_size.gz";
  FILE       * in    = NIL;
  FILE       * out   = NIL;
  void       * g     = NIL; /* WGzip object */
  warc_i32_t   ret   = 0;
  warc_u64_t   csize = 0;   /* compressed file size */

  fprintf (stdout, "%s>\n", t);

  /* empty string */
  g = bless (WGzip);
  assert (g);

  in = openReading (fin);
  assert (in);

  out = openWriting (fout);
  assert (out);


  ret = WGzip_compress (g, in, out, WARC_GZIP_BEST_COMPRESSION, & csize);
  assert (! ret);
  fprintf (stderr, "\"%s\" compressed to \"%s\" [size: %llu] [mode: %s]\n",
           fin, fout, (unsigned long long) csize,
           makeString (WARC_GZIP_BEST_COMPRESSION) );

  destroy (g);
  fclose (out);
  fclose (in);

  return 0;
}


int test5 (const char * fin)
{
  const char * t     = "TEST 5";
  const char * fout  = "compress.gz";
  FILE       * in    = NIL;
  FILE       * out   = NIL;
  void       * g     = NIL; /* WGzip object */
  warc_i32_t   ret   = 0;
  warc_u64_t   csize = 0;   /* compressed file size */

  fprintf (stdout, "%s>\n", t);

  /* empty string */
  g = bless (WGzip);
  assert (g);

  in = openReading (fin);
  assert (in);

  out = openWriting (fout);
  assert (out);


  ret = WGzip_compress (g, in, out, WARC_GZIP_BEST_COMPRESSION, & csize);
  assert (! ret);
  fprintf (stderr, "\"%s\" compressed to \"%s\" [size: %llu] [mode: %s]\n",
           fin, fout, (unsigned long long) csize,
           makeString (WARC_GZIP_BEST_COMPRESSION) );

  destroy (g);
  fclose (out);
  fclose (in);

  return 0;
}


int test6 (const char * unused)
{
  const char * t     = "TEST 6";
  const char * fin   = "compress.gz";
  FILE       * in    = NIL;
  void       * g     = NIL; /* WGzip object */
  warc_u64_t   usize = 0;   /* uncompressed file size */
  warc_u64_t   csize = 0;   /* compressed file size */
  warc_bool_t  ret;

  unused = 0;

  fprintf (stdout, "%s>\n", t);

  /* empty string */
  g = bless (WGzip);
  assert (g);

  in = openReading (fin);
  assert (in);

  /* try to extract compressed and uncompressed size from GZIP header */
  ret = WGzip_analyzeHeader (g, in, 0, & usize, & csize);

  unless (ret)
  fprintf (stdout,
           "Found data in the GZIP header:\n\t compressed : %llu\n\t uncompressed : %llu\n", (unsigned long long) csize, (unsigned long long) usize);
  else
    fprintf (stdout, "GZIP header contains no information. Sorry !!!\n");

  fclose (in);

  destroy (g);

  return 0;
}


int test7 (const char * unused)
{
  const char * t     = "TEST 7";
  const char * fin   = "compress.gz";
  const char * fout  = "compressed";
  FILE       * in    = NIL;
  FILE       * out   = NIL;
  void       * g     = NIL; /* WGzip object */
  warc_i32_t   ret   = 0;
  warc_u64_t   usize = 0;   /* uncompressed file size */
  warc_u64_t   csize = 0;   /* compressed file size */

  unused = 0;

  fprintf (stdout, "%s>\n", t);

  /* empty string */
  g = bless (WGzip);
  assert (g);

  in = openReading (fin);
  assert (in);

  out = openWriting (fout);
  assert (out);

  /* uncompress file from offset 0 using the callback with env = fout */
  ret = WGzip_uncompress (g, in, 0, & usize, & csize,
                          callback, (void *) out);
  assert (! ret);
  fprintf (stdout,
           "uncompressed \"%s\" to \"%s\" [usize: %llu][csize: %llu]\n",
           fin, fout, (unsigned long long) usize, (unsigned long long) csize);

  fclose (out);
  fclose (in);

  destroy (g);

  return 0;
}


int main (int argc, char ** argv)
{
  const char * f = "app/wdata/testwfile/warcfile.warc";
  int (* tests []) (const char *) = { test1, test2, test3, test4,
                                      test5, test6, test7 };
  warc_u32_t  i = 0;

  UNUSED (argc);
  UNUSED (argv);

  for (i = 0; i < ARRAY_LEN (tests); ++ i)
    {
      tests [i] (f);
    }

  return 0;
}