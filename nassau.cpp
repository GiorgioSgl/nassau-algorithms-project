using namespace std;
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

double takeDownProb(int v, int f, int V, int F, int colpi) {
  if (v == 0 && f == 0) {
    return 1;
  } else if (2 * v + f >= colpi) {
    return v * f;
  } else {
    double tookDownV = 0;
    if (v > 0) {
      tookDownV = ((double)V / ((double)(V + F) * (V + F))) *
                  takeDownProb(v - 1, f, V - 1, F, colpi - 2);
    }
    double tookDownF = 0;
    if (f > 0) {
      tookDownF = ((double)F / ((double)V + F)) *
                  takeDownProb(v, f - 1, V, F - 1, colpi - 1);
    }

    return tookDownV + tookDownF;
  }
}

int main() {

  ifstream in("input.txt");
  // string id;
  // cin >> id;
  // ifstream in("dataset/input/input" + id + ".txt");

  int V, F, C;
  in >> V >> F >> C;

  int i, j;
  cin >> i >> j;

  cout << takeDownProb(i, j, V, F, C) << endl;

  return 0;
}