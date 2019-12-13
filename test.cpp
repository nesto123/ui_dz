#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include<queue>
#include<utility>
using namespace std;

void f(queue < pair < int, int > > &q){

}


int main(){

std::vector< std::vector<int> > v ={{1,2},{3,4}}, v2;

v2=v;

for (size_t i = 0; i < v2.size(); i++) {
  for (size_t j = 0; j < v2[i].size(); j++) {
    std::cout << v2[i][j]<< " ";

  }std::cout << '\n';
}
  return 0;
}
