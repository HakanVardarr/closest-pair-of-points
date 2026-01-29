use crate::point::Point;
use std::collections::HashMap;

pub fn run(points: &[Point]) -> (Point, Point) {
    assert!(points.len() >= 2, "En az iki nokta gerekli");

    let mut x_sorted = points.to_vec();
    x_sorted.sort_unstable_by_key(|p| p.x);

    let mut y_table: HashMap<Point, i32> = HashMap::new();

    let p0 = x_sorted[0];
    let p1 = x_sorted[1];

    let mut result = (p0, p1);
    let mut smallest = p0.distance(&p1);
    let mut t = 0;

    y_table.insert(p0, p0.y);
    y_table.insert(p1, p1.y);

    for i in 2..points.len() {
        let current = x_sorted[i];
        while x_sorted[t].x <= current.x - smallest as i32 {
            y_table.remove(&x_sorted[t]);
            t += 1;
        }

        for (p, p_y) in &y_table {
            if (p_y - current.y < smallest as i32)
                && (p != &current)
                && (current.distance(p) < smallest)
            {
                smallest = current.distance(p);
                result.0 = current;
                result.1 = *p;
            }
        }

        y_table.insert(current, current.y);
    }

    result
}
