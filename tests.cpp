// Judy Li

#include "cards.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

void test_insert(){
  Cards test;
  assert(test.insert("h 9"));
  assert(test.insert("c k"));
  assert(test.insert("s 3"));
  assert(test.insert("c a"));
}

void test_contains(){
  Cards test;
  test.insert("h 9");
  test.insert("c k");
  test.insert("s 3");
  test.insert("c a");
  assert(test.contains(48));
  assert(test.contains(13));
  assert(test.contains(29));
  assert(test.contains(1));
}

void test_remove(){
  Cards test;
  test.insert("h 9");
  test.insert("c k");
  test.insert("s 3");
  test.insert("c a");
  assert(test.contains(48));
  assert(test.contains(13));
  assert(test.contains(29));
  assert(test.contains(1));
  test.remove(13);
  test.remove(1);
  assert(!test.contains(13));
  assert(!test.contains(1));
}

void test_predecessor(){
  Cards test;
  test.insert("h 9");
  test.insert("c k");
  test.insert("s 3");
  test.insert("c a");
  assert(test.getPredecessor(48)==29);
  assert(test.getPredecessor(29)==13);
  assert(test.getPredecessor(13)==1);
}

void test_successor(){
  Cards test;
  test.insert("h 9");
  test.insert("c k");
  test.insert("s 3");
  test.insert("c a");
  assert(test.getSuccessor(29)==48);
  assert(test.getSuccessor(13)==29);
  assert(test.getSuccessor(1)==13);
}

int main(int argc, char** argv){
  if (argc != 2) {
          cout << "error: need at least one int arg on command line" << endl;
          cout << "usage: " << argv[0] << " testid " << endl;
          return 1;
      }
      if(atoi(argv[1])==1){
          test_insert();
          cout<<"PASSED test_insert"<<endl;
      }
      if(atoi(argv[1])==2){
          test_contains();
          cout<<"PASSED test_contains"<<endl;
      }
      if(atoi(argv[1])==3){
          test_remove();
          cout<<"PASSED test_remove"<<endl;
      }
      if(atoi(argv[1])==4){
          test_predecessor();
          test_successor();
          cout<<"PASSED test_predecessor and test_successor"<<endl;
      }

      return 0;
}

