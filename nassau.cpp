using namespace std;
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int alternative(int v, int f, int mv, int c) {
  if (c <= 0) {
    return 0;
  } else if (v <= 0 && mv <= 0 && f <= 0) {
    return 0;
  } else {
    int res = v + mv + f;
    if (v > 0) {
      res += alternative(v - 1, f, mv + 1, c - 1);
    }
    if (f > 0) {
      res += alternative(v, f - 1, mv, c - 1);
    }
    if (mv > 0) {
      res += alternative(v, f, mv - 1, c - 1);
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

  int res = alternative(V, F, MV, C);

  cout << res << endl;

  return 0;
}