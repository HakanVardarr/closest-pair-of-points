use crate::point::Point;
use std::time::{Duration, Instant};

pub struct BenchmarkResult {
    pub name: String,
    pub duration: Duration,
    _pair: (Point, Point),
    pub distance: f32,
}

impl BenchmarkResult {
    pub fn print(&self) {
        println!(
            "{:20} | {:10.6}s | dist: {:.2}",
            self.name,
            self.duration.as_secs_f64(),
            self.distance
        );
    }
}

pub fn run_benchmark<F>(name: &str, points: &[Point], func: F) -> BenchmarkResult
where
    F: FnOnce(&[Point]) -> (Point, Point),
{
    let start = Instant::now();
    let pair = func(points);
    let duration = start.elapsed();
    let distance = pair.0.distance(&pair.1);

    BenchmarkResult {
        name: name.to_string(),
        duration,
        _pair: pair,
        distance,
    }
}
