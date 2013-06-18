#include <iostream>
#include <list>

using namespace std;

int main() {
  list<int> foo;
  foo.push_back(1);
  foo.push_back(20);
  foo.push_back(300);
  
  list<int> poo (foo);
  //list<int>::iterator it = poo.begin();
  //++it;
  int i = poo.front();
  cout << "front item: " << poo.front() << "\ti value: " << i << endl;
  poo.pop_front();
  cout << "i-value: " << i << endl;
  cout << "front(): " << poo.front() << endl;
  //  cout << poo.back() << " size-" << poo.size() << endl;
}
