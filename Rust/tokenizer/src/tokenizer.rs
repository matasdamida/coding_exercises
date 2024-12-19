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
