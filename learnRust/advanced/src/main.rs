macro_rules! calculate {
    () => (0);
    (()) => (1);
    (()()$($p:tt)*) => (calculate!($($p)*) + calculate!(()$($p)*));
}

fn main() {
    let res = calculate!(()()()()()()());
    println!("{res}");
    let r#abstract = 1;
    println!("{}", r#abstract);
}
