#include <iostream>
#include <cstring>

using namespace std;

struct list {
  char name[20];
  struct list *next=NULL;
};

class cart {
   public: 
     struct list *mycart = NULL;
     struct list *head = NULL;

   void addToCart(char *name)
   {
     mycart = (struct list *) malloc(sizeof(struct list));
     if (mycart != NULL)
     {
       strcpy(mycart->name, name);
       mycart->next = head;
       head = mycart;
     }
   }

   void getContents()
   {
     struct list *tmp = head;
     while(tmp != NULL)
     {
        cout << " item : " << tmp->name << endl;
        tmp = tmp->next;
     }
   }

   ~cart()
   {
     // free of memory for mycart
     while(mycart != NULL)
     {
        cout << "freed: " << mycart->name << endl;
        struct list *tmp = mycart->next;
        free(mycart);
        mycart = tmp;
     }
   }
};


int main(void)
{
   cart foodcart;

   foodcart.addToCart((char*)"bread");
   foodcart.addToCart((char*)"milk");
   foodcart.addToCart((char*)"water");

   foodcart.getContents();
   return 1;
}
