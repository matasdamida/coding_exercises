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
