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
 * FILE: gdt_btree.c
 * 
 */

#include "gdt_btree.h"

/* Function: gdt_btree_height
 * Description: To return the height of a 'gdt_tree'
 *
 * Parameters: gdt_btree
 * 
 * Returns: int, return height of gdt_btree.
 *               It returns -1 if 'rec' parameter is NULL.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
int gdt_btree_height( gdt_btree_node *node )
{
  return (!node ? -1 : node->height);
}


/* Function: gdt_btree_single_left_rotate
 * Description:
 *              
 * gdt_btree_single_left_rotate :
 *        o   height=2      <-- In this situation use this routine.
 *       /
 *      o   height=1
 *     /
 *    o   height=0
 *
 *
 * Parameters: gdt_btree *, pointer to the node to rotate left.
 * 
 * Returns: gdt_btree *, return pointer of gdt_btree rotated left.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 */
gdt_btree_node *gdt_btree_single_left_rotate( gdt_btree_node *parent )
{
  gdt_btree_node *tmp;

  tmp = parent->left;         /* grab parent left leg */
  parent->left = tmp->right;  /* grab tmp right leg and put on parents left side */

  /* Done with parent now, update it's height */
  parent->height = gdt_max(gdt_btree_height(parent->left),
                               gdt_btree_height(parent->right)) + 1;  

  /* Don't forget to put the parent leg on the right side of tmp */
  tmp->right = parent;        /* place on right of tmp the parent leg */

  /* Done with new parent (that is tmp now) update the height */
  tmp->height = gdt_max(gdt_btree_height(tmp->left),
                            gdt_btree_height(tmp->right)) + 1;
  return tmp;
}


/* Function: gdt_btree_single_right_rotate
 * Description:
 *              
 * gdt_btree_single_right_rotate :
 *        o    height=2   <-- In this situation use this routine.
 *         \
 *          o    height=1
 *           \
 *            o    height=0
 *
 *
 * Parameters: gdt_btree *, pointer to the node to rotate right.
 * 
 * Returns: gdt_btree *, return pointer of gdt_btree rotated right.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 */
gdt_btree_node *gdt_btree_single_right_rotate( gdt_btree_node *parent )
{
  gdt_btree_node *tmp;

  tmp = parent->right;         /* grab parent right leg */
  parent->right = tmp->left;  /* grab tmp left leg and put on parents right side */

  /* Done with parent now, update it's height */
  parent->height = gdt_max(gdt_btree_height(parent->left),
                               gdt_btree_height(parent->right)) + 1;  

  /* Don't forget to put the parent leg on the left side of tmp */
  tmp->left = parent;        /* place on left of tmp the parent leg */

  /* Done with new parent (that is tmp now) update the height */
  tmp->height = gdt_max(gdt_btree_height(tmp->left),
                            gdt_btree_height(tmp->right)) + 1;
  return tmp;
}


/* Function: gdt_btree_double_left_rotate
 * Description:
 *              
 * gdt_btree_double_left_rotate :
 *        o d        gdt_btree_double_left_rotate     gdt_btree_double_left_rotate
 *       /
 *      o b     --->   o c             --->     o c
 *       \            /                        / \
 *        o c        o b                    b o   o d
 *
 *
 * Parameters: gdt_btree *, pointer to the node to double rotate left.
 * 
 * Returns: gdt_btree *, return pointer of gdt_btree rotated.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 */
gdt_btree_node *gdt_btree_double_left_rotate( gdt_btree_node *parent )
{
  parent->left = gdt_btree_single_right_rotate(parent->left);
  parent = gdt_btree_single_left_rotate(parent);

  return parent;
}


/* Function: gdt_btree_double_right_rotate
 * Description:
 *              
 * gdt_btree_double_right_rotate :
 *       o b          gdt_btree_double_right_rotate     gdt_btree_double_right_rotate
 *        \
 *         o d   --->    o c           --->    o c
 *        /               \                   / \
 *       o c               o d             b o   o d
 *
 *
 * Parameters: gdt_btree *, pointer to the node to double rotate right.
 * 
 * Returns: gdt_btree *, return pointer of gdt_btree rotated.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 */
gdt_btree_node *gdt_btree_double_right_rotate( gdt_btree_node *parent )
{
  parent->right = gdt_btree_single_left_rotate(parent->right);
  parent = gdt_btree_single_right_rotate(parent);

  return parent;
}


