#[derive(Debug)]
struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

impl User {
    fn new() -> Self {
        Self {
            active: false,
            username: String::from("nameless"),
            email: String::from("emailless"),
            sign_in_count: 0,
        }
    }

    fn say(&self, s: &str) {
        println!("{} says {}", self.username, s);
    }
}

struct Color(u32, u32, u32);

// struct UnitLikeStruct;

fn build_user(username: String) -> User {
    User {
        active: true,
        username,
        email: String::from("ahh"),
        sign_in_count: 1,
    }
}

fn main() {
    let mut user1 = User {
        active: true,
        username: String::from("Hell"),
        email: String::from("lol"),
        sign_in_count: 1,
    };
    user1.email = String::from("good");
    println!("{}", user1.active);

    let user2 = build_user(String::from("Sheldon"));
    println!("{} {}", user2.username, user2.sign_in_count);

    let user3 = User {
        username: String::from("haha"),
        ..user2
    };
    println!("{}", user3.email);

    // println!("{} {}", user2.username, user2.email);
    println!("{} {}", user2.username, user2.sign_in_count);

    let black = Color(0, 0, 0);
    println!("{}", black.0);

    // let crap1 = UnitLikeStruct;
    // let crap2 = UnitLikeStruct;

    dbg!(&user1);
    println!("user1 is {:#?}", user1);
    user1.say("haha I'm user1");

    let test_user = User::new();
    test_user.say("hey I'm new in town");
}
