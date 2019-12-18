#include "board.h"

///////////////////////////////////// pomoćne fje za expand čvora

void obradi(int i, int j,pair<Board, Board> cvor, list <Board> posjeceni, queue < pair<Board, Board> > &open){
  if( cvor.first.map[i][j] == 1 )
    velika_kocka(cvor, posjeceni, open);
  else if( cvor.first.map[i][j] == 2 )
    horizontalni_pravokutnik(2,cvor, posjeceni, open);
  else if( cvor.first.map[i][j] == 3 || cvor.first.map[i][j] == 4 || cvor.first.map[i][j] == 5 || cvor.first.map[i][j] == 6 )
    vertikalni_pravokutnik( cvor.first.map[i][j],cvor, posjeceni, open);
  else if( cvor.first.map[i][j] == 7 || cvor.first.map[i][j] == 8 || cvor.first.map[i][j] == 9 || cvor.first.map[i][j] == 10 )
    mala_kocka(cvor.first.map[i][j],cvor, posjeceni, open);

}

void expand_and_insert(pair<int,int> slobodni,pair<Board, Board> cvor, list <Board> posjeceni, queue < pair<Board, Board> > &open){
//cout<<"e&i:"<<slobodni.first<<endl;
  if( slobodni.first-1 >= 0 ){//cout<<"1";    //iznad
    obradi(slobodni.first-1, slobodni.second, cvor, posjeceni, open);}
  //  cout<<"____________________________________-";
  if( slobodni.first+1 < 5 ){//cout<<"2";     //ispod
    obradi(slobodni.first+1, slobodni.second, cvor, posjeceni, open);}
  if( slobodni.second-1 >= 0 ){//cout<<"3";   //lijevo
    obradi(slobodni.first, slobodni.second-1, cvor, posjeceni, open);}
  if( slobodni.second+1 < 4 ){//cout<<"4";    //desno
    obradi(slobodni.first, slobodni.second+1, cvor, posjeceni, open);}
    //cout<<endl;
}

/////////////////////////////////////////////       DFS

bool breadthFirstSearch( Board b0, queue < pair<Board, Board> > &put){
  queue < pair<Board, Board> > open, open2; //trenutciljni, roditelj
  list <Board> posjeceni;

  int provjera=0;

  open.push(make_pair(b0, b0));
  while ( !open.empty() ){
    pair<Board, Board> temp = open.front();
    open.pop();
    if(posjecen(posjeceni, temp.first))
      continue;
    put.push(temp);
    if(temp.first.cilj()) {
      return true;//////gotovo nasli smo put do rj.... dovrsit--treba implementirat još pamćenje roditelja
    }
    posjeceni.push_back(temp.first);
    expand_and_insert(temp.first.slobodni_1,temp, posjeceni, open);
    expand_and_insert(temp.first.slobodni_2,temp, posjeceni, open);

/*      ///ispis reda open -- u iteraciji
    cout<<"temp trenutni:"<<endl;temp.first.print();
    open2=open;cout<<"print open:"<<endl;
      while(!open2.empty()){
        open2.front().first.print();cout<<endl<<endl;
        open2.pop();
      }*/
    ///ispis broja iteracije i veličine..
    //cout<<"provjera, open.size(), posjeceni.size(): "<<++provjera<<", "<<open.size()<<", "<<posjeceni.size()<<endl;
    //if(provjera==1)break;
  }/*
  cout<<"van whilea, ostatak u listi open:"<<endl;
  while(!open.empty()){
    open.front().first.print();cout<<endl<<endl;
    open.pop();
  }*/
  return false;
}
