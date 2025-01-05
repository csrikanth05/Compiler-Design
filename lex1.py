import re
import keyword

pyword = keyword.kwlist

TOKEN_TYPES = {
    'KEYWORD': r'\b(' + '|'.join(pyword) + r')\b',
    'IDENTIFIER': r'[a-zA-Z_][a-zA-Z0-9]*',
    'NUMBER': r'\d+',
    'WHITESPACE': r'\s+'
}

class Lexer:
    def __init__(self, token_types):
        self.token_types = [(name, re.compile(pattern)) for name, pattern in token_types.items()]

    def tokenize(self, text):
        tokens = []
        while text:
            match = None
            for name, pattern in self.token_types:
                match = pattern.match(text)
                if match:
                    value = match.group(0)
                    if name != 'WHITESPACE':
                        tokens.append((name, value))
                    text = text[len(value):]
                    break
        return tokens

lexer = Lexer(TOKEN_TYPES)


input_code = input("Enter code to tokenize:\n")

try:
    tokens = lexer.tokenize(input_code)
    for token in tokens:
        print(token)
except ValueError as e:
    print(e)


