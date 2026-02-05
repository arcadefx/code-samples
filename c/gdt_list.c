/*
 * GDT_LIST by Paul D. Cardwell
 * Generic Data Type: Linked List
 * 
 * FILE: gdt_list.c
 */

#include "gdt_list.h"


/* Function: gdt_list_new
 * Description: To create a new 'gdt_list' object/structure.
 *              It will automatically set defaults of the 'gdt_list' to NULL or 0.
 *
 * Parameters: gdt_compare_func, comparison function for data in list.
 *             gdt_malloc_func, allocation function for data in list.
 *             gdt_free_func, free memory allocated for data in list.
 * 
 * Returns: gdt_list *, pointer to the new 'gdt_list.'
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_new( gdt_compare_func gdt_compare,
                        gdt_compare_pattern_func gdt_compare_pattern,
                        gdt_malloc_func gdt_malloc,
                        gdt_free_func gdt_free )
{
  gdt_list *tmp;

  if (!gdt_compare) {
    GDT_LOG("gdt_list_new: gdt_compare_func not defined. No gdt_list defined.");
    return NULL;    
  }
  if (!gdt_malloc) {
    GDT_LOG("gdt_list_new: gdt_malloc_func not defined, no user-defined mallocs will be called.");
  }
  if (!gdt_free) {
    GDT_LOG("gdt_list_new: gdt_free_func not defined, no user-defined frees will be called.");
  }
  if (!gdt_free && gdt_malloc) {
    GDT_LOG("gdt_list_new: gdt_malloc_func is defined without gdt_free_func, please define a gdt_free_func. No gdt_list defined.");
    return NULL;
  }
  tmp = gdt_list_malloc();
  tmp->compare_nodes_func = gdt_compare;
  tmp->compare_nodes_pattern_func = gdt_compare_pattern;
  tmp->malloc_node_func = gdt_malloc;
  tmp->free_node_func = gdt_free;
  return tmp;
}


/* Function: gdt_list_pre_append
 * Description: To pre-append 'data' to a 'gdt_list' of nodes.
 *
 * Parameters: gdt_list (the list to be affected),
 *             gdt_pointer data (data to put into the node)
 *             
 * Returns: gdt_list *, pointer to the newly updated list.
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_pre_append( gdt_list *list, 
                               gdt_pointer data)
{
  gdt_list *tmp=NULL;
  gdt_list_node *node;
  

  if (!data || !list) {
    return NULL;
  }
  
  if (!list->nodes) {
    list->nodes = gdt_list_node_malloc();
    if (!list->nodes)
      return NULL;
    list->nodes->data = gdt_list_node_data_malloc( list, data );
    list->nodes->next = NULL;
    list->last = list->nodes;
    list->count++;
    tmp = list;
  } else {
    node = gdt_list_node_malloc();
    if (!node)
      return NULL;
    node->data = gdt_list_node_data_malloc( list, data );
    node->next = list->nodes;
    list->nodes = node;
    list->count++;
    tmp = list;
  }

  return tmp;
}


/* Function: gdt_list_append
 * Description: To append 'data' to a 'gdt_list' of nodes.
 *
 * Parameters: gdt_list (the list to be affected), 
 *             gdt_pointer data (data to put into the node)
 *             
 * Returns: gdt_list *, pointer to the newly updated list.
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_append( gdt_list *list, 
                           gdt_pointer data)
{
  gdt_list *tmp=NULL;
  gdt_list_node *node;
  gdt_list_node *p;

  if (!data || !list) {
    return NULL;
  }
  
  if (!list->nodes) {
    list->nodes = gdt_list_node_malloc();
    if (!list->nodes)
      return NULL;
    list->nodes->data = gdt_list_node_data_malloc( list, data );
    list->nodes->next = NULL;
    list->last = list->nodes;
    list->count++;
    tmp = list;
  } else {
    node = gdt_list_node_malloc();
    if (!node)
      return NULL;
    node->data = gdt_list_node_data_malloc( list, data );
    node->next = NULL;
    p = list->last;
    p->next = node;
    list->last = node;
    list->count++;
    tmp = list;
  }

  return tmp;
}


/* Function: gdt_list_insert
 * Description: To insert 'before_this_data' before 'this_data' in list of nodes.
 *
 * Parameters: gdt_list (the list to be affected), 
 *             gdt_pointer before_this_data (data to find and insert infront of)
 *             gdt_pointer this_data (data to insert)
 *             
 * Returns: gdt_list *, pointer to the newly updated list.
 *                      It returns NULL if unsuccessful (?).
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_insert( gdt_list *list, 
                           gdt_pointer before_this_data,
                           gdt_pointer this_data)
{
  gdt_list_node *tmp, *prev=NULL, *new_node=NULL;
  int result;


  if (!this_data || !before_this_data) return NULL;

  if (!list) { /* No data in list, just append */
    list = (gdt_list *) gdt_list_append( list, 
                                         this_data);
    return list;
  }

  for(tmp = list->nodes; tmp ; tmp=tmp->next) {
    result = (int) (* list->compare_nodes_func) ( before_this_data, tmp->data );
    if ( !result ) {
    
        new_node = gdt_list_node_malloc();
        new_node->data = gdt_list_node_data_malloc( list, this_data );
        if (!new_node->data) {
          GDT_LOG("gdt_list_insert: insert node failed on malloc().");     
          return list; /* return null ??? */
        }
        new_node->next = tmp;
        if (prev) prev->next = new_node;
          else list->nodes = new_node;
        list->count++;
        
        break;      
    }
    prev = tmp; /* save previous place */
  }

  return list;
}


