#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <list>
#include <queue>
#include <algorithm>

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

  bool pomak(size_t i, size_t j);

friend bool operator==(const Board &a,const Board &b );

  //pomaci
  bool velika_kocka(pair<Board, Board>, list <Board> posjeceni, stack < pair<Board, Board> > &open);





};
friend bool operator==(const Board &a,const Board  &b ){

}
 bool posjecen(list <Board> posjeceni, Board board){
   //if( find(posjeceni.begin(), posjeceni.end(), board)== posjeceni.end())return false;
   //else return true;
 }

bool velika_kocka_pomak(pair<Board, Board> trenutni, list <Board> posjeceni, stack < pair<Board, Board> > &open){
  Board temp;
  temp = trenutni.first;
  size_t i,j;

  for ( i = 0; i < trenutni.first.map.size(); i++){///postavljamo i,j na poziciju lijevog gornjeg vrha u kocki
    for( j = 0; j < trenutni.first.map[i].size() ; ++j){
      if(trenutni.first.map[i][j] == 1) break;
    }
    if(trenutni.first.map[i][j] == 1) break;
  }
///////////////////////slucajevi ovisno o poziciji nula
  if(i-1 >= 0 && trenutni.first.map[i-1][j]==0 &&trenutni.first.map[i-1][j+1]==0 ){///ako je iznad kocke 0
    temp.map[i-1][j]=temp.map[i-1][j+1]=1;
    temp.map[i+1][j]=temp.map[i+1][j+1]=0;
    if(!posjecen(posjeceni, temp))
      open.push(make_pair(temp,trenutni.first));return true;
  }
  else if(i+2 < 5 && trenutni.first.map[i+2][j]==0 &&trenutni.first.map[i+2][j+1]==0 ){///ako je ispod kocke 0
    temp.map[i+2][j]=temp.map[i+2][j+1]=1;
    temp.map[i][j]=temp.map[i][j+1]=0;
    if(!posjecen(posjeceni, temp))
      open.push(make_pair(temp,trenutni.first));return true;
  }
  else if(j+2 < 4 && trenutni.first.map[i][j+2]==0 &&trenutni.first.map[i+1][j+2]==0 ){///ako je desno od kocke 0-- micemo ju u desno
    temp.map[i][j+2]=temp.map[i+1][j+2]=1;
    temp.map[i][j]=temp.map[i+1][j]=0;
    if(!posjecen(posjeceni, temp))
      open.push(make_pair(temp,trenutni.first));return true;
  }
  else if(j-1 >=0 && trenutni.first.map[i][j-1]==0 &&trenutni.first.map[i+1][j-1]==0 ){///ako je lijevo od kocke 0-- micemo ju u lijevo
    temp.map[i][j-1]=temp.map[i+1][j-1]=1;
    temp.map[i][j+1]=temp.map[i+1][j+1]=0;
    if(!posjecen(posjeceni, temp))
      open.push(make_pair(temp,trenutni.first));return true;
  }
  return false;
}




  bool Board::pomak(size_t i, size_t j){}

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

void expand_and_insert(pair<Board, Board> cvor, list <Board> posjeceni, stack < pair<Board, Board> > &open){

}

bool depthFirstSearch( Board b0){
  stack < pair<Board, Board> > open; //trenutni, roditelj
  list <Board> posjeceni;

  open.push(make_pair(b0, b0));
  while ( !open.empty() ){
    auto temp = open.top();
    if(temp.first.cilj()) break;//////gotovo nasli smo put do rj.... dovrsit
    posjeceni.push_back(temp.first);
    expand_and_insert(temp, posjeceni, open);

  }

}

bool game(Board B, vector< Board > &rjesenje){///nije gotovo

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
