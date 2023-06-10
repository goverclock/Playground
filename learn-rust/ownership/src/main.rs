fn main() {
    let ret = is_palindrome(110111);
    println!("{ret}")
}

fn is_palindrome(x: i32) -> bool {
    let s = x.to_string();
    let l = s.len();
    for i in 0..l / 2 {
        let lc = s.chars().nth(i).unwrap_or('\0');
        let rc = s.chars().nth(l - i - 1).unwrap_or('\0');
        println!("lc={} rc={}", lc, rc);
        if lc != rc {
            return false;
        }
    }

    true
}
