package main

import "fmt"
import "time"
import "container/heap"

type IntHeap []uint32

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntHeap) Push(x any) {
    *h = append(*h, x.(uint32))
}

func (h *IntHeap) Pop() any {
    old := *h
    n := len(old)
    x := old[n-1]
    *h = old[0 : n-1]
    return x
}

func NewHeap(capacity int) *IntHeap {
    var res IntHeap = make([]uint32, 0, capacity)
    return &res
}

func main() {
    var heapMax int = 10000

    var err error
    var simTime uint32 = 0
    var total uint32 = 5000000

    var h *IntHeap = NewHeap(heapMax)

    start := time.Now()

    for idx := uint32(0); idx < total; idx += 1 {
        if h.Len() >= heapMax {
            simTime = heap.Pop(h).(uint32)
        }

        var diff uint32 = 20
        if idx % 2 == 0 {
            diff = 2
        } else if idx % 3 == 0 {
            diff = 5
        }

        heap.Push(h, simTime + diff)
    }

    for h.Len() > 0 {
        simTime = heap.Pop(h).(uint32)
        if err != nil {
            panic(err)
        }
    }

    elapsed := time.Since(start)

    fmt.Printf("GO simulation result %d, runtime: %.2f ms\n", simTime, float64(elapsed.Microseconds()) / 1000.0)
}
