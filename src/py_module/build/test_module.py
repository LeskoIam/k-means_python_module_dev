import testmodule
import random

print dir(testmodule)
print dir(testmodule.call_k_means)

print help(testmodule)
print help(testmodule.call_k_means)

N = 2000

lat = [random.randint(1000, 2000)/100. for _ in xrange(N)]
lon = [random.randint(4000, 5000)/100. for _ in xrange(N)]
testmodule.call_k_means(lat,
                        lon,
                        50)


