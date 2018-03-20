using namespace std;
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int memoDP(unordered_map<string, pair<int, int>> &DP, int v, int f, int P);
int calcDP(unordered_map<string, pair<int, int>> &DP, int v, int f, int P);
void solution(vector<int> &sol, int V, int F, int P);

string intToKey(int a, int b) { return to_string(a) + " " + to_string(b); }

int memoDP(unordered_map<string, pair<int, int>> &DP, int v, int f, int P) {
  string key = intToKey(v, f);
  if (!DP.count(key)) {
    DP[key].first = calcDP(DP, v, f, P);
    DP[key].second = 1;
  } else {
    DP[key].second += 1;
  }
  return DP[key].first;
}

int calcDP(unordered_map<string, pair<int, int>> &DP, int v, int f, int P) {
  int N = ((int)ceil(v / 2.0)) + f;
  if (P == 0) {
    return 0;
  } else if (!(v > 0 && f > 0)) {
    return 0;
  } else {
    return memoDP(DP, v - 1, f, P - 1) + memoDP(DP, v, f - 1, P - 1) + N;
  }
}

void solution(vector<int> &sol, int V, int F, int P) {
  int N = V + F;
  unordered_map<string, pair<int, int>> DP;
  int result = memoDP(DP, 2 * V, F, P);

  for (pair<string, pair<int, int>> element : DP) {
    cout << "Key   : " << element.first << endl;
    cout << "First : " << element.second.first << endl;
    cout << "Second: " << element.second.second << endl << endl;
  }
}

int main() {

  ifstream in("input.txt");

  int V, F, P;
  in >> V >> F >> P;
  int N = V + F;

  vector<int> sol;
  solution(sol, V, F, P);

  // double result;
  // ofstream out("output.txt");
  // out << scientific << setprecision(10) << result << endl;

  return 0;
}