/* Function: gdt_list_update
 * Description: To find and update a item in a 'gdt_list'.
 *
 * Parameters: gdt_list (the list to be affected),
 *             gdt_pointer cur_data (current data to find)
 *             gdt_pointer new_data (new data to put into the node found)
 *             
 * Returns: gdt_list *, pointer to the updated list.
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_update( gdt_list *list,
                           gdt_pointer cur_data, 
                           gdt_pointer new_data)
{
  gdt_list_node *tmp;
  int result;
  
  if (!list || !cur_data || !new_data)
    return list; /* return NULL ?? */

  for(tmp = list->nodes; tmp ; tmp=tmp->next) {
    result = (int) (* list->compare_nodes_func) ( cur_data, tmp->data );
    if ( !result ) {
      gdt_list_free_data( list, tmp->data );
      tmp->data = NULL;
      tmp->data = gdt_list_node_data_malloc( list, new_data );
    }
  }
  
  return list;
}


/* Function: gdt_list_update_node
 * Description: To update a specific node in a 'gdt_list_node'.
 *
 * Parameters: gdt_list_node (the node to be affected),
 *             gdt_pointer data (data to put into the node)
 *             
 * Returns: gdt_list_node *, pointer to the updated node.
 *                           It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list_node *gdt_list_update_node( gdt_list_node *node, 
                                     gdt_pointer data)
{
  gdt_list_node *tmp;
  
  if (!node || !data)
    return NULL;

  tmp = node->data;
  node->data = data;
  gdt_free( tmp->data );
  
  return node;
}


/* Function: gdt_list_remove
 * Description: To remove a the first occurrence of 'data' in a 'gdt_list'.
 *
 * Parameters: gdt_list (the list be affected),
 *             gdt_pointer data (data to find and remove),
 *             gdt_pointer user_function (comparision function, it follows same
 *                                        logic as "strcmp").
 *             
 * Returns: gdt_list_node *, pointer to the updated 'gdt_list.'
 *                           It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_remove( gdt_list *list, 
                           gdt_pointer data)
{
  gdt_list_node *tmp, *prev;
  int result;


  if (!list || !data) return NULL;

  prev = list->nodes;
 
  for(tmp = list->nodes; tmp ; tmp=tmp->next) {
    result = (int) (* list->compare_nodes_func) ( data, tmp->data );
    if ( !result ) {
    
        /* 
         * example of below line in action:
         * node 2,3,4 make node 2 point to node 4 instead of node 3
         */
        prev->next = tmp->next;
        
        if (list->nodes == tmp) list->nodes = tmp->next; /* if on top, then go next one down */
        if (list->last == tmp) {
           list->last = prev;
           list->last->next = NULL;
         }
        gdt_list_free_data( list, tmp->data );
        gdt_list_free(tmp);
        tmp=NULL;
        list->count--;
        
        break;      
    }
    prev = tmp; /* save previous place */
  }

  return list;
}


/* Function: gdt_list_remove_pattern
 * Description: To remove all occurrences of 'data' in a 'gdt_list'.
 *
 * Parameters: gdt_list (the list be affected),
 *             data (data to find and remove),
 *             gdt_pointer user_function (comparision function, it follows same
 *                                        logic as "strcmp").
 *             
 * Returns: gdt_list_node *, pointer to the updated 'gdt_list.'
 *                           It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_remove_pattern( gdt_list *list, 
                                   gdt_pointer data)
{
  gdt_list_node *tmp, *prev, *save;
  int result;


  if (!list || !data) return NULL;

  prev = list->nodes;
 
  for(tmp = list->nodes; tmp ; tmp=tmp->next) {
    result = (int) (* list->compare_nodes_func) ( data, tmp->data );
    if ( !result ) {
    
        /* node 2,3,4 make node 2 point to node 4 instead of node 3 */
        if (prev) prev->next = tmp->next;
        
        if (list->nodes == tmp) list->nodes = tmp->next; /* if on top, then go next one down */
        if (list->last == tmp) {
           list->last = prev;
           list->last->next = NULL;
           tmp=NULL;
           break;
         }
        save = tmp->next;
        gdt_list_free_data( list, tmp->data );
        gdt_list_free(tmp);
        tmp = save;
        list->count--;
    }
    if (tmp) prev = tmp; /* save previous place */
  }

  return list;
}


