#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define DUBINA 7;



class Board{
public:
  vector< vector<int> > map;
  pair< int, int > slobodni_1, slobodni_2; //sloboddni indexi

  Board();
  bool input_initial_map( vector< vector<int> > initial_map);//input initcijalne mape
  void print(void);
  void find_free(void);//traži slobodne indexe
  bool cilj(void); // ciljno stanje

  //pomaci
  bool velika_kocka()




};

Board::Board(){//inicijalizacija polja map --vlicina
    map.resize(5);
    for( unsigned i = 0 ; i < map.size() ; ++i)
      map.resize(4);
    slobodni_1.first=slobodni_1.second=slobodni_2.first=slobodni_2.second=-1;
}

bool Board::input_initial_map( vector< vector<int> > initial_map){
  map = initial_map;
  find_free();
}

void Board::print ( void){
  for( size_t i = 0 ; i < map.size() ; ++i ){
    for (size_t j = 0; j < map[i].size(); j++)
      cout<<map[i][j]<<" ";
    cout<<endl;
  }
}

void Board::find_free(void){
  for( size_t i = 0 ; i < map.size() ; ++i )
    for (size_t j = 0; j < map[i].size(); j++)
      if(map[i][j] == 0){
        if(slobodni_1.first == -1) {slobodni_1.first=i;slobodni_1.second=j;}
        else { slobodni_2.first=i;slobodni_2.second=j; }
      }
}

bool Board::cilj(void){//provjerav jesmo li u ciljnom stanju
  if( map[3][1] == map[3][2] == map[4][1] == map[4][2] == 1)
    return true;
  else return false;
}

bool game(Board B){///nije gotovo

//za 1. slobodno polje
  if( B.slobodni_1.second-1 > 0 ){ if( B.pomak(B.slobodni_1.first,B.slobodni_1.second-1) ){
    rjesenje.push_back(B); return true;
  }}
  if( B.slobodni_1.second+1 < 4 ){ if( B.pomak(B.slobodni_1.first,B.slobodni_1.second+1) ){
    rjesenje.push_back(B); return true;
  }}
  if( B.slobodni_1.first-1 > 0 ){ if( B.pomak(B.slobodni_1.first-1,B.slobodni_1.second) ){
    rjesenje.push_back(B); return true;
  }}
  if( B.slobodni_1.first+1 < 5 ){ if( B.pomak(B.slobodni_1.first+1,B.slobodni_1.second) ){
    rjesenje.push_back(B); return true;
  }}
////za 2. slobodno polje
  if( B.slobodni_2.second-1 > 0 ){ if( B.pomak(B.slobodni_2.first,B.slobodni_2.second-1) ){
    rjesenje.push_back(B); return true;
  }}
  if( B.slobodni_2.second+1 < 4 ){ if( B.pomak(B.slobodni_2.first,B.slobodni_2.second+1) ){
    rjesenje.push_back(B); return true;
  }}
  if( B.slobodni_2.first-1 > 0 ){ if( B.pomak(B.slobodni_2.first-1,B.slobodni_2.second) ){
    rjesenje.push_back(B); return true;
  }}
  if( B.slobodni_2.first+1 < 5 ){ if( B.pomak(B.slobodni_2.first+1,B.slobodni_2.second) ){
    rjesenje.push_back(B); return true;
  }}
  return false;
}


vector< Board > rjesenje;

int main(){

  vector< vector<int> > input { {3,1,1,4},
                              {3,1,1,4},
                              {5,2,2,6},
                              {5,8,9,6},
                              {7,0,0,10} };

  Board board;
  board.input_initial_map(input);
  board.print();


//unos mape  -- kasnije
  ///cin<<




  return 0;
}
