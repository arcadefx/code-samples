/*
 * GDT_STRINGS by Paul D. Cardwell
 * Generic Data Type:
 * 
 * FILE: gdt_strings.c
 * Routines for: string manipulation, 
 *               dynamic string allocation and concatenation, 
 */

#include "gdt_strings.h"

/* Function: gdt_string_new
 * Description: creates a new text string.
 *
 * Useful: It's useful to creating on the fly text strings and
 *         when using the gdt_string_append() you can concatenate two
 *         strings.
 *
 * Parameters: char * = pointer to a string of text or NULL.
 * 
 * Returns: a new string of text pointed at data or NULL.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 04-25-2002 | Paul D. Cardwell | Original code.
 *
 */
char *gdt_string_new(
    char *data)
{
	char *tmp=NULL;
	
	if (data) {
	  tmp = gdt_string_append(tmp,data);
	  data = tmp;
   } else {
     data=NULL;
   }
   return data;
}


/* Function: gdt_string_destroy
 * Description: destroy a string created by gdt_string_new()
 *
 * Parameters: char * = pointer to the string to destroy.
 * 
 * Returns: NULL (frees up memory pointed at data)
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 04-25-2002 | Paul D. Cardwell | Original code.
 *
 */
char *gdt_string_destroy(
    char *data)
{
	if (data) {
	  free(data);
	  data=NULL;
   } else {
     data=NULL;
   }
   return data;
}


/* Function: gdt_string_pre_append
 * Description: pre-append a string to a string
 *
 * Parameters: char * = a pointer to a string of text to pre-append to.
 *             char * = a pointer to a string of text to pre-append. 
 * 
 * Returns: on failure = original 'data' (string) that was passed.
 *          on success = a pointer to the new string
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 04-26-2002 | Paul D. Cardwell | Original code.
 *
 */
char *gdt_string_pre_append(
    char *data,
    char *buf)
{
  int len;
  
  len = strlen(buf)+1;
  
  if (len>0) {
    if (data) {
    	len += strlen(data)+1;
      data = (char*) realloc(data, len * sizeof(char));   
      if (!data) { 	
        GDT_LOG("gdt_append_string: realloc() failed.\n");
      }
      if (data) sprintf(data,"%s%s",buf,data);
    } else {
    	data = NULL;
      data = (char*) malloc(len * sizeof(char));
      if (!data) {
        GDT_LOG("gdt_append_string: malloc() failed.\n");
      }
      if (data) sprintf(data,"%s",buf);
    }    
  }
  return data;
}


/* Function: gdt_append_string
 * Description: append a string
 *
 * Parameters: char * = a pointer to a string of text to append to.
 *             char * = a pointer to a string of text to append. 
 * 
 * Returns: on failure = original 'data' (string) that was passed.
 *          on success = a pointer to the new string
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 04-25-2002 | Paul D. Cardwell | Original code.
 *
 */
char *gdt_string_append(
    char *data,
    char *buf)
{
  int len;
  
  len = strlen(buf)+1;
  
  if (len>0) {
    if (data) {
    	len += strlen(data)+1;
      data = (char*) realloc(data, len * sizeof(char));   
      if (!data) { 	
        GDT_LOG("gdt_append_string: realloc() failed.\n");
      }
      if (data) sprintf(data,"%s%s",data,buf);
    } else {
    	data = NULL;
      data = (char*) malloc(len * sizeof(char));
      if (!data) {
        GDT_LOG("gdt_append_string: malloc() failed.\n");
      }
      if (data) sprintf(data,"%s",buf);
    }    
  }
  return data;
}


/* Function: gdt_string_replace
 * Description: replaces a string with a new string
 *
 * Parameters: char * = a pointer to a string of text to update.
 *             char * = a pointer to a string of text to replace. 
 *             char * = a pointer to a string of replacement text.
 *             int = character position to start the replacement in string
 *                   0 = first position, 1 = second, etc.
 *             int = number of times to replace. ex: replace 2 occurrences.
 *                   0 = all occurrences (default)
 * 
 * Returns: on failure = original 'data' (string) that was passed.
 *          on success = a pointer to the new string
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 04-27-2002 | Paul D. Cardwell | Original code.
 *
 */
