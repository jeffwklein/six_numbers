#include <unistd.h>
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <csignal>

using namespace std;


//function name declarations
void permute(list<int> & startList, list<int> & endList);
static void sig_usr(int); //signal handler
void add(list<int> & );
void subtract(list<int> & );
void multiply(list<int> & );
void divide(list<int> & );
void printSteps();
void printList(list<int> & );

//global data declarations
int target, countIndex;
int counter[6];
const int LIMIT[] = {0,1,1,2,6,24};
clock_t t;
string newStep;
list<string> steps;
list<int>::iterator it;

int main() {
  cout << "Enter target number: ";
  cin >> target;
  list<int> inputNumbers;
  int n;
  for (int i = 0; i < 6; i++) {
    cout << "Enter number " << (i+1) << ": ";
    cin >> n;
    inputNumbers.push_back(n);
  }
  t = clock();
  list<int> empty;
  permute(empty, inputNumbers);
}

void permute(list<int> & startList, list<int> & endList) {
  if (endList.size() == 1) {
    startList.push_back(endList.front());
    countIndex = startList.size()-1;
    if (counter[countIndex] == LIMIT[countIndex]) {
      counter[countIndex] = 0;
    }
    counter[countIndex]++;
    if (counter[countIndex] == 1) {
	for (int i = 0; i < 4; i++) {
	  list<int> temp (startList);
	  switch (i) {
	  case 0 : add(temp);
	    break;
	  case 1 : subtract(temp);
	    break;
	  case 2 : multiply(temp);
	    break;
	  case 3 : divide(temp);
	    break;
	  } //end switch
	  if (temp.size() > 0) {
	    if (temp.size() > 1) {
	      list<int> newList;
	      permute(newList, temp);
	    }
	    steps.pop_back();
	  }
	} //end for
    }
  }
  else { //permuting algorithm
    for (int i = 0; i < endList.size(); i++) {
      list<int> newEnd (endList);
      list<int> newStart (startList);
      it = newEnd.begin();
      advance(it, i);
      newEnd.erase(it);
      it = endList.begin();
      advance(it, i);
      newStart.push_back(*it);
      permute(newStart, newEnd);
    }
  }
} //end permute method

/*
// signal handler for terminated background processes
static void sig_usr(int signo) {
  signal(SIGCHLD, sig_usr);
  if (signo == SIGCHLD) {
    int childpid;
    if ((childpid = waitpid(-1, NULL, WNOHANG) ) != -1) {
      childCount--;
      printf("\t\tChild terminated, %d remain", childCount);
    }
  }
}
*/

void add(list<int> & v) {
  int hold = v.front();
  v.pop_front();
  int hold2 = v.front();
  char buf[25];
  sprintf(buf, "%d + %d = %d", hold, hold2, hold+hold2);
  steps.push_back(buf);
  v.front() += hold;
  if (v.front() == target) {    
    printSteps();
  }
}

void subtract(list<int> & v) {
  int hold = v.front();
  v.pop_front();
  if (hold <= v.front()) {
    v.clear();
  }
  else {
    char buf[25];
    sprintf(buf, "%d - %d = %d", hold, v.front(), hold-v.front());
    steps.push_back(buf);
    v.front() = hold - v.front();
    if (v.front() == target) {
      printSteps();
    }
  }
}
	
void multiply(list<int> & v) {
  int hold = v.front();
  v.pop_front();
  char buf[25];
  sprintf(buf, "%d * %d = %d", hold, v.front(), hold*v.front());
  steps.push_back(buf);
  v.front() *= hold;
  if (v.front() == target) {
    printSteps();
  }
}

void divide(list<int> & v) {
  int hold = v.front();
  v.pop_front();
  if (hold % v.front() > 0 || hold < v.front()) {
    v.clear();
  }
  else {
    char buf[25];
    sprintf(buf, "%d / %d = %d", hold, v.front(), hold/v.front());
    steps.push_back(buf);
    v.front() = hold / v.front();
    if (v.front() == target) {
      printSteps();
    }
  }
}

void printSteps() {
  list<string>::iterator iter;
  for (iter = steps.begin(); iter != steps.end(); ++iter) {
    cout << *iter << endl;
  }
  cout << "\nSuccess!\n";
  clock_t t2 = clock() - t;
  printf("Execution time:\t%f\n\n",((float)t2)/CLOCKS_PER_SEC);
  exit(0);
}

void printList(list<int> &v) {
  for (it = v.begin(); it != v.end(); ++it) {
    cout << " " << *it;
  }
  cout << endl;
}
	
	


