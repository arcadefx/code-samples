#include <iostream>

using namespace std;

class simple {
  public:
    int r;

    simple()
    {
      r = 0;
    }

    ~simple()
    {
      r = 0;
      cout << "reset r back" << endl;
    }

    int count(int max)
    {
      if (r == max) return r;
      r++;
      cout << "r = "<< r << endl;
      count(max);
    }

    int countDesc(int next,int max)
    {
      if (next < max)
       r = countDesc(next+1, max);
      if (r) cout << "r = "<< r << endl;
      return next;
    }
};

int main(void)
{
  simple counter;
  cout << counter.count(10) << endl;
  counter.r = 0;
  counter.countDesc(0,10);
  return 1;
}
