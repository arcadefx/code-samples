/*
 * GDT_LIST by Paul D. Cardwell
 * Generic Data Type: Linked List
 * 
 * FILE: gdt_list.h
 */


#ifndef GDT_LIST_H
#define GDT_LIST_H 1

#ifndef GDT_H

#include "gdt_common.h"

#endif

/*
 * GDT_LIST order types
 */
enum GDT_LIST_ORDER_TYPES { GDT_LIST_ORDERED=0, GDT_LIST_REVERSED };

typedef struct GDT_LIST_NODE {
  gdt_pointer data;
  struct GDT_LIST_NODE *next;
} gdt_list_node;

typedef struct GDT_LIST {
  gdt_list_node *last;
  gdt_long count;
  gdt_flag locked;
  gdt_compare_func compare_nodes_func;
  gdt_compare_pattern_func compare_nodes_pattern_func;
  gdt_malloc_func malloc_node_func;
  gdt_free_func free_node_func;
  gdt_list_node *nodes;
} gdt_list;


/* functions the programmer does not care about */

gdt_list *gdt_list_malloc( void );

gdt_list_node *gdt_list_node_malloc( void );

gdt_pointer gdt_list_node_data_malloc( gdt_list *list, gdt_pointer data );

void gdt_list_free( gdt_pointer  );

void gdt_list_free_data( gdt_list *list, gdt_pointer data );

void gdt_list_foreach_recursion( gdt_list_node *nodes,
                                gdt_pointer gdt_list_foreach_func( gdt_pointer user_data));

/* functions the programmer does care about */

gdt_list *gdt_list_new( gdt_compare_func gdt_compare,
                        gdt_compare_pattern_func gdt_compare_pattern,
                        gdt_malloc_func gdt_malloc,
                        gdt_free_func gdt_free );

gdt_list *gdt_list_pre_append( gdt_list *list, 
                               gdt_pointer data);

gdt_list *gdt_list_append( gdt_list *list, 
                           gdt_pointer data);

gdt_list *gdt_list_insert( gdt_list *list, 
                           gdt_pointer before_this_data,
                           gdt_pointer this_data);

gdt_list *gdt_list_update( gdt_list *list,
                           gdt_pointer cur_data, 
                           gdt_pointer new_data);

gdt_list *gdt_list_remove( gdt_list *list, 
                           gdt_pointer data);

gdt_list *gdt_list_remove_pattern( gdt_list *list, 
                                   gdt_pointer data);

void      gdt_list_foreach( gdt_list *list, 
                           gdt_pointer gdt_list_foreach_func( gdt_pointer user_data ),
                           int gdt_list_order);

gdt_list *gdt_list_search( gdt_list *list, 
                           gdt_pointer data);

gdt_list *gdt_list_search_pattern( gdt_list *list, 
                                   gdt_pointer data);

gdt_long  gdt_list_count( gdt_list *list );

gdt_list *gdt_list_destroy( gdt_list * );

/* GDT_LIST "node" specific functions for the programmer */

gdt_list_node *gdt_list_update_node( gdt_list_node *node, 
                                     gdt_pointer data);

gdt_list_node *gdt_list_next_node( gdt_list_node *node );

gdt_list_node *gdt_list_get_nth_node( gdt_list *list, gdt_long n_th_node );

#endif
