#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

class Token {
 public:
  Token(int num) : is_num(true), num(num), other('x') {}
  Token(char other) : is_num(false), num(0), other(other) {}

  bool is_number() { return is_num; }
  int number() { return num; }

  bool is_add() { return other == '+'; }
  bool is_multiply() { return other == '*'; }
  bool is_left_paren() { return other == '('; }
  bool is_right_paren() { return other == ')'; }

 private:
  bool is_num;
  int num;
  char other;
};

std::vector<Token> tokens_from_expression(std::string expression) {
  std::vector<Token> tokens;
  for (char c : expression) {
    if (c >= '0' && c <= '9') {
      int num = c - '0';
      tokens.push_back(Token(num));
    } else {
      tokens.push_back(Token(c));
    }
  }
  return tokens;
}

#endif  // TOKEN_H