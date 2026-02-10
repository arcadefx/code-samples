from demo import Demo

class FooClass(Demo):
   def sayhello(self):
     print("hello")
     print(self.greet())

obj = Demo()
ret = obj.greet()
print(ret)

ret = obj.add(2,5)
print(ret)

obj.countTo(5);

# array
obj.printArray(['start',1,2,'three',4,5,'laugh','stop',6,7])

for fruit in obj.splitBasket("apple,bannana"):
  print("item %s" %fruit)

# use array on the fly
obj.element()

stuff = {'name':'Paul','phone':'444-444-4444'}
print(stuff['name'])

# object inheritance
objInherit = FooClass()
objInherit.sayhello()

# substring that string
thing = "some things to look at"
for letter in thing:
  print(letter, end=' ')

print("")

# using a alt method
for i in range(0,len(thing)):
  print(thing[i], end=' ')

# print more than one number
print("%02d %02d %02d" % (5,10,7))
