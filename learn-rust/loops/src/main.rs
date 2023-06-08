fn main() {
    for i in 1..10 {
        println!("{i}th fib is {}", fibn(i))
    }
}

fn fibn(n: i32) -> i32 {
    if n <= 2 {
        1
    } else {
        fibn(n - 1) + fibn(n - 2)
    }
}
