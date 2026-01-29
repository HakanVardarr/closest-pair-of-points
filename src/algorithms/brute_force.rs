use crate::point::Point;

/// O(n²) brute force algorithm - All Pairs
pub fn run(points: &[Point]) -> (Point, Point) {
    assert!(points.len() >= 2, "Points size must be >= 2");

    let mut result = (points[0], points[1]);
    let mut smallest = result.0.distance(&result.1);

    for i in 0..points.len() - 1 {
        for j in i + 1..points.len() {
            let d = points[i].distance(&points[j]);
            if d < smallest {
                smallest = d;
                result = (points[i], points[j]);
            }
        }
    }

    result
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::point::Point;

    #[test]
    fn test_cpp_ap_simple() {
        let points = vec![
            Point { x: 0, y: 0 },
            Point { x: 1, y: 1 },
            Point { x: 10, y: 10 },
        ];
        let (p1, p2) = run(&points);
        assert!(p1.distance(&p2) < 2.0);
    }
}
