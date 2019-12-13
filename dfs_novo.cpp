#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <list>
#include <queue>
#include <algorithm>
#include <queue>

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


  friend bool operator==(const Board &a,const Board &b );

  //pomaci
  //bool velika_kocka(pair<Board, Board>, list <Board> posjeceni, stack < pair<Board, Board> > &open);
  //bool vertikalni_pravokutnik(int index, pair<Board, Board> trenutni, list <Board> posjeceni, stack < pair<Board, Board> > &open);
  //bool horizontalni_pravokutnik(int index, pair<Board, Board> trenutni, list <Board> posjeceni, stack < pair<Board, Board> > &open);
  //bool mala_kocka(int index, pair<Board, Board> trenutni, list <Board> posjeceni, stack < pair<Board, Board> > &open);




};

bool operator==(const Board &a,const Board  &b ){
  for (size_t i = 0; i < a.map.size(); i++)
    for (size_t j = 0; j < a.map[i].size(); j++)
      if( a.map[i][j] != b.map[i][j])return false;
  return true;
}

bool posjecen(list <Board> posjeceni, Board board){
 if( find(posjeceni.begin(), posjeceni.end(), board)== posjeceni.end())return false;
 else return true;
}

bool postavi_index(Board trenutni, int &i, int &j, int find_index){//nalazi nam oblik u polju map
  for ( i = 0; i < trenutni.map.size(); i++)///postavljamo i,j na poziciju lijevog gornjeg vrha u obliku
    for( j = 0; j < trenutni.map[i].size() ; ++j)
      if(trenutni.map[i][j] == find_index) return true;
  return false;
}