char *gdt_string_replace(
    char *data,
    char *replace_buf,
    char *replace_with_buf,
    int pos,
    int count)
{
  int len,
      len_replace_buf,
      i,
      found=-1,
      match=0,
      countflag;
  char *tmp,
       *partial_str;
  
  if (!data) return NULL;
  if (!replace_buf) return data;
  if (pos<0 || count<0) return data;
  
  countflag = (count == 0 ? 0 : count);
  tmp = gdt_string_new(NULL);
  partial_str = gdt_string_new(data);
  
  len = strlen(data); // length of data (original string)
  len_replace_buf = strlen(replace_buf);  // length of string we want to find
  
  for(i=0; i<len;i++) {
  	 if ((countflag && count>0) || !countflag) {
    	 sprintf(partial_str,"%-*.*s",len_replace_buf,len_replace_buf,data+(i));
    	 if (!strcmp(partial_str,replace_buf) && i>=pos) { // we found a match
    	 	match=1;
   	 	found=i;
   	 	if (replace_with_buf) {
   	 	  tmp = gdt_string_append(tmp,replace_with_buf);
   	 	}
   	 	i += len_replace_buf-1;
   	   if (countflag && count) {
   	     count--;
     	   }
   	 }
    }
  	 if (!match) {  // no match, so append each character
  	 	if (tmp) {
  	 	  tmp = (char*) realloc(tmp,strlen(tmp)+2);
  	 	  if (!tmp) {
          GDT_LOG("gdt_string_replace: realloc() failed.\n");
  	 	  } else {
  	 	    sprintf(tmp,"%s%c",tmp,data[i]);
  	 	  }
  	 	} else {
  	 	  tmp = (char*) malloc(2);
  	 	  if (!tmp) {
  	 	    GDT_LOG("gdt_string_replace: malloc() failed.\n");
        } else {
  	 	    sprintf(tmp,"%c",data[i]);
  	 	  }
  	   }
  	 }
  	 match=0;
  }
  if (found>-1) { // found a match, copy the new string data.
  	 data = gdt_string_destroy(data);
  	 data = gdt_string_new(tmp);
  }
  partial_str = gdt_string_destroy(partial_str);
  return data;
}


/* Function: gdt_string_substr
 * Description: returns a substring of a string
 *
 * Parameters: char * = a pointer to string of text.
 *             int = starting position in string (0...)
 *             int = ending position in string (<n> characters from start position)
 * 
 * Returns: on failure = null, if a parameter is invalid or mis-used.
 *          on success = a pointer to the new string
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 04-26-2002 | Paul D. Cardwell | Original code.
 *
 */
char *gdt_string_substr(
    char *data,
    int start_pos,
    int end_pos)
{
  char *tmp; // the result of the substring goes in here
  int len,i,j;
  
  if (!data) return NULL;
  len = strlen(data);
  
  if (start_pos < 0 || start_pos > len) return NULL;
  if (end_pos < 0 || end_pos > len) return NULL;
  if (start_pos > end_pos) return NULL;
    
  tmp = (char*) malloc(((end_pos-start_pos)+1));
  j = 0;
  
  end_pos = start_pos + end_pos;
  
  for(i=start_pos;i<end_pos;i++) {
    tmp[j++] = data[i];
  }
  
  tmp[j]='\0';
  
  return tmp;
}


/* Function: gdt_string_instr
 * Description: returns the first position of occurrence of a string
 *
 * Useful: To see if a string is found in another string.
 *
 * Parameters: char * = a pointer to string of text to search.
 *             char * = a pointer to the string of text to search for.
 *
 * Returns: 
 *          on failure = -1  (no match found)
 *          on success = positive integer (0...) of the starting position
 *                       the string was found at.
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 04-27-2002 | Paul D. Cardwell | Original code.
 *
 */
int gdt_string_instr(
    char *data,
    char *search_str)
{
  int len,
      len_search_str,
      i,
      found=-1;
  char *tmp,
       *partial_str;
  
  if (!data) return found;
  if (!search_str) return found;

  len = strlen(data);
  len_search_str = strlen(search_str);

  if (len_search_str > len) return found;
  
  tmp = gdt_string_new(NULL);
  partial_str = gdt_string_new(data);
  
  for(i=0; i<len;i++) {
  	 sprintf(partial_str,"%-*.*s",len_search_str,len_search_str,data+(i));
  	 if (!strcmp(partial_str,search_str)) {
  	 	found=i; // okay, we found it
  	 	break;
  	 }
  }
  
  partial_str = gdt_string_destroy(partial_str);
  return found; // return starting position of string found else -1
}


/* Function: gdt_string_binary_append
 * Description: append binary data like a string
 *
 * Parameters: char * = binary data to append to.
 *             char [] = binary data to append. 
 *             int = number of characters/bytes in char [] to append.
 * 
 * Returns: on failure = original 'data' (string) that was passed.
 *          on success = a pointer to the new binary string
 *
 * -----------------------------------------------------------------------
 * Change Log
 * -----------------------------------------------------------------------
 * 04-25-2002 | Paul D. Cardwell | Original code.
 *
 */
char *gdt_string_binary_append(
     char *data, 
     char buffer[],
     int n)
{
	static int nbytes;
	int i;
	
   if (!data) {     
     data = (char*) malloc(n);
     for(i=0;i<n;i++) {
    	 data[i]=buffer[i];
     }
     nbytes = n;
   } else {
     data = (char*) realloc(data,(nbytes+n));
     for(i=0;i<n;i++) {
     	 data[nbytes++]=buffer[i];
     }
   }     
   return data;
}
