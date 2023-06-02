use ferris_says::*;
use rand::Rng;
use std::cmp::Ordering;
use std::io::{stdout, BufWriter };
use std::io;

fn main() {
    let stdout = stdout();
    let out = b"Guess the fucking number!(sorry)";
    let wid = 24;
    let mut writer = BufWriter::new(stdout.lock());
    say(out, wid, &mut writer).unwrap();    // won't work

    let secret_number = rand::thread_rng().gen_range(1..=100);
    println!("The fucking number(sorry) is {secret_number}");

    loop {
        println!("Please input your guess:");
        let mut guess = String::new();
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        println!("Your guess: {guess}");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };
        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!Fuck U!"),
            Ordering::Greater => println!("Too big!Fuck U!"),
            Ordering::Equal => {
                println!("You WONG!FUCCK U!");
                break;
            }
        }
    }
}
