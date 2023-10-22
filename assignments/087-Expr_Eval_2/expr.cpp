#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include "expr.hpp"

Expression * parse(std::string &line);

const std::string OPERATORS = "+-*/";

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void consumeInput(std::string &s, size_t length = 1) {
    s.erase(0,length);
}

Expression * makeExpr(char op, Expression * lhs, Expression * rhs) {
  switch(op) {
  case '+':
    return new PlusExpression(lhs,rhs);
  case '-':
    return new MinusExpression(lhs,rhs);
  case '*':
    return new TimesExpression(lhs,rhs);
  case '/':
    return new DivExpression(lhs,rhs);
  default:
    std::cerr << "Impossible op char: " << op << "\n";
    abort();
  }
}

bool isValidOp(char c) {
      return OPERATORS.find(c) != std::string::npos;
}

Expression * parseOp(std::string &line) {
  ltrim(line);
  char op = line[0];
  if (!isValidOp(op)) {
    std::cerr << "Invalid op: "<< op<< "\n";
    return nullptr;
  }
  consumeInput(line);
  Expression * lhs = parse(line);
  if (lhs == nullptr) {
    return nullptr;
  }

  Expression * rhs = parse(line);
  if (rhs == nullptr) {
    delete lhs;
    return nullptr;
  }
  ltrim(line);
  if (line[0] == ')') {
    consumeInput(line);
    return makeExpr(op,lhs,rhs);
  }
  std::cerr <<"Expected ) but found " << line << "\n";
  delete lhs;
  delete rhs;
  return nullptr;
}

Expression * parse(std::string &line) {
    ltrim(line);

    if (line.length() == 0) {
        std::cerr << "End of line found mid expression!\n";
        return nullptr;
    }
    else if (line[0] == '(') {     // (op E E)
        consumeInput(line);
        return parseOp(line);
    }
    else {    //number
        try {
            size_t pos;
            long num = stol(line,&pos);
            consumeInput(line,pos);
            return new NumExpression(num);
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "Expected a number, but found " << line << '\n';
	          std::cerr << "Invalid argument: " << ia.what() << '\n';
            return nullptr;
        }
    }
}


int main(void) {
    std::string line;
    while (getline(std::cin,line)) {
    std::cout << "Read expression: " << line << "\n";

    Expression * expr = parse(line);
    if (expr != nullptr) {
      std::cout << "Parsed expression to: " << expr->toString() << "\n";
      //std::cout << "Evaluated expression to: " << expr->evaluate() << "\n";
      std::cout << "(evaluation will be done in the future)\n";
      delete expr;
    }
    else {
      std::cout << "Could not parse expression, please try again.\n";
    }
  }

  return EXIT_SUCCESS;
}

