pub struct Tokenizer {
    input: String,
    tokens: String,
    index: usize,
}

#[allow(dead_code)]
impl Tokenizer {
    pub fn new(input: &str, tokens: &str) -> Tokenizer {
        Tokenizer {
            input: input.to_string(),
            tokens: tokens.to_string(),
            index: 0,
        }
    }
}

impl Iterator for Tokenizer {
    type Item = String;

    fn next(&mut self) -> Option<String> {
        if self.index >= self.input.len() {
            None
        } else {
            let mut start = self.index;
            while start < self.input.len()
                && self.tokens.contains(self.input.chars().nth(start).unwrap())
            {
                start += 1;
            }
            if start == self.input.len() {
                return None;
            }
            let mut end = start;
            while end < self.input.len()
                && !self.tokens.contains(self.input.chars().nth(end).unwrap())
            {
                end += 1;
            }
            self.index = end;
            Some(self.input[start..end].to_string())
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

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
