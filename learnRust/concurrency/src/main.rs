use std::thread;
use std::sync::{Arc, Mutex};
use std::time::Duration;

fn main() {
    // let handle = thread::spawn(|| {
    //     for i in 1..10 {
    //         println!("hello {}", i);
    //         thread::sleep(Duration::from_millis(1));
    //     }
    // });

    // for i in 1..5 {
    //     println!("hellno {}", i);
    //     thread::sleep(Duration::from_millis(1));
    // }

    // handle.join().unwrap();


    // let (tx, rx) = mpsc::channel();

    // thread::spawn(move || {
    //     let vals = vec![
    //         String::from("Hello"),
    //         String::from("wordle"),
    //         String::from("no"),
    //         String::from("world"),
    //     ];

    //     for v in vals {
    //         tx.send(v).unwrap();
    //         thread::sleep(Duration::from_secs(1));
    //     }
    // });

    // for received in rx {
    //     println!("got {received}");
    // }

    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];
    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            *num += 1;
        });
        handles.push(handle);
    }
    for h in handles {
        h.join().unwrap();
    }
    println!("res={}", *counter.lock().unwrap());
}
