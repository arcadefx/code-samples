/*
 * GDT_BTREE is derived from the AVL Tree by G. M. Adel'son-Vel'skii and 
 *                                        E. M. Landis.
 * 
 * GDT_BTREE by Paul D. Cardwell
 *
 * Generic Data Type: Balanced Tree
 * 
 * License: LGPL
 * 
 * FILE: gdt_btree.h
 * 
 */

#ifndef GDT_BTREE_H
#define GDT_BTREE_H

#ifndef GDT_H

#include "gdt_common.h"

#endif

/* 
 *                     ** THIS SECTION UNUSED, KEEP AROUND FOR NOW **
 *                     flags = 0;
 *                     flags |= gdt_btree_NUMBER;
 */

#define gdt_btree_NUMBER 0x01
#define gdt_btree_STRING 0x02
#define gdt_btree_STRUCTURE 0x04

/*
 * GDT_BTREE sort types
 */
enum GDT_BTREE_SORT_TYPES { GDT_BTREE_SORT_ASCENDING=0, GDT_BTREE_SORT_DESCENDING };

/*
 * GDT_BTREE structure
 * 
 * NOTE: WE NEED A LOCK MECHANISM FOR EACH NODE (?)
 */

typedef struct GDT_BTREE_NODE {
  void *data;               /* data to store in tree: struct, char, int, etc */
  int height;               /* height of tree node */
  struct GDT_BTREE_NODE *left;      /* left node */
  struct GDT_BTREE_NODE *right;     /* right node */
} gdt_btree_node;

typedef struct GDT_BTREE {
  gdt_long count;
  gdt_flag locked;
  gdt_compare_func compare_nodes_func;
  gdt_compare_pattern_func compare_nodes_pattern_func;
  gdt_malloc_func malloc_node_func;
  gdt_free_func free_node_func;
  gdt_btree_node *node;
} gdt_btree;


/* functions the programmer doesn't care about */

int gdt_btree_height( gdt_btree_node *node );
gdt_btree_node *gdt_btree_single_left_rotate( gdt_btree_node *parent );
gdt_btree_node *gdt_btree_single_right_rotate( gdt_btree_node *parent );
gdt_btree_node *gdt_btree_double_left_rotate( gdt_btree_node *parent );
gdt_btree_node *gdt_btree_double_right_rotate( gdt_btree_node *parent );

gdt_btree_node *gdt_btree_set_node_null( gdt_btree_node *node );

gdt_btree_node *gdt_btree_insert_node( void *data, gdt_btree *tree, gdt_btree_node *node);

gdt_btree_node *gdt_btree_remove_node( void *data,
                                       gdt_btree *tree,
                                       gdt_btree_node *rec );

gdt_btree_node *gdt_btree_update_node( void *data, 
                                  gdt_btree *tree,
                                  gdt_btree_node *node );

void gdt_btree_traverse_node( gdt_btree_node *node, void *gdt_btree_traverse_func( void *),
                              int gdt_btree_sort_type );

gdt_btree_node *gdt_btree_search_node( gdt_btree *tree,
                                       gdt_btree_node *node,
                                       void *data_key,
                                       gdt_btree_node *new_node);

void gdt_btree_free_data( gdt_btree *tree, void *data );

gdt_btree_node *gdt_btree_destroy_node( gdt_btree *tree, gdt_btree_node *node );

/* functions the programmer does care about */

gdt_btree *gdt_btree_new( gdt_compare_func gdt_compare,
                          gdt_compare_pattern_func gdt_compare_pattern,
                          gdt_malloc_func gdt_malloc,
                          gdt_free_func gdt_free );

gdt_btree *gdt_btree_insert( void *data, gdt_btree *tree );

gdt_btree *gdt_btree_update( void *data, gdt_btree *tree );

void     gdt_btree_traverse( gdt_btree *rec, void *gdt_btree_traverse_func( void *),
                           int gdt_btree_sort_type );

gdt_btree *gdt_btree_search( gdt_btree *tree,
                             void *data_key,
                             gdt_btree *new_tree);

gdt_btree *gdt_btree_remove( void *data, gdt_btree *tree );

gdt_btree *gdt_btree_destroy( gdt_btree *tree );

#endif
