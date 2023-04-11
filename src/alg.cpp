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
      default:
        return -1;
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
    default:
      return 0;
      break;
  }
}
int Reverse(std::string val) {
    int ival;
    std::string temp=val;
    for(int i=0; i<val.length();++i){
        int count = val.length() - 1 - i;
        temp[i] = val[count];
    }
    val = temp;
   ival = std::stoi(val);
    return ival;
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
        }
        else {
            outstr += ch;
            outstr += " ";
            continue;
        }
     }
     else {
         Operator op(ch);
         Operator top(stack1.WatchTop());
         curprior = top.prioriti;
         if (op.prioriti == 1) {
             while (top.GivePrioriri() != 0) {
                 outstr += stack1.Pop();
                 outstr += " ";
                 top.oper = stack1.WatchTop();
                 top.GivePrioriri();
             }
             stack1.IncTop();
             top.oper = stack1.WatchTop();
             top.GivePrioriri();
             curprior = top.prioriti;
             continue;
         }
         else if (op.prioriti == 0 || op.prioriti > curprior || stack1.isEmpty()) {
             stack1.Push(ch);
             curprior = op.prioriti;
             continue;
         }
         else if (op.prioriti <= curprior) {
             while (top.GivePrioriri() >= op.prioriti) {
                 outstr += stack1.Pop();
                 outstr += " ";
                 top.oper = stack1.WatchTop();
                 top.GivePrioriri();
             }
             stack1.Push(ch);
             curprior = op.prioriti;
             continue;
         }
     }
 }
 while (!(stack1.isEmpty())) {
     outstr += stack1.Pop();
     outstr += " ";
 }
 outstr.pop_back();
    return outstr;
}

int eval(std::string pref) {
    int res = 0;
    std::string sres;
    char str;
    int in;
    TStack<char, 100> stack1;
    for (int i = 0; i < pref.length(); ++i) {
        str = pref.c_str()[i];
        int f = 0;
        int s = 0;
        char ch = '+';
        if ('0' <= str && str <= '9') {
            if ('0' <= pref[i + 1] && pref[i + 1] <= '9') {
                stack1.Push(str);
                continue;
            }
            else {
                stack1.Push(str);
                stack1.Push(' ');
                continue;
            }
        }
            else {
            if (str == ' ') {
                continue;
            }
            else
            {
                
                char ch = str;
                std::string sf, ss;
                if (stack1.WatchTop() == ' ') {
                    stack1.Pop();
                }
                while(stack1.WatchTop() != ' ' && (!stack1.isEmpty()))
                {
                    ss += stack1.Pop();
                }
                if (stack1.WatchTop() == ' ') {
                    stack1.Pop();
                }
                while (stack1.WatchTop() != ' ' && (!stack1.isEmpty()))
                {
                    sf += stack1.Pop();
                }
                int s = Reverse(ss);
                int f = Reverse(sf);
                int result = SwitchOperator(f, s, ch);
                std::string sresult= std::to_string(result);
                for(int j=0;j<sresult.length();++j)
                {
                    stack1.Push(sresult[j]);
                }
                stack1.Push(' ');
            }
            }
    }
    while (!(stack1.isEmpty())) {
        sres += stack1.Pop();
    }
    res = Reverse(sres);
    return res;
}
