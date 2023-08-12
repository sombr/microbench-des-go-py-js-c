import heapq
import time

def main():
    heapMax = 10000

    simTime = 0
    total = 5000000

    heap = []

    start = time.time_ns()

    for idx in range(total):
        if len(heap) >= heapMax:
            simTime = heapq.heappop(heap)

        diff = 2 if idx % 2 == 0 else 5 if idx % 3 == 0 else 20

        heapq.heappush(heap, simTime + diff)

    while len(heap) > 0:
        simTime = heapq.heappop(heap)

    elapsed = time.time_ns() - start

    print("PY simulation result %d, runtime: %.2f ms" % ( simTime, (elapsed // 1000) / 1000.0 ))

main()
