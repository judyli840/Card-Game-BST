// Judy Li
#include "cards.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void playGame(Cards &player1, Cards &player2){
  Node* p1 = player1.getMin();
  Node* p2 = player2.getMax();
  while(p1&&p2){
    while(p1){
      if(player2.contains(p1->info)){
        int s = p1->info;
        cout<<"Alice picked matching card "<<convertInt(s)<<endl;
        p1 = player1.getSuccessorNode(p1->info);
        player1.remove(s);
        player2.remove(s);
        break;
      }
      p1 = player1.getSuccessorNode(p1->info);
    }
    while(p2){
      if(player1.contains(p2->info)){
        int s = p2->info;
        cout<<"Bob picked matching card "<<convertInt(s)<<endl;
        if(p2->left&&p2->right){
          p2 = player2.getPredecessorNode(p2->info);
          p2 = player2.getPredecessorNode(p2->info);
          player1.remove(s);
          player2.remove(s);
          p2 = player2.getSuccessorNode(p2->info);
          break;
        }else{
          p2 = player2.getPredecessorNode(p2->info);
          player1.remove(s);
          player2.remove(s);
          break;
        }
      }
      p2 = player2.getPredecessorNode(p2->info);
    }
  }
  cout<<endl;
}

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  Cards alice, bob;
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    alice.insert(line);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    bob.insert(line);
  }
  cardFile2.close();

  playGame(alice, bob);
  cout<<"Alice's cards:"<<endl;
  alice.printInOrder();
  cout<<endl;
  cout<<"Bob's cards:"<<endl;
  bob.printInOrder();

  return 0;
}

