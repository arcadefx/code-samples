class Demo:
  __privNumber = '555-555-5555'
  __privCode = 777
  elements = []

  def greetUser(self):
    return "Welcome to the Python refresher"

  def add(self,a,b):
    return a+b

  def countTo(self,maxNum):
    for x in range(1,maxNum):
      print "val = %d" % x

  def printArray(self,data):
    for x in data:
      print x
      if x == "stop":
        break
    self.tellSecret()

  def tellSecret(self):
     print "secret number is %r\naccess code %d" % (self.__privNumber, int(self.__privCode))

  def splitBasket(self,basket):
     return basket.split(',')

  def arrayFactory(self):
     self.elements.append('apple')
     self.elements.append('pie')
     for entry in self.elements:
       print "element %s" %entry
