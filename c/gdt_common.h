/*
 * GDT_LIST by Paul D. Cardwell
 * Generic Data Type: Common macros and includes used by GDT_xxxx source files
 * 
 * FILE: gdt_common.h
 */


#ifndef GDT_COMMON_H
#define GDT_COMMON_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "gdt_types.h"

int gdt_debug;

/* memory macros */
#define gdt_malloc(A)	malloc(A)
#define gdt_free(A)     free(A)

/* misc. function like macros */
#define gdt_min(A,B)    (A < B ? A : B)   /* return maximum value of A vs B */
#define gdt_max(A,B)    (A > B ? A : B)   /* return mininum value of A vs B */

#ifdef DEBUG
#define GDT_LOG(A)		fprintf(stderr,"GDT_LIBRARY Warning: %s\n", A);
#else
#define GDT_LOG(A)		;
#endif

#endif
