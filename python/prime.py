# prime numbers 
for i in xrange(2,100):
  count = 0
  for j in xrange(2,i):
    if (i % j == 0):  # have a remainder it fails!
      count += 1

  if count == 0:
    print "prime: %d" % i
  
