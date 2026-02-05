#include <iostream>
#include <cstring>

using namespace std;

int main(void)
{
  // stack
  char input[32] = "([hello])";
  char stack[32] = "";
  int len_input = strlen(input);
  int len_stack = 0;
  char c;
  char popped;

  char match = 1;
  for(int x=0; x < len_input; x++)
  {
    c = input[x];
    switch ( c )
    {
      case '{' :
      case '[' :
      case '(' :
        // push
        len_stack = strlen(stack);
        if (len_stack < 31)
          stack[len_stack] = c;
        break;
      case '}' :
      case ']' :
      case ')' :
        // pop
        len_stack = strlen(stack);
        if (len_stack)
        {
          popped = stack[len_stack-1];
          stack[len_stack-1] = '\0';
          if ( (popped == '}' && c != '{') ||
               (popped == ']' && c != '[') ||
               (popped == ')' && c != '(') )
          {
            match = 0;
            break;
          }
        }
        else
         match = 0;
        break;
      default :
        break;
    }
  }
  if (match) 
    cout << "all match" << endl;
  else
    cout << "mis-match found" << endl;

  return 1;
}