/* Function: gdt_list_foreach
 * Description: For all nodes in 'gdt_list' execute user function.
 *
 * Parameters: gdt_list (the list be affected),
 *             gdt_pointer x() (user-defined function to execute)
 *             
 * Returns: none
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
void gdt_list_foreach( gdt_list *list, 
                      gdt_pointer gdt_list_foreach_func( gdt_pointer user_data ),
                      int gdt_list_order)
{
   gdt_list_node *tmp;
   
   if (!list) return;
   if (!list->nodes) return;

   if (gdt_list_order == GDT_LIST_ORDERED) {   
     for(tmp = list->nodes ; tmp ; tmp = tmp->next) 
       gdt_list_foreach_func( tmp->data );
   } else if (gdt_list_order == GDT_LIST_REVERSED) {
     tmp = list->nodes;
     gdt_list_foreach_recursion( tmp, gdt_list_foreach_func );
   }
}


/* Function: gdt_list_foreach_recursion
 * Description: For all nodes in 'gdt_list_node' execute user function.
 *              It uses recursion to handle walking the list of nodes.
 *
 * Parameters: gdt_list_node (the nodes to be affected),
 *             gdt_pointer x() (user-defined function to execute)
 *             
 * Returns: none
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
void gdt_list_foreach_recursion( gdt_list_node *nodes,
                                gdt_pointer gdt_list_foreach_func( gdt_pointer user_data))
{
  gdt_list_node *tmp;

  tmp = nodes;
  
  if (tmp) {
    gdt_list_foreach_recursion( tmp->next, gdt_list_foreach_func ); 
    gdt_list_foreach_func( tmp->data );
  }
}


/* Function: gdt_list_search
 * Description: Find and return the first occurrence of 'data' in 'gdt_list'.
 *
 * Parameters: gdt_list (the list to be affected),
 *             gdt_pointer data (data to be found),
 *             gdt_pointer user_function (comparision function, it follows same
 *                                        logic as "strcmp").
 *             
 * Returns: gdt_list *, pointer to a newly created list, which contains one node
 *                      that was found.
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_search( gdt_list *list, 
                                gdt_pointer data)
{
  gdt_list_node *tmp;
  gdt_list *found_list;

  if (!list || !data)
    return NULL;
    
  found_list = gdt_list_new( list->compare_nodes_func,
                             list->compare_nodes_pattern_func,
                             list->malloc_node_func,
                             list->free_node_func );

  for(tmp = list->nodes; tmp ; tmp = tmp->next) {
    if (!(int) (* list->compare_nodes_func) ( data, tmp->data )) {
      found_list = gdt_list_append( found_list, tmp->data );
      return found_list;
    }
  }
  
  return NULL;
}


/* Function: gdt_list_search_pattern
 * Description: Find all occurrence of 'data' in 'gdt_list'.
 *
 * Parameters: gdt_list (the list to be affected),
 *             gdt_pointer data (user-defined function to execute)
 *             gdt_pointer user_function (comparision function, it follows same
 *                                        logic as "strcmp").
 *             
 * Returns: gdt_list *, pointer to a newly created list, which contains nodes
 *                      that were found.
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_search_pattern( gdt_list *list, 
                                   gdt_pointer data)
{
  gdt_list_node *tmp;
  gdt_list *found_list;

  if (!list || !data)
    return NULL;

  if (!list->compare_nodes_pattern_func) {
    GDT_LOG("gdt_list_search_pattern: compare_nodes_pattern_func function not defined. No pattern search performed.");
    return NULL;
  }
  
  found_list = gdt_list_new( list->compare_nodes_func,
                             list->compare_nodes_pattern_func,
                             list->malloc_node_func,
                             list->free_node_func );

  for(tmp = list->nodes; tmp ; tmp = tmp->next) {
    if (!(int) (* list->compare_nodes_func) ( data, tmp->data )) {
      found_list = gdt_list_append( found_list, tmp->data );
    }
  }
  
  return found_list;
}


/* Function: gdt_list_next_node
 * Description: To return the next node in a 'gdt_list_node'.
 *              Use it like (examples only):
 *              p = (gdt_list_node *) gdt_list_next_node(example_list->nodes);
 *              ..or..
 *              while ( (p = (gdt_list_node *) gdt_list_next_node(example_list->nodes) ) 
 *                printf("data: %s\n", p->data);
 *
 * Parameters: gdt_list_node (the list->node to be affected),
 *             
 * Returns: gdt_list_node *, pointer to the next node in the 'gdt_list_node.'
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list_node *gdt_list_next_node( gdt_list_node *node )
{
   if (node) {
     return node->next;
   } else {
     return NULL;
   }
}


/* Function: gdt_list_get_nth_node
 * Description: To return the n_th (node n of n) node in a 'gdt_list_node'.
 *
 * Parameters: gdt_list (the list to walk to find the n_th node),
 *             gdt_long (the n_th node to find)
 *             
 * Returns: gdt_list_node *, pointer to the n_th node in the 'gdt_list_node.'
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list_node *gdt_list_get_nth_node( gdt_list *list, gdt_long n_th_node )
{
  gdt_list_node *tmp;
  gdt_long count;
  
  if (list) {
    for(tmp = list->nodes, count = 0 ; tmp && (count < n_th_node) ; tmp = tmp->next , count++);
    return tmp;
  }
  return NULL;
}


/* Function: gdt_list_count
 * Description: To return the number of nodes in a 'gdt_list'.
 *
 * Parameters: gdt_list (the list that contains the number of nodes in it),
 *             gdt_long (the number of nodes in the gdt_list)
 *             
 * Returns: gdt_long , the number of nodes in the 'gdt_list_node.'
 *                      It returns 0 if empty.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_long gdt_list_count( gdt_list *list )
{
  if (list)
    return list->count;

  return (gdt_long)0;
}


/* Function: gdt_list_malloc
 * Description: To create a new object/structure of 'gdt_list' and set
 *              initial values to null and/or 0.
 *
 * Parameters: none
 *             
 * Returns: gdt_list *, pointer to the newly created gdt_list.
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_malloc( void )
{
  gdt_list *tmp;

  tmp = (gdt_list *) gdt_malloc(sizeof( gdt_list ));
  if (!tmp) {
    return NULL;
  }
  tmp->last = NULL;
  tmp->nodes = NULL;
  tmp->count = 0;
  return tmp;
}


/* Function: gdt_list_node_malloc
 * Description: To create a new object/structure of 'gdt_list_node'
 *
 * Parameters: none
 *             
 * Returns: gdt_list *, pointer to the newly created gdt_list_node.
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list_node *gdt_list_node_malloc( void )
{
  gdt_list_node *tmp;

  tmp = (gdt_list_node *) gdt_malloc(sizeof( gdt_list_node ));
  if (!tmp) {
    return NULL;
  }
  return tmp;
}


/* Function: gdt_list_node_data_malloc
 * Description: To create a new data chunk for data member of 'gdt_list_node'
 *
 * Parameters: gdt_list *, the list to alloc/set the member variable 'data'.
 *             gdt_pointer, the data to alloc/set with.
 *             
 * Returns: gdt_pointer, pointer to the data allocated or pointed to
 *                      It returns NULL if unsuccessful.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_pointer gdt_list_node_data_malloc( gdt_list *list, gdt_pointer data)
{
  if (!list || !data) return NULL;

  return (list->malloc_node_func ? ((* list->malloc_node_func) (data)) : data);  
}


/* Function: gdt_list_free
 * Description: To release memory allocated for data
 *
 * Parameters: gdt_pointer, any type of data allocated by gdt_malloc()
 *             
 * Returns: none.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
void gdt_list_free( gdt_pointer data )
{
   gdt_free( data );
}


/* Function: gdt_list_free_data
 * Description: To release memory allocated for data using user_function,
 *              if not, just free it.
 *
 * Parameters: gdt_pointer, any type of data allocated by gdt_malloc()
 *             
 * Returns: none.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
void gdt_list_free_data( gdt_list *list, gdt_pointer data )
{
   if (!list->free_node_func) {
     if (data)
       gdt_free( data );
   } else {
     if (data)
       (*list->free_node_func) ( data );
   }
}


/* Function: gdt_list_destroy
 * Description: To destroy/remove a 'gdt_list' from memory and free up
 *              memory allocated for it.
 *
 * Parameters: gdt_pointer *, ( a pointer to the gdt_list to be affected)
 *             
 * Returns: NULL
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_list *gdt_list_destroy( gdt_list *list )
{
  gdt_list_node *tmp;
  
  if ( list ) {
    while(list->nodes) {
      tmp = list->nodes->next;                                     
      gdt_list_free_data( list, list->nodes->data );
      gdt_list_free(list->nodes);
      list->nodes = tmp;
    }
    gdt_list_free(list);
  }
  return NULL;
}