bool mala_kocka(int index, pair<Board, Board> trenutni, list <Board> posjeceni, stack < pair<Board, Board> > &open){
  Board temp;
  temp = trenutni.first;
  int i,j;

  postavi_index(trenutni.first, i, j, index);

  if( i-1 >= 0){
    if( temp.map[i-1][j] == 0){///iznad je 0, micemo ga gore
      temp.map[i-1][j]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( i+1 < 5){
    if( temp.map[i+1][j] == 0){///ispod je 0, micemo ga dole
      temp.map[i+1][j]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( j-1 >= 0){
    if( temp.map[i-1][j] == 0){///lijevo je 0, micemo ga lijevo
      temp.map[i][j-1]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( j+1 < 4){
    if( temp.map[i][j+1] == 0){///iznad je 0, micemo ga gore
      temp.map[i][j+1]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
    return true;
}

bool vertikalni_pravokutnik(int index,pair<Board, Board> trenutni, list <Board> posjeceni, stack < pair<Board, Board> > &open){
  Board temp;
  temp = trenutni.first;
  int i,j;

  postavi_index(trenutni.first, i, j, index);

  if( i-1 >= 0 ){
    if( temp.map[i-1][j] == 0){///iznad je 0, micemo ga gore
      temp.map[i-1][j]=index; temp.map[i+1][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
   if( i+2 < 5){
    if( temp.map[i+2][j] == 0){///ispod je 0, micemo ga dole
      temp.map[i+2][j]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
   if( j+1 < 4){
    if( temp.map[i][j+1] == 0 && temp.map[i+1][j+1] == 0){///pored(desno) su 0-e, micemo ga desno
      temp.map[i][j+1] = temp.map[i+1][j+1] = index;
      temp.map[i][j] = temp.map[i+1][j] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
   if( j-1 >= 0){
    if( temp.map[i][j-1] == 0 && temp.map[i+1][j-1] == 0){///pored(lijevo) su 0-e, micemo ga lijevo
      temp.map[i][j-1] = temp.map[i+1][j-1] = index;
      temp.map[i][j] = temp.map[i+1][j] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
    return true;
}

bool horizontalni_pravokutnik(int index, pair<Board, Board> trenutni, list <Board> posjeceni, stack < pair<Board, Board> > &open){
  Board temp;
  temp = trenutni.first;
  int i,j;

  postavi_index(trenutni.first, i, j, index);//postavlja index na traženi oblik u gornji lijevi kut

  if( i-1 >= 0 ){
    if( temp.map[i-1][j] == 0 && temp.map[i-1][j+1] == 0 ){///iznad su dvije 0, micemo ga gore
      temp.map[i-1][j] = temp.map[i-1][j+1] = index;
      temp.map[i][j] = temp.map[i][j+1] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( i+1 < 5){
    if( temp.map[i+1][j] == 0 && temp.map[i+1][j+1] == 0 ){///ispod su dvije 0, micemo ga dole
      temp.map[i+1][j] = temp.map[i+1][j+1] = index;
      temp.map[i][j] = temp.map[i][j+1] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( j+2 < 4){
    if( temp.map[i][j+2] == 0 ){///pored(desno) je 0, micemo ga desno
      temp.map[i][j+2] = index;
      temp.map[i][j] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( j-1 >= 0){
    if( temp.map[i][j-1] == 0 ){///pored(lijevo) je 0, micemo ga lijevo
      temp.map[i][j-1] = index;
      temp.map[i][j+1] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
    return true;
}


bool velika_kocka(pair<Board, Board> trenutni, list <Board> posjeceni, stack < pair<Board, Board> > &open){
  Board temp;
  temp = trenutni.first;
  int i,j;

  postavi_index(trenutni.first, i,j,1);

///////////////////////slucajevi ovisno o poziciji nula
  if(i-1 >= 0){
    if( trenutni.first.map[i-1][j]==0 &&trenutni.first.map[i-1][j+1]==0 ){///ako je iznad kocke 0
      temp.map[i-1][j]=temp.map[i-1][j+1]=1;
      temp.map[i+1][j]=temp.map[i+1][j+1]=0;
      temp.slobodni_1.first = temp.slobodni_2.first = i+1;
      temp.slobodni_1.second = j; temp.slobodni_2.second = j+1;
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));return true;
    }}
  else if(i+2 < 5 ){
    if( trenutni.first.map[i+2][j]==0 &&trenutni.first.map[i+2][j+1]==0 ){///ako je ispod kocke 0
      temp.map[i+2][j]=temp.map[i+2][j+1]=1;
      temp.map[i][j]=temp.map[i][j+1]=0;
      temp.slobodni_1.first = temp.slobodni_2.first = i;
      temp.slobodni_1.second = j; temp.slobodni_2.second = j+1;
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));return true;
    }}
  else if(j+2 < 4 ){
    if( trenutni.first.map[i][j+2]==0 &&trenutni.first.map[i+1][j+2]==0 ){///ako je desno od kocke 0-- micemo ju u desno
      temp.map[i][j+2]=temp.map[i+1][j+2]=1;
      temp.map[i][j]=temp.map[i+1][j]=0;
      temp.slobodni_1.first = i;temp.slobodni_2.first = i+1;
      temp.slobodni_1.second = temp.slobodni_2.second = j;
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));return true;
    }}
  else if(j-1 >=0 ){
    if( trenutni.first.map[i][j-1]==0 &&trenutni.first.map[i+1][j-1]==0 ){///ako je lijevo od kocke 0-- micemo ju u lijevo
      temp.map[i][j-1]=temp.map[i+1][j-1]=1;
      temp.map[i][j+1]=temp.map[i+1][j+1]=0;
      temp.slobodni_1.first = i; temp.slobodni_2.first = i+1;
      temp.slobodni_1.second = temp.slobodni_2.second = j+1;
      if(!posjecen(posjeceni, temp))
        open.push(make_pair(temp,trenutni.first));return true;
    }}
  return false;
}


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
    for (size_t j = 0; j < map[i].size(); ++j)
      cout<<map[i][j]<<" ";
    cout<<endl;
  }
}

void Board::find_free(void){
  slobodni_1.first = slobodni_1.second = slobodni_2.first = slobodni_2.second = -1;
  for( size_t i = 0 ; i < map.size() ; ++i )
    for (size_t j = 0; j < map[i].size(); j++)
      if(map[i][j] == 0){
        if(slobodni_1.first == -1) {slobodni_1.first=i;slobodni_1.second=j;}
        else { slobodni_2.first=i;slobodni_2.second=j; }
      }
}

bool Board::cilj(void){//provjerav jesmo li u ciljnom stanju
  if( map[3][1] == 1 && map[3][2] == 1 && map[4][1] == 1 && map[4][2] == 1)
    return true;
  else return false;
}

void obradi(int i, int j,pair<Board, Board> cvor, list <Board> posjeceni, stack < pair<Board, Board> > &open){
  if( cvor.first.map[i][j] == 1 )
    velika_kocka(cvor, posjeceni, open);
  if( cvor.first.map[i][j] == 2 )
    horizontalni_pravokutnik(2,cvor, posjeceni, open);
  if( cvor.first.map[i][j] == 3 || cvor.first.map[i][j] == 4 || cvor.first.map[i][j] == 5 || cvor.first.map[i][j] == 6 )
    vertikalni_pravokutnik( cvor.first.map[i][j],cvor, posjeceni, open);
  if( cvor.first.map[i][j] == 7 || cvor.first.map[i][j] == 8 || cvor.first.map[i][j] == 9 || cvor.first.map[i][j] == 10 )
    mala_kocka(cvor.first.map[i][j],cvor, posjeceni, open);

}

void expand_and_insert(pair<int,int> slobodni,pair<Board, Board> cvor, list <Board> posjeceni, stack < pair<Board, Board> > &open){

  if( slobodni.first-1 >= 0 )
    obradi(slobodni.first-1, slobodni.second, cvor, posjeceni, open);
  if( slobodni.first+1 < 5 )
    obradi(slobodni.first+1, slobodni.second, cvor, posjeceni, open);
  if( slobodni.second-1 >= 0 )
    obradi(slobodni.first, slobodni.second-1, cvor, posjeceni, open);
  if( slobodni.second+1 < 4 )
    obradi(slobodni.first, slobodni.second+1, cvor, posjeceni, open);
}

bool depthFirstSearch( Board b0, queue < pair<Board, Board> > &put){
  stack < pair<Board, Board> > open; //trenutciljni, roditelj
  list <Board> posjeceni;

  int provjera=0;

  open.push(make_pair(b0, b0));
  while ( !open.empty() ){
    auto temp = open.top();
    open.pop();
    put.push(temp);
    if(temp.first.cilj()) return true;//////gotovo nasli smo put do rj.... dovrsit--treba implementirat još pamćenje roditelja
    posjeceni.push_back(temp.first);
    expand_and_insert(temp.first.slobodni_1,temp, posjeceni, open);
    expand_and_insert(temp.first.slobodni_2,temp, posjeceni, open);

    cout<<++provjera<<" ";
  }
  return false;
}
/*
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
}*/


void okreni_red(queue < pair<Board, Board> > put){
  queue < pair<Board, Board> > temp;

  while(!put.empty()){
    temp.push(put.front());
    put.pop();
  }
  put = temp;

}
void nadi_slj(Board trazeni,queue< pair< Board, Board > > &put){
  while( !(put.front().first == trazeni) ) put.pop();
}
void printrj(queue < pair<Board, Board> > put){
  pair<Board, Board> temp;

  do{
    temp = make_pair(put.front().first,put.front().second);
    put.pop();
    temp.first.print();
    if( !put.empty() )
      nadi_slj( temp.second, put );
  }while( !put.empty() );
}


int main(){

  vector< vector<int> > input { {3,1,1,4},
                              {3,1,1,4},
                              {5,2,2,6},
                              {5,8,9,6},
                              {7,0,0,10} };

  Board board;
  queue< pair< Board, Board > > put;

  board.input_initial_map(input);
  board.print();
  cout<<"go";
  cout<<depthFirstSearch(board, put)<<endl;////////////neće poslat put
  okreni_red(put);
  printrj(put);


//unos mape  -- kasnije
  ///cin<<




  return 0;
}
