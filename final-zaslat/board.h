#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <list>
#include <queue>
#include <algorithm>
#include <queue>
using namespace std;

class Board{
public:
  vector< vector<int> > map;
  pair< int, int > slobodni_1, slobodni_2; //sloboddni indexi

  Board();
  bool input_initial_map( vector< vector<int> > initial_map);//input initcijalne mape
  void print(void);
  void find_free(void);//traži slobodne indexe
  bool cilj(void); // ciljno stanje

  Board(const Board &obj);
  friend bool operator==(const Board &a,const Board &b );
};

bool velika_kocka(pair<Board, Board> trenutni, list <Board> posjeceni, queue < pair<Board, Board> > &open);
bool horizontalni_pravokutnik(int index, pair<Board, Board> trenutni, list <Board> posjeceni, queue < pair<Board, Board> > &open);
bool vertikalni_pravokutnik(int index,pair<Board, Board> trenutni, list <Board> posjeceni, queue < pair<Board, Board> > &open);
bool mala_kocka(int index, pair<Board, Board> trenutni, list <Board> posjeceni, queue < pair<Board, Board> > &open);
bool posjecen(list <Board> posjeceni, Board board);
bool breadthFirstSearch( Board b0, queue < pair<Board, Board> > &put);
