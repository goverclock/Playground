use std::collections::HashMap;

fn main() {
    // let mut v = vec![100, 32, 57];
    // for i in v {
    //     *i += 50;
    // }
    // println!("{:?}", v)
    let mut hm = HashMap::new();
    hm.insert(1, 2);
    let k = 1;
    let score = hm.get(&k).copied().unwrap_or(0);
    for (k, v) in &hm {

    }
    hm.insert(k, 1);
}

