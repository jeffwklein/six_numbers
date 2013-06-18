#include <unistd.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <csignal>

using namespace std;


//function name declarations
void permute(vector<int> & startList, vector<int> & endList);
static void sig_usr(int); //signal handler
vector<int> add(vector<int> & v);
vector<int> subtract(vector<int> & v);
vector<int> multiply(vector<int> & v);
vector<int> divide(vector <int> & v);
void clearbuffer(int b);
void printSteps();
void printList(vector<int> &);

//global data declarations
int target;
int counter, perms;
int childCount = 0;
int bufindex;
int pid;
double startTime, endTime;
char buffer[5][20];
string newStep;

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
  counter = 0;
  startTime = time(NULL);
  vector<int> vec;
  permute(vec, inputNumbers);
}

void permute(vector<int> & startList, vector<int> & endList) {
  if (endList.size() == 1) {
    startList.push_back(endList[0]);
    if (startList.size() == 6) {
      if (counter == 24 || counter == 0) {
	counter = 0;
	perms++;
	cout << perms << ":\t";
	printList(startList);
      }
      counter++;
    }
    if (startList.size() > 1 && counter == 1) {
	for (int i = 0; i < 4; i++) {
	  vector<int> temp;
	  switch (i) {
	  case 0 : temp = add(startList);
	    break;
	  case 1 : temp = subtract(startList);
	    break;
	  case 2 : temp = multiply(startList);
	    break;
	  case 3 : temp = divide(startList);
	    break;
	  }//end switch
	  if (temp.size() > 0) {
	    vector<int> newVec;
	    permute(newVec, temp);
	    clearbuffer(-1 * (startList.size() - 6));
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

vector<int> add(vector<int> & v) {
  int test = v[0] + v[1];
  bufindex = -1 * (v.size() - 6);
  sprintf(buffer[bufindex], "%d + %d = %d", v[0], v[1], test);
  if (test == target) {    
    printSteps();
    return v;
  }
  else if (test > 0) {
    vector<int> r (v);
    r.erase(r.begin());
    r.erase(r.begin());
    r.insert(r.begin(), test);
    return r;
  }
  else {
    clearbuffer(bufindex);
    vector<int> empty;
    return empty;
  }
}

vector<int> subtract(vector<int> & v) {
  int test = v[0] - v[1];
  bufindex = -1 * (v.size() - 6);
  sprintf(buffer[bufindex], "%d - %d = %d", v[0], v[1], test);
  if (test == target) {
    printSteps();
    return v;
  }
  else if (test > 0) {
    vector<int> r (v);
    r.erase(r.begin());
    r.erase(r.begin());
    r.insert(r.begin(), test);
    return r;
  }
  else {
    clearbuffer(bufindex);
    vector<int> empty;
    return empty;
  }
}
	
vector<int> multiply(vector<int> & v) {
  int test = v[0] * v[1];
  bufindex = -1 * (v.size() - 6);
  sprintf(buffer[bufindex], "%d * %d = %d", v[0], v[1], test);
  if (test == target) {
    printSteps();
    return v;
  }
  else if (test > 0) {
    vector<int> r (v);
    r.erase(r.begin());
    r.erase(r.begin());
    r.insert(r.begin(), test);
    return r;
  }
  else {
    clearbuffer(bufindex);
    vector<int> empty;
    return empty;
  }	
}


vector<int> divide(vector<int> & v) {
  int test;
  vector<int> empty;
  if (v[0] == 0 || v[1] == 0) {
    return empty;
  }
  else if (v[0] % v[1] > 0 || v[0] < v[1]) {
    return empty;
  }
  else {
    test = v[0] / v[1];
    bufindex = -1 * (v.size() - 6);
    sprintf(buffer[bufindex], "%d / %d = %d", v[0], v[1], test);
  }
  if (test == target) {
    printSteps();
    return empty;
  }
  else {
    vector<int> r (v);
    r.erase(r.begin());
    r.erase(r.begin());
    r.insert(r.begin(), test);
    return r;
  }
}

void clearbuffer(int buf) {
  for (int i = 0; i < 20; i++) {
    buffer[buf][i] = '\0';
  }
}


void printSteps() {
  for (int i = 0; i < 5; i++) {
    if (buffer[i][0] != '\0') {
      cout << buffer[i] << endl;
    }
  }
  cout << "\nSuccess!\n";
  endTime = time(NULL);
  double totalTime = (double)(endTime - startTime);
  cout << "Execution time: " << totalTime << "\n" << endl;
  //  "Execution time: " + (((double)(endTime-startTime))/1000) + " seconds";
  exit(0);
}
	
void printList(vector<int> &v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
}
	
	


