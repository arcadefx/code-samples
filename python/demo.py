class Demo:
  __privNumber = '555-555-5555'
  __privCode = 777
  elements = []
  
  def __init__(self):
    print "init launch"

  def greet(self):
    return "nothing special"

  def finish(self):
    return "Bye"

  def add(self,a,b):
    return a+b

  def countTo(self,maxNum):
    for x in xrange(1,maxNum):  # range() creats all numbers used or not, xrange() create as needed
      print "val = %d" % x

  def printArray(self,data):
    for x in data:
      print x
      if x == "stop":
        break
      elif x == "laugh":
        print "HAHAHA"
    self.tellSecret()

  def tellSecret(self):
     print "secret number is %r\naccess code %d" % (self.__privNumber, int(self.__privCode))

  def splitBasket(self,basket):
     return basket.split(',')

  def element(self):
     self.elements.append('apple')
     self.elements.append('pie')
     for entry in self.elements:
       print "element %s" %entry
