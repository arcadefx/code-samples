# Name: fib
# Description: Paul's fibonacci
a=1
b=c=0
maxNum = 15

# xrange performs faster
for x in xrange(1,maxNum):
   c = a + b
   b = a
   a = c
   print c 
