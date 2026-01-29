mod algorithms;
mod benchmark;
mod point;

use algorithms::{brute_force, divide_conquer, plane_sweep};
use benchmark::{CsvWriter, run_benchmark};
use point::generate_points;

fn main() {
    let sizes = vec![100, 500, 1_000, 5_000, 10_000];
    let range = 1_000_000;
    let csv_file = "benchmark_results.csv";

    let csv = CsvWriter::new(csv_file);
    if let Err(e) = csv.init() {
        eprintln!("Failed to initialize CSV: {}", e);
        return;
    }

    println!("Closest Pair Problem - Benchmark\n");
    println!(
        "{:20} | {:>10} | {:>10}",
        "Algorithm", "Time (s)", "Distance"
    );
    println!("{}", "-".repeat(50));

    for size in sizes {
        println!("\nN = {} points:", size);
        let points = generate_points(size, range);

        let ap = run_benchmark("brute_force", &points, brute_force::run);
        ap.print();

        let dc = run_benchmark("divide_conquer", &points, divide_conquer::run);
        dc.print();

        let ps = run_benchmark("plane_sweep", &points, plane_sweep::run);
        ps.print();

        let epsilon = 0.01;
        let matches = (ap.distance - dc.distance).abs() < epsilon
            && (ap.distance - ps.distance).abs() < epsilon;

        if matches {
            println!("All results match!");
        } else {
            println!("Results differ!");
        }

        if let Err(e) = csv.write_batch(size, &[ap, dc, ps]) {
            eprintln!("Failed to write CSV: {}", e);
        }
    }

    println!("\nResults written to {}", csv_file);
}
