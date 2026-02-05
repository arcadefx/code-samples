/*
 * GDT_TYPES_H by Paul D. Cardwell
 * Generic Data Type: Top level of GDT library
 * 
 * FILE: gdt_types.h
 */
 
#ifndef GDT_TYPES_H
#define GDT_TYPES_H 1

/* define custom variable types */
typedef void* gdt_pointer;
typedef unsigned long gdt_long;
typedef int gdt_flag;
typedef long int gdt_off_t;

/* define user_declared functions */
typedef int (*gdt_compare_func) (gdt_pointer data, gdt_pointer data2);
typedef int (*gdt_compare_pattern_func) (gdt_pointer data, gdt_pointer data2);
typedef void* (*gdt_malloc_func) (gdt_pointer);
typedef void (*gdt_free_func) (gdt_pointer);

#endif
