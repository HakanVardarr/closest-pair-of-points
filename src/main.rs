mod algorithms;
mod benchmark;
mod point;

use algorithms::{brute_force, divide_conquer};
use benchmark::run_benchmark;
use point::generate_points;

fn main() {
    let sizes = vec![100, 1_000, 10_000, 100_000];
    let range = 1_000_000;

    println!("Closest Pair Problem - Benchmark\n");
    println!(
        "{:20} | {:>10} | {:>10}",
        "Algorithm", "Time (s)", "Distance"
    );
    println!("{}", "-".repeat(50));

    for size in sizes {
        println!("\nN = {} points:", size);
        let points = generate_points(size, range);

        let ap = run_benchmark("Brute Force", &points, brute_force::run);
        ap.print();

        let dc = run_benchmark("Divide & Conquer", &points, divide_conquer::run);
        dc.print();

        let epsilon = 0.01;
        if (ap.distance - dc.distance).abs() < epsilon {
            println!("All results match!");
        } else {
            println!("Results differ!");
        }
    }
}
