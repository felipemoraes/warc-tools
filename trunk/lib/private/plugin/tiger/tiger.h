#ifndef	__TIGER_H__
#define	__TIGER_H__

/* sboxes.c: Tiger S boxes */

/* 
 * This file was originally called "sboxes.c". 
 * Move the "table" array into "tiger.c"
 * change 2008-01-11 by voidptrptr - Hanzo Archives Limited.
 */

/*
 * Portability header file
 */

#include <wport.h>

typedef warc_u64_t    word64;
typedef warc_u32_t    word32;
typedef unsigned char byte;

extern void tiger(word64 *, word64, word64 res[3]);

#endif /* __TIGER_H__ */