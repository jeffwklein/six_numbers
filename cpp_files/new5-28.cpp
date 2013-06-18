#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

//function name declarations
void permute(deque<int> & );
void operations(deque<int> & );
void add(deque<int> & );
void subtract(deque<int> & );
void multiply(deque<int> & );
void divide(deque<int> & );
void printSteps();
void printList(deque<int> & );

//global data declarations
int target;
clock_t startTime;
vector<string> steps;

int main() {
  cout << "\n\tEnter target number: ";
  cin >> target;
  deque<int> inputNumbers;
  int n;
  for (int i = 0; i < 6; i++) {
    cout << "\tEnter number " << (i+1) << ": ";
    cin >> n;
    inputNumbers.push_back(n);
  }
  startTime = clock();
  permute(inputNumbers);
}

void permute(deque<int> & numbers) {
  for (int i = 0; i < numbers.size(); i++) {
    for (int j = 0; j < numbers.size(); j++) {
      if (i != j && numbers[i] >= numbers[j]) {
	deque<int> deq (numbers);
	deq.front() = numbers[i];
	deq[1] = numbers[j];
	deq[i] = numbers[0];
	deq[j] = numbers[1];
	operations(deq);
      }
    }
  }  
}//end permute method

void operations(deque<int> & numbers) {
  for (int i = 0; i < 4; i++) {
    deque<int> temp (numbers);
    switch (i) {
    case 0 : add(temp);
      break;
    case 1 : subtract(temp);
      break;
    case 2 : multiply(temp);
      break;
    case 3 : divide(temp);
      break;
    }//end switch
    if (temp.size() > 0) {
      if (temp.size() > 1) {
	permute(temp);
      }
      steps.pop_back();
    }
  } //end for
}


void add(deque<int> & d) {
  int test = d[0] + d[1];
  char buf[25];
  sprintf(buf, "%d + %d = %d", d[0], d[1], test);
  steps.push_back(buf);
  if (test == target) {
    printSteps();
  }
  d.pop_front();
  d.front() = test;
}

void subtract(deque<int> & d) {
  int test = d[0] - d[1];
  if (test <= 0) {
    d.clear();
  }
  else {
    char buf[25];
    sprintf(buf, "%d - %d = %d", d[0], d[1], test);
    steps.push_back(buf);
    if (test == target) {
      printSteps();
    }
    d.pop_front();
    d.front() = test;
  }
}
	
void multiply(deque<int> & d) {
  int test = d[0] * d[1];
  char buf[25];
  sprintf(buf, "%d * %d = %d", d[0], d[1], test);
  steps.push_back(buf);
  if (test == target) {
    printSteps();
  }
  d.pop_front();
  d.front() = test;
}

void divide(deque<int> & d) {
  if (d[0] % d[1] > 0) {
    d.clear();
  }
  else {
    int test = d[0] / d[1];
    char buf[25];
    sprintf(buf, "%d / %d = %d", d[0], d[1], test);
    steps.push_back(buf);
    if (test == target) {
      printSteps();
    }
    d.pop_front();
    d.front() = test;
  }
}

void printSteps() {
  cout << "\n";
  for (int i = 0; i < steps.size(); i++) {
    cout << "\t" << steps[i] << endl;
  }
  cout << "\n\tSuccess!\n";
  startTime = clock()-startTime;
  printf("\tExecution time:\t%fs\n\n",((float)startTime)/CLOCKS_PER_SEC);
  exit(0);
}

void printList(deque<int> &d) {
  for (int i = 0; i < d.size(); i++) {
    cout << d[i] << " ";
  }
  cout << endl;
}



