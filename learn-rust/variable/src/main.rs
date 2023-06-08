fn main() {
    the_fuck(-128, 'h');
}

fn the_fuck(x: i8, u: char) {
    println!("THE FUCK!{} {}", x, u);
    fn y() -> i8 {
        19
    }
    let q = y;
    println!("{}", q()) 
}
