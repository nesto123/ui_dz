#include <iostream>
#include <vector>

using namespace std;

class Board{
public:
  vector< vector<int> > map;

  Board();
  bool input_initial_map( vector< vector<int> > initial_map);
};

Board::Board(){//inicijalizacija polja map --vlicina
    map.resize(5);
    for( unsigned i = 0 ; i < map.size() ; ++i)
      map.resize(4);
}

bool Board::input_initial_map( vector< vector<int> > initial_map){
  
}

int main(){

  return 0;
}
