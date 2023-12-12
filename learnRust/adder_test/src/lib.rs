pub fn add(left: usize, right: usize) -> usize {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn works() {
        let result = add(2, 1);
        assert_ne!(result, 2, "lefttt={}", result);
    }

    #[test]
    fn maybework() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    #[test]
    #[ignore]
    #[should_panic(expected = "lol")]
    fn notworking() {
        panic!("lol");
    }
}
