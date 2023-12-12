#[derive(Debug)]
enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn say(&self) {
        println!("{:?}", self)
    }
}

fn message_resolve(m: Message) -> String {
    match m {
        Message::Quit => String::from("hahaha"),
        Message::ChangeColor(x, y, z) => String::from("lll"),
        Message::Move { x, y } => String::from("a"),
        Message::Write(s) => s,
    }
}

fn main() {
    let m = Message::Write(String::from("mess"));
    let q = Message::Quit;
    let c = Message::ChangeColor(12, 13, 14);
    m.say();
    q.say();
    c.say();

    // let none = Some(2);
    // println!("{}", none);

    let ret = message_resolve(c);
    println!("{ret}");

    let some_val = Some(123);
    match some_val {
        Some(v) => println!("{v}"),
        None => (),
    }

    fn plus_one(x: Option<i32>) -> Option<i32> {
        match x {
            Some(i) => Some(i + 1),
            None => None,
        }
    }
    let five = Some(5);
    let six = plus_one(five);
    match six {
        Some(v) => println!("{v}"),
        None => (),
    }
}
