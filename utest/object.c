
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

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <wstring.h>
#include <wanvl.h>
#include <warc.h>

#define makeWString(s) (bless (WString, (s), strlen((s))))

int test1 (void)
{	
  const char * t   = "TEST 1";
  void       * s   = makeWString("");
  void       * a   = bless (WAnvl);

  fprintf (stderr, "%s>\n", t);
  
  assert (s);
  assert (a);

  /* should generate class consistency error */
  WString_getText (a);

  /* never reached */
  destroy (a);
  destroy (s);
      
  return 0;
}

int test2 (void)
{	
  const char * t   = "TEST 2";
  void       * s   = makeWString("");
  void       * l   = bless (WList);

  fprintf (stderr, "%s>\n", t);
  
  assert (s);
  assert (l);

  /* should generate class consistency error */
  WList_size (s);

  /* never reached */
  destroy (l);
  destroy (s);
      
  return 0;
}



int main (void)
{	
  int (* tests [])() = { test1, test2 };
  warc_u32_t  i      = 0;

  for(i = 0; i < ARRAY_LEN (tests); ++ i)
    {
      tests[i] ();
    }

  return 0;
}