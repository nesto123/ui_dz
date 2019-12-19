#include "board.h"


///////////////pomoćne f-je za isis puta unatrag
void okreni_red(queue < pair<Board, Board> > &put){///okreće red za ispis
  stack < pair<Board, Board> > stack;

  while(!put.empty()){
    stack.push(put.front());
    put.pop();
  }
  while(!stack.empty()){
    put.push(stack.top());
    stack.pop();
  }
}

void nadi_slj(Board trazeni,queue< pair< Board, Board > > &put){// traži trazeni Board u queue tj njegovog roditelja
  while( !(put.front().first == trazeni) ) put.pop();
}

void printrj(queue < pair<Board, Board> > put){///ispis rješenja, tj puta unatrag
  pair<Board, Board> temp;
  int i=0;

  do{
    cout<<"________________________"<< ++i<<". korak:"<<endl;
    temp = make_pair(put.front().first,put.front().second);
    put.pop();
    temp.first.print();
    if( !put.empty() )
      nadi_slj( temp.second, put );
  }while( !put.empty() );
}

void clear_put(  queue< pair< Board, Board > > &put){
  while(!put.empty()) put.pop();
}

int main(){

vector< vector<int> > input { {3,2,2,4},      
                              {3,6,8,4},
                              {5,6,1,1},
                              {5,9,1,1},
                              {7,0,0,10} };
vector< vector<int> > input1 { {3,8,9,4},
                              {3,2,2,4},
                              {5,1,1,6},
                              {5,1,1,6},
                              {0,7,10,0} };
vector< vector<int> > input2 { {3,2,2,4},
                              {3,1,1,4},
                              {5,1,1,6},
                              {5,9,8,6},
                              {7,0,0,10} };


  Board board;
  queue< pair< Board, Board > > put;
  bool t;

  board.input_initial_map(input);
  cout<<"početna ploća:"<<endl;
  board.print();
  t=breadthFirstSearch(board, put);
  cout<<"breadthFirstSearch: "<<t<<endl<<"Put unazad:"<<endl;
  if( t ) {
    okreni_red(put);
    printrj(put);clear_put(put);
  }

cout<<"------------------------------------------";
  board.input_initial_map(input1);
  cout<<"početna ploća:"<<endl;
  board.print();
  t=breadthFirstSearch(board, put);
  cout<<"breadthFirstSearch: "<<t<<endl<<"Put unazad:"<<endl;
  if( t ) {
    okreni_red(put);
    printrj(put);clear_put(put);
  }

cout<<"------------------------------------------";
  board.input_initial_map(input2);
  cout<<"početna ploća:"<<endl;
  board.print();
  t=breadthFirstSearch(board, put);
  cout<<"breadthFirstSearch: "<<t<<endl<<"Put unazad:"<<endl;
  if( t ) {
    okreni_red(put);
    printrj(put);clear_put(put);
  }



  return 0;
}
