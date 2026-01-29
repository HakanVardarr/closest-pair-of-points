use crate::point::Point;
use std::fs::OpenOptions;
use std::io::Write;
use std::time::{Duration, Instant};

pub struct BenchmarkResult {
    pub name: String,
    pub duration: Duration,
    pub _pair: (Point, Point),
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

pub struct CsvWriter {
    filename: String,
}

impl CsvWriter {
    pub fn new(filename: &str) -> Self {
        Self {
            filename: filename.to_string(),
        }
    }

    pub fn init(&self) -> std::io::Result<()> {
        if std::fs::metadata(&self.filename).is_err() {
            let mut file = std::fs::File::create(&self.filename)?;
            writeln!(file, "n_points,algorithm,time_seconds,distance,matches")?;
        }
        Ok(())
    }

    pub fn write_result(
        &self,
        n_points: u32,
        result: &BenchmarkResult,
        matches: bool,
    ) -> std::io::Result<()> {
        let mut file = OpenOptions::new()
            .create(true)
            .append(true)
            .open(&self.filename)?;

        writeln!(
            file,
            "{},{},{:.6},{:.6},{}",
            n_points,
            result.name,
            result.duration.as_secs_f64(),
            result.distance,
            if matches { 1 } else { 0 }
        )?;

        Ok(())
    }

    pub fn write_batch(&self, n_points: u32, results: &[BenchmarkResult]) -> std::io::Result<()> {
        let epsilon = 0.01;
        let distances: Vec<f32> = results.iter().map(|r| r.distance).collect();
        let matches = distances.windows(2).all(|w| (w[0] - w[1]).abs() < epsilon);

        for result in results {
            self.write_result(n_points, result, matches)?;
        }

        Ok(())
    }
}
