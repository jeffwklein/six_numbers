
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;


//function name declarations
void permute(vector<int> & , vector<int> & );
void add(vector<int> & );
void subtract(vector<int> & );
void multiply(vector<int> & );
void divide(vector <int> & );
void printSteps();
void printList(vector<int> &);

//global data declarations
int target, countIndex;
int counter[6];
const int LIMIT[] = {0,1,1,2,6,24};
clock_t startTime;
vector<string> steps;

int main() {
  cout << "Enter target number: ";
  cin >> target;
  vector<int> inputNumbers;
  int n;
  for (int i = 0; i < 6; i++) {
    cout << "Enter number " << (i+1) << ": ";
    cin >> n;
    inputNumbers.push_back(n);
  }
  startTime = clock();
  vector<int> vec;
  permute(vec, inputNumbers);
}

void permute(vector<int> & startList, vector<int> & endList) {
  if (endList.size() == 1) {
    startList.push_back(endList.front());
    countIndex = startList.size()-1;
    if (counter[countIndex] == LIMIT[countIndex]) {
      counter[countIndex] = 0;
    }
    counter[countIndex]++;
    if (counter[countIndex] == 1) {
	for (int i = 0; i < 4; i++) {
	  vector<int> temp (startList);
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
	      vector<int> newVec;
	      permute(newVec, temp);
	    }
	    steps.pop_back();
	  }
	} //end for
    }
  }
  else { //permuting algorithm
    for (int i = 0; i < endList.size(); i++) {
      vector<int> newEnd (endList);
      vector<int> newStart (startList);
      newEnd.erase(newEnd.begin() + i);
      newStart.push_back(endList[i]);
      permute(newStart, newEnd);
    }
  }
}//end permute method


void add(vector<int> & v) {
  int s = v.size()-1;
  int test = v[s-1] + v[s];
  char buf[25];
  sprintf(buf, "%d + %d = %d", v[s-1], v[s], test);
  steps.push_back(buf);
  if (test == target) {
    printSteps();
  }
  v.pop_back();
  v.back() = test;
}

void subtract(vector<int> & v) {
  int s = v.size()-1;
  int test = v[s-1] - v[s];
  if (test <= 0) {
    v.clear();
  }
  else {
    char buf[25];
    sprintf(buf, "%d - %d = %d", v[s-1], v[s], test);
    steps.push_back(buf);
    if (test == target) {
      printSteps();
    }
    v.pop_back();
    v.back() = test;
  }
}
	
void multiply(vector<int> & v) {
  int s = v.size()-1;
  int test = v[s-1] * v[s];
  char buf[25];
  sprintf(buf, "%d * %d = %d", v[s-1], v[s], test);
  steps.push_back(buf);
  if (test == target) {
    printSteps();
  }
  v.pop_back();
  v.back() = test;
}

void divide(vector<int> & v) {
  int s = v.size()-1;
  if (v[s-1] % v[s] > 0 || v[s-1] < v[s]) {
    v.clear();
  }
  else {
    int test = v[s-1] / v[s];
    char buf[25];
    sprintf(buf, "%d / %d = %d", v[s-1], v[s], test);
    steps.push_back(buf);
    if (test == target) {
      printSteps();
    }
    v.pop_back();
    v.back() = test;
  }
}


void printSteps() {
  cout << "\n";
  for (int i = 0; i < steps.size(); i++) {
    cout << steps[i] << endl;
  }
  cout << "\nSuccess!\n";
  startTime = clock()-startTime;
  printf("Execution time:\t%f\n\n",((float)startTime)/CLOCKS_PER_SEC);
  exit(0);
}
	
void printList(vector<int> &v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
}
	
	


