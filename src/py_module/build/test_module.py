import ckmeans
import random
import time

print dir(ckmeans)
print dir(ckmeans.k_means)

N = 10  # 13042
K = 2

lat = [random.randint(1000, 2000)/100. for _ in xrange(N)]
lon = [random.randint(4000, 5000)/100. for _ in xrange(N)]

s_time = time.time()
ans = ckmeans.k_means(lat, lon, K)

# print "ANS:", ans
print "Time to cluster {0} points in to {1} clusters was: {2} seconds".format(N, K, (time.time() - s_time))
