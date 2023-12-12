// use snake_case in Rust!

fn main() {
    let a: [i8; 4] = [1, 2, 3, 4];
    let b = [123; 4];
    println!("{} {}", a[0], b[3]);

    fuck(123);
}

fn fuck(x: i32) -> i32 {
    println!("lol{}", { 2 });
    x
}