/* Function: gdt_btree_insert
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree *gdt_btree_insert( void *data, gdt_btree *tree )
{

  if (!tree) return NULL;

  tree->node = gdt_btree_insert_node( data, tree, tree->node);
  
  return tree;
}


/* Function: gdt_btree_insert_node
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree_node *gdt_btree_insert_node( void *data, gdt_btree *tree, gdt_btree_node *node)
{ 
  int result;

  if (!data) return NULL;
  
  if (!node) {

    node = (gdt_btree_node *) gdt_malloc(sizeof(gdt_btree_node));
    if (!node) return NULL;
    
    node = gdt_btree_set_node_null( node );
    
    node->data = data;

  } else {

    result = (int) (* tree->compare_nodes_func) ( data, node->data );
    
    if (result <= 0) {

      node->left = gdt_btree_insert_node(data, tree, node->left);

      if ( (gdt_btree_height(node->left) - gdt_btree_height(node->right)) == 2) { /* rotate */
        /* Check to see which rotate is needed that is..
         * SingleLeftRotate() or DoubleLeftRotate().
         * SingleLeftRotate is for the outer leg.
         * DoubleLeftRotate is for the inner leg.
         * if the new_record item is less than the parent->left item then use
         * SingleLeftRotate else use DoubleLeftRotate.
         */

        result = (int) (* tree->compare_nodes_func) ( data, node->left->data );
         
        if (result <= 0) {
          node = gdt_btree_single_left_rotate( node );
        } else {
          node = gdt_btree_double_left_rotate( node );
        }
      }
    } else if (result > 0) {
    
      node->right = gdt_btree_insert_node(data, tree, node->right);

      if ( (gdt_btree_height(node->left) - gdt_btree_height(node->right)) == 2) { /* rotate */
        /* Check to see which rotate is needed that is..
         * SingleRightRotate() or DoubleRightRotate().
         * SingleRightRotate is for the outer leg.
         * DoubleRightRotate is for the inner leg.
         * if the new_record item is greater than the parent->right item then use
         * SingleRightRotate else use DoubleRightRotate.
         */

        result = (int) (* tree->compare_nodes_func) ( data, node->right->data );

        if (result > 0) {
          node = gdt_btree_single_right_rotate( node );
        } else {
          node = gdt_btree_double_right_rotate( node );
        }
      }
    }
    node->height = gdt_max(gdt_btree_height(node->left),
                           gdt_btree_height(node->right)) + 1;
  }
  return node;
}


