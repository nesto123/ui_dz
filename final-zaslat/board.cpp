#include "board.h"

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
//  cout<<"slobodni1: "<<slobodni_1.first<<", "<<slobodni_1.second<<" 2: "<<slobodni_2.first<<", "<<slobodni_2.second<<endl;
}

bool Board::cilj(void){//provjerav jesmo li u ciljnom stanju
  if( map[3][1] == 1 && map[3][2] == 1 && map[4][1] == 1 && map[4][2] == 1)
    return true;
  else return false;
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

bool operator==(const Board &a,const Board  &b ){
  for (size_t i = 0; i < a.map.size(); i++)
    for (size_t j = 0; j < a.map[i].size(); j++)
      if( a.map[i][j] != b.map[i][j])return false;
  return true;
}

Board::Board(const Board &obj){//CCtor
  map = obj.map;
  find_free();
}

//////////////////////////////////// pomoćne

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

bool vec_u_redu(Board temp, queue < pair<Board, Board> > open){
  while( !open.empty() ){
    if( open.front().first == temp )
      return true;
    open.pop();
  }
  return false;
}

///////////////////////////////////////// move -  pomaci ovisno o tome koji je oblik na mjestu trenutni

bool mala_kocka(int index, pair<Board, Board> trenutni, list <Board> posjeceni, queue < pair<Board, Board> > &open){
  Board temp;
  temp = trenutni.first;
  int i,j;

  postavi_index(trenutni.first, i, j, index);

  if( i-1 >= 0){
    if( temp.map[i-1][j] == 0){///iznad je 0, micemo ga gore
      temp.map[i-1][j]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( i+1 < 5){
    if( temp.map[i+1][j] == 0){///ispod je 0, micemo ga dole
      temp.map[i+1][j]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( j-1 >= 0){
    if( temp.map[i][j-1] == 0){///lijevo je 0, micemo ga lijevo
      temp.map[i][j-1]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( j+1 < 4){
    if( temp.map[i][j+1] == 0){///iznad je 0, micemo ga gore
      temp.map[i][j+1]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
    return true;
}

bool vertikalni_pravokutnik(int index,pair<Board, Board> trenutni, list <Board> posjeceni, queue < pair<Board, Board> > &open){
  Board temp;
  temp = trenutni.first;
  int i,j;

  postavi_index(trenutni.first, i, j, index);

  if( i-1 >= 0 ){
    if( temp.map[i-1][j] == 0){///iznad je 0, micemo ga gore
      temp.map[i-1][j]=index; temp.map[i+1][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
   if( i+2 < 5){
    if( temp.map[i+2][j] == 0){///ispod je 0, micemo ga dole
      temp.map[i+2][j]=index; temp.map[i][j]=0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
   if( j+1 < 4){
    if( temp.map[i][j+1] == 0 && temp.map[i+1][j+1] == 0){///pored(desno) su 0-e, micemo ga desno
      temp.map[i][j+1] = temp.map[i+1][j+1] = index;
      temp.map[i][j] = temp.map[i+1][j] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
   if( j-1 >= 0){
    if( temp.map[i][j-1] == 0 && temp.map[i+1][j-1] == 0){///pored(lijevo) su 0-e, micemo ga lijevo
      temp.map[i][j-1] = temp.map[i+1][j-1] = index;
      temp.map[i][j] = temp.map[i+1][j] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
    return true;
}

bool horizontalni_pravokutnik(int index, pair<Board, Board> trenutni, list <Board> posjeceni, queue < pair<Board, Board> > &open){
  Board temp;
  temp = trenutni.first;
  int i,j;

  postavi_index(trenutni.first, i, j, index);//postavlja index na traženi oblik u gornji lijevi kut

  if( i-1 >= 0 ){
    if( temp.map[i-1][j] == 0 && temp.map[i-1][j+1] == 0 ){///iznad su dvije 0, micemo ga gore
      temp.map[i-1][j] = temp.map[i-1][j+1] = index;
      temp.map[i][j] = temp.map[i][j+1] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( i+1 < 5){
    if( temp.map[i+1][j] == 0 && temp.map[i+1][j+1] == 0 ){///ispod su dvije 0, micemo ga dole
      temp.map[i+1][j] = temp.map[i+1][j+1] = index;
      temp.map[i][j] = temp.map[i][j+1] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( j+2 < 4){
    if( temp.map[i][j+2] == 0 ){///pored(desno) je 0, micemo ga desno
      temp.map[i][j+2] = index;
      temp.map[i][j] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
  if( j-1 >= 0){
    if( temp.map[i][j-1] == 0 ){///pored(lijevo) je 0, micemo ga lijevo
      temp.map[i][j-1] = index;
      temp.map[i][j+1] = 0;
      temp.find_free();
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      temp = trenutni.first;
    }}
    return true;
}

bool velika_kocka(pair<Board, Board> trenutni, list <Board> posjeceni, queue < pair<Board, Board> > &open){
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
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      return true;
    }}
   if(i+2 < 5 ){
    if( trenutni.first.map[i+2][j]==0 &&trenutni.first.map[i+2][j+1]==0 ){///ako je ispod kocke 0
      temp.map[i+2][j]=temp.map[i+2][j+1]=1;
      temp.map[i][j]=temp.map[i][j+1]=0;
      temp.slobodni_1.first = temp.slobodni_2.first = i;
      temp.slobodni_1.second = j; temp.slobodni_2.second = j+1;
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      return true;
    }}
   if(j+2 < 4 ){
    if( trenutni.first.map[i][j+2]==0 &&trenutni.first.map[i+1][j+2]==0 ){///ako je desno od kocke 0-- micemo ju u desno
      temp.map[i][j+2]=temp.map[i+1][j+2]=1;
      temp.map[i][j]=temp.map[i+1][j]=0;
      temp.slobodni_1.first = i;temp.slobodni_2.first = i+1;
      temp.slobodni_1.second = temp.slobodni_2.second = j;
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      return true;
    }}
   if(j-1 >=0 ){
    if( trenutni.first.map[i][j-1]==0 &&trenutni.first.map[i+1][j-1]==0 ){///ako je lijevo od kocke 0-- micemo ju u lijevo
      temp.map[i][j-1]=temp.map[i+1][j-1]=1;
      temp.map[i][j+1]=temp.map[i+1][j+1]=0;
      temp.slobodni_1.first = i; temp.slobodni_2.first = i+1;
      temp.slobodni_1.second = temp.slobodni_2.second = j+1;
      if(!posjecen(posjeceni, temp) && !vec_u_redu(temp,open) )
        open.push(make_pair(temp,trenutni.first));
      return true;
    }}
  return false;
}


