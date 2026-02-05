#include <iostream>
#include <cstring>

using namespace std;

class simple {
  public:
    int a, b;


    void calc(int left, int right)
    {
      c = left + right;
    }


    int getAnswer(void)
    {
      return c;
    }

  protected:
    int c;

  private: /* I do not share my private data */
    int d;

};

class adv : public simple {
  public:

  void calc(int left, int right)
  {
    c = left * right;
  }

};

int main(void)
{
  simple foo;
  adv afoo;
  cout << "I am a little program." << endl;
  foo.calc(2,4);
  cout << "2+4=" << foo.getAnswer() << endl;
  afoo.calc(2,4);
  cout << "2*4=" << afoo.getAnswer() << endl;

  return 1;
}