/* Function: gdt_btree_remove
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree *gdt_btree_remove(void *data, gdt_btree *tree )
{
  if ( !tree )
    return NULL;

  tree->node = gdt_btree_remove_node( data, tree, tree->node );
  return tree;
}


/* Function: gdt_btree_remove_node
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree_node *gdt_btree_remove_node( void *data,
                                       gdt_btree *tree,
                                       gdt_btree_node *node )
{
  gdt_btree_node *tmp_left, *tmp_right;

  int result;
  
  if (!node) {
    return node;
  } else {

  result = (int) (* tree->compare_nodes_func) ( data, node->data );
  
  if (result < 0) {

    node->left = gdt_btree_remove_node(data, tree, node->left);
    if (!node->left) {
      node->height = gdt_max(gdt_btree_height(node->left), 
                                gdt_btree_height(node->right)) + 1;
      return node;
    }

    if ( (gdt_btree_height(node->left) - gdt_btree_height(node->right)) == 2) { /* rotate */
      /* Check to see which rotate is needed that is..
       * SingleLeftRotate() or DoubleLeftRotate().
       * SingleLeftRotate is for the outer leg.
       * DoubleLeftRotate is for the inner leg.
       * if the new_record item is less than the parent->left item then use
       * SingleLeftRotate else use DoubleLeftRotate.
       */

      result = (int) (* tree->compare_nodes_func) ( data, node->data );
        
      if (result < 0) {
        node = gdt_btree_single_left_rotate( node );
      } else {
        node = gdt_btree_double_left_rotate( node );
      }
    }
    
  } else if (result > 0) {
  
    node->right = gdt_btree_remove_node(data, tree, node->right);
    if (!node->right) {
      node->height = gdt_max(gdt_btree_height(node->left),
                                gdt_btree_height(node->right)) + 1;
      return node;
    }

    if ( (gdt_btree_height(node->left) - gdt_btree_height(node->right)) == 2) { /* rotate */
      /* Check to see which rotate is needed that is..
       * SingleRightRotate() or DoubleRightRotate().
       * SingleRightRotate is for the outer leg.
       * DoubleRightRotate is for the inner leg.
       * if the new_record item is greater than the parent->right item then use
       * SingleRightRotate else use DoubleRightRotate.
       */

      result = (int) (* tree->compare_nodes_func) ( data, node->data );

      if (result > 0) {
        node = gdt_btree_single_right_rotate( node );
      } else {
        node = gdt_btree_double_right_rotate( node );
      }
    }
    
  } else { /* okay, time to nuke the record */
        if (node->left && !node->right) {
          printf("left && !right\n");
          fflush(stdout);
          tmp_left = node->left;
          gdt_btree_free_data(tree, node->data);
          gdt_free(node);
          node = tmp_left;
        } else if (!node->left && node->right) {
          printf("!left && right\n");
          fflush(stdout);
          tmp_right = node->right;
          gdt_btree_free_data(tree, node->data);
          gdt_free(node);
          node = tmp_right;
        } else if (node->left && node->right) {
          printf("left && right\n");
          fflush(stdout);
          tmp_left = node->left;
          tmp_right = node->right;
          gdt_btree_free_data(tree, node->data);
          gdt_free(node);
          node = tmp_right;

          node = gdt_btree_insert_node( node->left->data, tree, node );

        } else if (!node->left && !node->right) {
          printf("!left && !right\n");
          fflush(stdout);
          gdt_btree_free_data(tree, node->data);
          gdt_free(node);
          node = NULL;
          return node;
        }
    }
    node->height = gdt_max(gdt_btree_height(node->left),
                              gdt_btree_height(node->right)) + 1;
  }
  return node;
}


/* Function: gdt_btree_update
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree *gdt_btree_update( void *data, gdt_btree *tree )
{
  if (!data || !tree)
    return NULL;

  tree->node = gdt_btree_update_node( data, tree, tree->node );
  return tree;
}


/* Function: gdt_btree_update_node
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree_node *gdt_btree_update_node( void *data, 
                                  gdt_btree *tree,
                                  gdt_btree_node *node )
{
  int result;
  
  if (!data || !tree || !node) {
    return NULL;
  }

  result = (int) (* tree->compare_nodes_func) ( data, node->data );
  
  if (result == 0) {
    /* if data free it */
    if (node->data) gdt_btree_free_data(tree, node->data);
    node->data = (tree->malloc_node_func ? (void *) (* tree->malloc_node_func) (data) : data);       /* ?????????????????? */
  }
  
  if (result < 0)
    node->left = gdt_btree_update_node(data, tree, node->left);       
   else if (result > 0)
    node->right = gdt_btree_update_node(data, tree, node->right);       

  return node;
}


