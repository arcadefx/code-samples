/*
 * GDT_STRINGS_H by Paul D. Cardwell
 * Generic Data Type:
 *
 * Routines for: string manipulation, 
 *               dynamic string allocation and catenation,
 *               
 * 
 * FILE: gdt_strings.h
 */
 
#ifndef GDT_STRINGS_H
#define GDT_STRINGS_H 1

#include "gdt.h"

char *gdt_string_new(
    char *data);
    
char *gdt_string_destroy(
    char *data);

char *gdt_string_pre_append(
    char *data,
    char *buf);

char *gdt_string_append(
    char *data,
    char *buf);

char *gdt_string_replace(
    char *data,
    char *replace_buf,
    char *replace_with_buf,
    int pos,
    int count);
    
char *gdt_string_substr(
    char *data,
    int start_pos,
    int end_pos);

int gdt_string_instr(
    char *data,
    char *search_str);

char *gdt_string_binary_append(
     char *data, 
     char buffer[],
     int n);

#endif
