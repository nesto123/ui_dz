#include <iostream>
#include <vector>

using namespace std;



int main(){
  vector< vector<int> > map;

  map.resize(5);
  for( int i = 0 ; i < map.size() ; ++i )
    map[i].resize(4);
    map[4][3]=9;
    cout<<map[4][3]<<endl;
  return 0;
}
