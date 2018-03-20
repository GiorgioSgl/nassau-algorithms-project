using namespace std;
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int finals(int v, int f, int mv, int c) {
  if (c <= 0) {
    return 1;
  } else {
    int res = 0;
    if (v > 0) {
      res += finals(v - 1, f, mv + 1, c - 1) * v;
    }
    if (f > 0) {
      res += finals(v, f - 1, mv, c - 1) * f;
    }
    if (mv > 0) {
      res += finals(v, f, mv - 1, c - 1) * mv;
    }
    return res;
  }
}

int main() {

  ifstream in("input.txt");
  // string id;
  // cin >> id;
  // ifstream in("dataset/input/input" + id + ".txt");

  int V, F, MV = 0, C;
  in >> V >> F >> C;

  int res = finals(V, F, MV, C);

  cout << res << endl;

  return 0;
}