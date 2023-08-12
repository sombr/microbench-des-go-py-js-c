import java.time.Instant;
import java.time.Duration;
import java.util.PriorityQueue;

public class Main {
    public static void main(String[] args) {
        int heapMax = 10000;

        int simTime = 0;
        int total = 5000000;

        PriorityQueue<Integer> heap = new PriorityQueue<Integer>(heapMax);

        Instant start = Instant.now();

        for (int idx = 0; idx < total; idx += 1) {
            if ( heap.size() >= heapMax ) {
                simTime = heap.poll();
            }

            int diff = idx % 2 == 0 ? 2 :
                       idx % 3 == 0 ? 5 : 20;

            heap.add(simTime + diff);
        }

        while (heap.size() > 0) {
            simTime = heap.poll();
        }

        Duration elapsed = Duration.between(start, Instant.now());

        System.out.printf("JAVA simulation result %d, runtime: %.2f ms\n", simTime, ((double) (elapsed.toNanos() / 1000) / 1000.0));

    }
}
