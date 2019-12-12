#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>

using namespace std;

void f(stack<int> &s){
  s.push(5);
}


int main(){
  stack<int> s;
  f(s);
  cout<< s.top()<<endl;
  return 0;
}