/* Function: gdt_btree_traverse
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
void gdt_btree_traverse( gdt_btree *tree, void *gdt_btree_traverse_func( void *),
                       int gdt_btree_sort_type )
{
  if (!tree)
    return;

  gdt_btree_traverse_node( tree->node, gdt_btree_traverse_func, gdt_btree_sort_type);
}


/* Function: gdt_btree_traverse_node
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
void gdt_btree_traverse_node( gdt_btree_node *node, void *gdt_btree_traverse_func( void *),
                              int gdt_btree_sort_type )
{
  gdt_btree_node *tmp;
 
  tmp = node;

  if (tmp) {
    if ( gdt_btree_sort_type == GDT_BTREE_SORT_DESCENDING ) {
      if (tmp->right) gdt_btree_traverse_node(tmp->right, gdt_btree_traverse_func,
                                       gdt_btree_sort_type);
      gdt_btree_traverse_func( tmp->data );
      if (tmp->left) gdt_btree_traverse_node(tmp->left, gdt_btree_traverse_func,
                                      gdt_btree_sort_type);
    } else if ( gdt_btree_sort_type == GDT_BTREE_SORT_ASCENDING ) {
      if (tmp->left) gdt_btree_traverse_node(tmp->left, gdt_btree_traverse_func,
                                      gdt_btree_sort_type);
      gdt_btree_traverse_func( tmp->data );
      if (tmp->right) gdt_btree_traverse_node(tmp->right, gdt_btree_traverse_func,
                                       gdt_btree_sort_type);
    }
  }
}


/* Function: gdt_btree_search
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree *gdt_btree_search( gdt_btree *tree,
                             void *data_key,
                             gdt_btree *new_tree)
{
  gdt_btree_node *new_nodes=NULL;  

  if (!tree || !data_key || !new_tree)
    return NULL;
    
  new_nodes = gdt_btree_search_node( tree, tree->node, data_key, new_nodes);
  if (new_nodes) {
    new_tree->node = new_nodes;    
  } else {
    return NULL;
  }
  return new_tree;
}


/* Function: gdt_btree_search_node
 * Description:
 * 
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree_node *gdt_btree_search_node( gdt_btree *tree,
                                       gdt_btree_node *node,
                                       void *data_key,
                                       gdt_btree_node *new_node)
{
  int result;
  
  if (!node) {
    return NULL;
  }

  result = (int) (* tree->compare_nodes_func) ( data_key, node->data );
  
  if (result < 0) {
    node->left = gdt_btree_search_node( tree,
                                        node->left,
                                        data_key,
                                        new_node);
  } else if (result > 0) {
    node->right = gdt_btree_search_node( tree,
                                         node->right,
                                         data_key,
                                         new_node);  
  } else {
    new_node = gdt_btree_insert_node( node->data, tree, new_node);
  }
  
  return new_node;
}


/* Function: gdt_btree_new
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 * 
 */
gdt_btree *gdt_btree_new( gdt_compare_func gdt_compare,
                          gdt_compare_pattern_func gdt_compare_pattern,
                          gdt_malloc_func gdt_malloc,
                          gdt_free_func gdt_free )
{
  gdt_btree *tmp;

  if (!gdt_compare) {
    GDT_LOG("gdt_btree_new: gdt_compare_func not defined. No gdt_list defined.");
    return NULL;    
  }
  if (!gdt_malloc) {
    GDT_LOG("gdt_btree_new: gdt_malloc_func not defined, no user-defined mallocs will be called.");
  }
  if (!gdt_free) {
    GDT_LOG("gdt_btree_new: gdt_free_func not defined, no user-defined frees will be called.");
  }
  if (!gdt_free && gdt_malloc) {
    GDT_LOG("gdt_btree_new: gdt_malloc_func is defined without gdt_free_func, please define a gdt_free_func. No gdt_list defined.");
    return NULL;
  }

  tmp = (gdt_btree *) gdt_malloc(sizeof( gdt_btree ));
  if (!tmp) {
    GDT_LOG("gdt_btree_new: Not enough memory. Exiting\n");
    exit(-1);
  }

  tmp->count = 0;
  tmp->locked = 0;
  tmp->compare_nodes_func = gdt_compare;
  tmp->compare_nodes_pattern_func = gdt_compare_pattern;
  tmp->malloc_node_func = gdt_malloc;
  tmp->free_node_func = gdt_free;  
  tmp->node = NULL;
  
  return tmp;
}


/* Function: gdt_btree_set_node_null
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree_node *gdt_btree_set_node_null( gdt_btree_node *node )
{
  node->height = 0;
  node->left = node->right = NULL;
  return node;
}


/* Function: gdt_btree_destroy
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
void gdt_btree_free_data( gdt_btree *tree, void *data )
{
  if (!tree->free_node_func) {
    gdt_free( data );
  } else {
    (*tree->free_node_func) ( data );
  }
}


/* Function: gdt_btree_destroy
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree *gdt_btree_destroy( gdt_btree *tree )
{
  if (!tree) {
    return NULL;
  }
  tree->node = gdt_btree_destroy_node( tree, tree->node );
  gdt_free( tree );
  return NULL;
}


/* Function: gdt_btree_destroy_node
 * Description:
 *
 * Parameters: 
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 03-26-1999 | Paul D. Cardwell | Original code.
 *
 */
gdt_btree_node *gdt_btree_destroy_node( gdt_btree *tree, gdt_btree_node *node )
{
  if (!node) {
    return NULL;
  }

  if (node->left) node->left = gdt_btree_destroy_node(tree, node->left);
  if (node->right) node->right = gdt_btree_destroy_node(tree, node->right);

  if (node) {
    gdt_btree_free_data(tree, node->data);
  }
  
  return node;
}
