#[derive(Debug, PartialEq, Eq, PartialOrd, Ord, Clone, Copy, Hash)]
pub struct Point {
    pub x: i32,
    pub y: i32,
}

impl Point {
    pub fn random(range: u32) -> Self {
        Self {
            x: fastrand::u32(0..range) as i32,
            y: fastrand::u32(0..range) as i32,
        }
    }

    pub fn distance(&self, other: &Point) -> f32 {
        let dx = (self.x - other.x) as f32;
        let dy = (self.y - other.y) as f32;
        (dx * dx + dy * dy).sqrt()
    }
}

pub fn generate_points(count: u32, range: u32) -> Vec<Point> {
    (0..count).map(|_| Point::random(range)).collect()
}
