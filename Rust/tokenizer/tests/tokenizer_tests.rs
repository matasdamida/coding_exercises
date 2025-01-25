#[path = "../src/tokenizer.rs"]
mod tokenizer;

#[cfg(test)]
mod tokenizer_tests {
    use super::tokenizer::*;

    #[test]
    fn one_separator() {
        assert_eq!(
            Tokenizer::new("a,b,c", ",")
                .into_iter()
                .collect::<Vec<String>>(),
            vec!["a".to_string(), "b".to_string(), "c".to_string()]
        );
    }

    #[test]
    fn two_separators() {
        assert_eq!(
            Tokenizer::new("a,b;c", ",;")
                .into_iter()
                .collect::<Vec<String>>(),
            vec!["a".to_string(), "b".to_string(), "c".to_string()]
        );
    }

    #[test]
    fn empty_input() {
        assert_eq!(
            Tokenizer::new("", " ").into_iter().collect::<Vec<String>>(),
            Vec::<String>::new()
        );
    }

    #[test]
    fn no_empty_strings() {
        assert_eq!(
            Tokenizer::new("a,b,,c", ",")
                .into_iter()
                .collect::<Vec<String>>(),
            vec!["a".to_string(), "b".to_string(), "c".to_string()]
        );
    }

    #[test]
    fn spaces() {
        assert_eq!(
            Tokenizer::new(" , ", ",")
                .into_iter()
                .collect::<Vec<String>>(),
            vec![" ".to_string(), " ".to_string()]
        );
    }

    #[test]
    fn input_only_separators() {
        assert_eq!(
            Tokenizer::new(",", ",")
                .into_iter()
                .collect::<Vec<String>>(),
            Vec::<String>::new()
        );
    }
}

#[cfg(test)]
mod split_tests {
    #[test]
    fn one_separator() {
        assert_eq!(
            "a,b,c".split(",").collect::<Vec<&str>>(),
            vec!["a", "b", "c"]
        );
    }

    #[test]
    fn two_separators() {
        assert_eq!(
            "a,b;c".split(&[',', ';']).collect::<Vec<&str>>(),
            vec!["a", "b", "c"]
        );
    }

    #[test]
    fn multiple_separators() {
        assert_ne!(
            "a, b".split(&[',', ' ']).collect::<Vec<&str>>(),
            vec!["a", "b"]
        );
        assert_eq!(
            "a, b"
                .split(&[',', ' '])
                .filter(|c| !c.is_empty())
                .collect::<Vec<&str>>(),
            vec!["a", "b"]
        )
    }
}
