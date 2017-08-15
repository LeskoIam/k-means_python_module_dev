import ckmeans
import random
import time

N = 100000
K = 50

lat = [random.randint(1000, 2000) / 100. for _ in xrange(N)]
lon = [random.randint(4000, 5000) / 100. for _ in xrange(N)]

print "Version:", ckmeans.version(), "\n"

print "Star clustering ... "
master_start_time = time.time()
times = []
for cycle in range(100):
    cycle_start_time = time.time()
    ckmeans.k_means(lat, lon, K)
    cycle_end_time = time.time()
    times.append(cycle_end_time - cycle_start_time)
    print "{0},{1}".format(cycle + 1, times[-1])

print """\n
---------------------------------
N: {N}
K: {K}

Min: {_min}
Max: {_max}
Mean: {m}
---------------------------------
""".format(N=N, K=K, _min=min(times), _max=max(times), m=sum(times) / len(times))

print "Time to cluster {0} points in to {1} clusters {2} times was: {3} seconds".format(N, K,
                                                                                        cycle + 1,
                                                                                        (
                                                                                        time.time() - master_start_time))
