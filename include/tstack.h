// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  T arr[size];
  int top;
  
 public:
  TStack() :top(-1) {}
  ~TStack() {}
  void Push(const T& value) {
    arr[++top] = value;
  }
  const T& Pop() {
    return arr[top--];
  }
  bool isEmpty()const {
    return top == -1;
  }
  bool isFull() const {
    return top == size;
  }
  const T& Get() const {
    return top;
  }
  T WatchTop() {
    return arr[top];
  }
  void IncTop() {
    --top;
  }
};

#endif  // INCLUDE_TSTACK_H_
