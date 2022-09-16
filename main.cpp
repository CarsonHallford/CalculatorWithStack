#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Token.h"

bool solve(std::vector<Token> tokens);

int main() {
  std::string expression;
  std::cin >> expression;
  std::vector<Token> tokens = tokens_from_expression(expression);
  if (!solve(tokens)) {
    std::cout << "error\n";
  }
}

bool solve(std::vector<Token> tokens) {
  std::stack<Token> stack;
  for (Token &t : tokens) {
    // TODO: implement this!
    // Rules
    // 1: if we get one of (+* then push
    if (t.is_left_paren() || t.is_add() || t.is_multiply()) {
      stack.push(t);
    }
    // 2: if we get ) then go back and reduce (a) to a
    else if (t.is_right_paren()) {
      if (stack.size() == 0) {
        return false;
      }

      else {
        Token tt = stack.top();
        stack.pop();
        if (stack.size() > 1 &&
            (stack.top().is_add() || stack.top().is_multiply())) {
          if (stack.top().is_add()) {
            stack.pop();
            Token num2 = (stack.top().number() + tt.number());
            stack.pop();
            stack.pop();
            stack.push(num2);

          } else {
            stack.pop();
            Token num2 = (stack.top().number() * tt.number());
            stack.pop();
            stack.pop();
            stack.push(num2);
          }
        } else {
          //(a) -> a
          if (stack.size() > 0) {
            stack.pop();
          } else {
            return false;
          }
          stack.push(tt);
          if (stack.size() >= 3) {
            Token oldTop = stack.top();
            stack.pop();
            if (stack.top().is_add() || stack.top().is_multiply()) {
              if (stack.top().is_add()) {
                stack.pop();
                Token sum = (oldTop.number() + stack.top().number());
                stack.pop();
                stack.push(sum);
              } else {
                stack.pop();
                Token product = (oldTop.number() * stack.top().number());
                stack.pop();
                stack.push(product);
              }

            } else {
              stack.push(oldTop);
            }
          }
        }
      }
    }
    // 3: if we get number and stack is empty then push
    else if (t.is_number() && stack.size() == 0) {
      stack.push(t);
    }
    // 4: if we get number and previous is ( then push
    else if (t.is_number() && stack.top().is_left_paren()) {
      stack.push(t);
    }
    // 5: if we get number and previous is +* then go back
    else if (t.is_number() &&
             (stack.top().is_add() || stack.top().is_multiply())) {
      if (stack.top().is_add()) {
        stack.pop();
        Token sum = (stack.top().number() + t.number());
        stack.pop();
        stack.push(sum);
      } else {
        stack.pop();
        Token product = (stack.top().number() * t.number());
        stack.pop();
        stack.push(product);
      }
      //    calculate result and reduce a+b to c
    }
    // 6: anything else is an error
  }

  // Ensure that we only have one item left, and it is a number.
  if (stack.size() != 1 || !stack.top().is_number()) {
    return false;
  }

  // Print the result and return.

  std::cout << stack.top().number() << std::endl;
  return true;
}