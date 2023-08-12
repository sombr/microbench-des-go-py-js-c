use std::env;
use std::time::Instant;
use std::collections::BinaryHeap;

fn main() {
    let args: Vec<String> = env::args().collect();

    let heap_max: isize = args[1].parse().unwrap();

    let mut sim_time: isize = 0;
    let total: isize = args[2].parse().unwrap();

    let mut heap: BinaryHeap<isize> = BinaryHeap::new();

    let start = Instant::now();

    for idx in 0..total {
        if heap.len() as isize >= heap_max {
            sim_time = - heap.pop().unwrap();
        }

        let diff = if idx % 2 == 0 { 2 } else {
                   if idx % 3 == 0 { 5 } else { 20 } };

        heap.push(-(sim_time + diff));
    }

    while heap.len() > 0 {
        sim_time = - heap.pop().unwrap();
    }

    let duration = start.elapsed();

    println!("RUST simulation result {}, runtime: {} ms", sim_time, (duration.as_micros() as f64) / 1000.0);
}
