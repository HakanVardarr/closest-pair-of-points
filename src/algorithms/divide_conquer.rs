use crate::algorithms::brute_force;
use crate::point::Point;

/// O(n log n) divide and conquer algorithm
pub fn run(points: &[Point]) -> (Point, Point) {
    assert!(points.len() >= 2, "Points size must be >= 2");

    let mut p_x: Vec<Point> = points.to_vec();
    let mut p_y: Vec<Point> = points.to_vec();

    p_x.sort_unstable_by_key(|p| p.x);
    p_y.sort_unstable_by_key(|p| p.y);

    cpp_dc_recursive(&p_x, &p_y)
}

fn cpp_dc_recursive(p_x: &[Point], p_y: &[Point]) -> (Point, Point) {
    let n = p_x.len();

    if n <= 3 {
        return brute_force::run(p_x);
    }

    let mid = n / 2;
    let mid_point = p_x[mid];

    let (left_y, right_y): (Vec<Point>, Vec<Point>) = p_y.iter().partition(|p| p.x < mid_point.x);

    let left_pair = cpp_dc_recursive(&p_x[..mid], &left_y);
    let right_pair = cpp_dc_recursive(&p_x[mid..], &right_y);

    let mut best = if left_pair.0.distance(&left_pair.1) < right_pair.0.distance(&right_pair.1) {
        left_pair
    } else {
        right_pair
    };
    let mut smallest = best.0.distance(&best.1);

    let strip: Vec<Point> = p_y
        .iter()
        .filter(|p| (p.x - mid_point.x).abs() as f32 <= smallest)
        .copied()
        .collect();

    for i in 0..strip.len() {
        for j in (i + 1)..strip.len() {
            if (strip[j].y - strip[i].y) as f32 >= smallest {
                break;
            }

            let d = strip[i].distance(&strip[j]);
            if d < smallest {
                smallest = d;
                best = (strip[i], strip[j]);
            }
        }
    }

    best
}
