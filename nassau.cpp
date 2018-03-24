using namespace std;
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

double takeDownProb(int v, int f, int V, int F, int colpi) {
  if (colpi < 0) {
    return 0;
  } else if (colpi == 0) {
    return 1;
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

    double dropOnMV = 0;
    int MV = colpi - 2 * v - f;
    if (MV > 0) {
      // if (v <= 0 && f <= 0 && colpi > 0) {
      dropOnMV = ((double)MV / ((double)(V + F))) *
                 takeDownProb(v, f, V, F, colpi - 1);
    }

    return tookDownV + tookDownF + dropOnMV;
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

  double res = takeDownProb(i, j, V, F, C);

  cout << scientific << setprecision(10) << res << endl;

  return 0;
}