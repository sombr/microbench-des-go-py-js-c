package main

import "fmt"
import "time"
import "github.com/sombr/go-container-heap"

func main() {
    heapMax := 10000

    var err error
    simTime := 0
    total := 5000000

    heap := heapq.NewHeap[int](heapMax, func (a *int, b *int) bool { return (a != nil) && (b == nil || *a < *b) })

    start := time.Now()

    for idx := 0; idx < total; idx += 1 {
        if heap.Size() >= heapMax {
            simTime, err = heap.Pop()
            if err != nil {
                panic(err)
            }
        }

        diff := 20
        if idx % 2 == 0 {
            diff = 2
        } else if idx % 3 == 0 {
            diff = 5
        }

        err := heap.Push(simTime + diff)
        if err != nil {
            panic(err)
        }
    }

    for heap.Size() > 0 {
        simTime, err = heap.Pop()
        if err != nil {
            panic(err)
        }
    }

    elapsed := time.Since(start)

    fmt.Printf("GO simulation result %d, runtime: %.2f ms\n", simTime, float64(elapsed.Microseconds()) / 1000.0)
}
