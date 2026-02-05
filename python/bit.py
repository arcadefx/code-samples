# Name: Bit Manipulator
# Description: Showing how to do simple math bit shifting and then setting/removing bits
# by Paul Cardwell

n = 10

n <<= 1 # multiply by 2
print "n: %d" % int(n)

n >>= 1 # divide by 2, faster to do with no fpu (float point unit) :)
print "n: %d" % int(n)

# flag

def setbit(n,v):
    n |= v
    print "n: ", n
    return n

def removebit(n, v):
    n &= ~v
    return n

def isbit(n,v):
    if (n & v == v):
      return 1
    else:
      return 0

n=0
read=64
write=128

n = setbit(n,read)
n = setbit(n,write)
print "read: %d" % isbit(n,read)

n = removebit(n,read)
print "read removed so check for read: %d" % isbit(n,read)
print "write: %d" % isbit(n,write)


