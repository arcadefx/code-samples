/**
 * Program: example.c
 * Description: Example programming using my String like objects in C.
 * Author: Paul Cardwell
 *
 **/
#include "gdt_strings.h"

int main()
{
  char buffer[1024];
  char *data;
   
  // testing my new string functions
  //
  data = gdt_string_new("pooch");
  printf("data = [%s]\n",data);
  
  data = gdt_string_append(data," was here");
  printf("data = [%s]\n",data);

  data = gdt_string_append(data," and ate dog food!");
  printf("data = [%s]\n",data);
  
  // test replacing a string: gdt_string_replace()
  //
  data = gdt_string_replace(data,"e","*",3,0);
  printf("replace data = [%s]\n",data);
  
  // test finding a string: gdt_string_instr()
  //
  if (gdt_string_instr(data,"was")>-1) {
  	 printf("gdt_string_instr found \"was\"\n");
  }
  
  data = gdt_string_destroy(data);
  
  return 1;
}
