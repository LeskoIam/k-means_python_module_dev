import testmodule
import random
import time

print dir(testmodule)
print dir(testmodule.call_k_means)

print help(testmodule)

N = 13042
K = 50

lat = [random.randint(1000, 2000)/100. for _ in xrange(N)]
lon = [random.randint(4000, 5000)/100. for _ in xrange(N)]

s_time = time.time()
testmodule.call_k_means(lat, lon, K)

print "Time to cluster {0} points in to {1} clusters was: {2} seconds".format(N, K, (time.time() - s_time))

