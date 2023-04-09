// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
class Operator {
public:
  Operator(char op) {
    this->oper = op;
    this->prioriti = GivePrioriri();
  };
  int prioriti;
  char oper;
  int GivePrioriri() {
    switch (oper) {
      case '+':
      case '-':
        return 2;
        break;
      case '*':
      case'/':
        return 3;
        break;
      case ')':
        return 1;
        break;
      case '(':
        return 0;
        break;
    }
  }
};

int SwitchOperator(int f, int s, char op) {
  switch (op) {
    case '+':
      return f + s;
      break;
    case '-':
      return f-s;
      break;
    case '*':
      return f * s;
      break;
    case'/':
      return f/s;
      break;
  }
}
std::string infx2pstfx(std::string inf) {
  const int size = inf.length();
  TStack<char, 100> stack1;
  std::string outstr;
  char ch;
  int curprior = -1;
  for (int i = 0; i < inf.length(); ++i) {
    ch=inf[i];
    if ('0' <= ch && ch <= '9') {
      if ('0' <= inf[i + 1] && inf[i + 1] <= '9') {
        outstr += ch;
        continue;
      } else {
          outstr += ch;
          continue;
        }
    } else {
        Operator op(ch);
        Operator top(stack1.WatchTop());
        if (op.prioriti == 1) {
          while (top.GivePrioriri() != 0) {
            outstr += stack1.Pop();
            top.oper = stack1.WatchTop();
          }
          stack1.IncTop();
          curprior = op.prioriti;
          continue;
        } else if (op.prioriti == 0 || op.prioriti > curprior || stack1.isEmpty()) {
            stack1.Push(ch);
            curprior = op.prioriti;
            continue;
          } else if (op.prioriti <= curprior) {
              while (top.GivePrioriri() >= op.prioriti) {
                outstr += stack1.Pop();
                top.oper = stack1.WatchTop();
              }
              stack1.Push(ch);
              curprior = op.prioriti;
              continue;
       }
     }
   }
  while (!(stack1.isEmpty())) {
    outstr += stack1.Pop();
  }
  return outstr;
}

int eval(std::string pref) {
  int res = 0;
  char str;
  int in, f, s;
  TStack<int, 100> stack1;
  for (int i = 0; i < pref.length(); ++i) {
    str = pref.c_str()[i];
    in = str - '0';
    if (0 <= in && in <= 9) {
      stack1.Push(in);
    } else {
        char ch = str;
        s= stack1.Pop();
        f= stack1.Pop();
        int result = SwitchOperator(f, s, ch);
        stack1.Push(result);
      }
    }
  res = stack1.Pop();
  return res;
  return 0;
}
