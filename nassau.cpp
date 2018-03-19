using namespace std;
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int memoDP(unordered_map<string, pair<int, int>> &DP, int v, int f, int P,
           int N);
int calcDP(unordered_map<string, pair<int, int>> &DP, int v, int f, int P,
           int N);
void solution(vector<int> &sol, int V, int F, int P);

string intToKey(int a, int b) { return to_string(a) + to_string(b); }

int memoDP(unordered_map<string, pair<int, int>> &DP, int v, int f, int P,
           int N) {
  string key = intToKey(v, f);
  if (!DP.count(key)) {
    DP[key].first = calcDP(DP, v, f, P, N);
    DP[key].second = 1;
  } else {
    DP[key].second += 1;
  }
  return DP[key].first;
}

int calcDP(unordered_map<string, pair<int, int>> &DP, int v, int f, int P,
           int N) {
  if (P == 0) {
    return 0;
  } else if (!(v > 0 && f > 0)) {
    return 0;
  } else {
    return memoDP(DP, v - 1, f + 1, P - 1, N) + memoDP(DP, v, f - 1, P - 1, N) +
           N;
  }
}

void solution(vector<int> &sol, int V, int F, int P) {
  int N = V + F;
  unordered_map<string, pair<int, int>> DP;
  int result = memoDP(DP, 2 * V, F, P, N);

  for (pair<string, pair<int, int>> element : DP) {
    cout << "Key: " << element.first << endl;
    cout << "Second: " << element.second.second << endl << endl;
  }
}

// int iterDP(int V, int F, int P, int N) {
//   // Init of DP
//   vector<vector<int>> DP;
//   DP.resize(V + 1);
//   for (int i = 0; i <= V; i++) {
//     DP[i].resize(V + F + 1);
//   }
//   // buffer line for i = 0
//   for (int j = 0; j <= V + F; j++) {
//     DP[0][j] = 0;
//   }
//   // buffer line for j = 0
//   for (int i = 0; i <= V; i++) {
//     DP[i][0] = 0;
//   }

//   // DP construction
//   int i, j;
//   for (i = 1; i <= V && P >= 0; i++) {
//     DP[i][0] = DP[i - 1][1];
//     for (j = 1; j <= V + F && P > 0; j++) {
//       DP[i][j] = DP[i - 1][j + 1] + DP[i][j - 1] + N;
//       P--;
//     }
//   }
//   return DP[i - 1][j - 1];
// }

int main() {

  ifstream in("input.txt");

  int V, F, P;
  in >> V >> F >> P;
  int N = V + F;

  // cout << pureDP(2 * V, F, P, N) << endl;
  // cout << iterDP(2 * V, F, P, N) << endl;

  vector<int> sol;
  solution(sol, V, F, P);

  // double result;
  // ofstream out("output.txt");
  // out << scientific << setprecision(10) << result << endl;

  return 0;
}