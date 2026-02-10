
class CartDemo:

  def __init__(self):
    print('cart demo')
    self.cart = []

  def add(self, item=''):
     if len(item):
       print("add to cart: %s" %item)
       self.cart.append(item)

  def show(self):
       for item in self.cart:
         print("item=%s" % item)
       print('total items %d' % len(item))

cart = CartDemo()

cart.add('apple')
cart.add('milk')
cart.show()

