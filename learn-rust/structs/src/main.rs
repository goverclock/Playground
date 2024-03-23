struct User {
    email: String,
    username: String,
}

fn main() {
    let u1 = build_user(String::from("e"), String::from("u"));
    println!("{} {} ", u1.username, u1.email);

    let u2 = User {
        email: String::from("fucking email"),
        ..u1
    };
    println!("{} {}", u2.email, u2.username);
}

fn build_user(e: String, u: String) -> User {
    User {
        email: e,
        username: u,
    }
}
