/*
 * Name: fib
 * Description: Paul's fibonacci
 */
#include <iostream>

using namespace std;

int main(void)
{
  int a,b,c;

  a=1;
  b=0;
  c=0;

  for(int x=1; x <= 10; x++)
  {
    c = a + b;
    b = a;
    a = c;
    cout << "c: " << c << endl;
  } 

  return 1;
}
