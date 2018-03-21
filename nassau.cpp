using namespace std;

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

double iterPotenza(int V, int F, int mV, int colpi) {
  int dim = 2;
  // // DP 3d matrix init
  // vector<vector<vector<double>>> DP;
  // DP.resize(dim);
  // for (int i = 0; i < dim; i++) {
  //   DP[i].resize(F + 1);
  //   for (int j = 0; j <= F; j++) {
  //     DP[i][j].resize(V + 1);
  //   }
  // }
  double DP[dim][dim][V + 1];

  // for (int i = 0; i < dim; i++) {
  //   for (int j = 0; j <= F; j++) {
  //     for (int k = 0; k <= V; k++) {
  //       DP[i][j][k] = 0.0;
  //     }
  //   }
  // }

  int currentI, previousI;
  int currentJ, previousJ;

  for (int i = 0; i <= V; i++) {
    currentI = i % 2;
    previousI = (i - 1) % 2;
    for (int j = 0; j <= F; j++) {
      currentJ = j % 2;
      previousJ = (j - 1) % 2;
      for (int k = 0; k <= V; k++) {
        // Se colpi andati, restituisci potenza!
        int colpiSparati = 2 * (V - i) - k + F - j;
        if (colpiSparati > colpi) {
          DP[currentI][currentJ][k] = 0.0;
        } else if (colpiSparati == colpi) {
          double tmp = (i + k) * j;
          DP[currentI][currentJ][k] = tmp;
        } else {
          double uno, due, tre;
          if (i > 0 && k < V) {
            uno = ((double)i) * DP[previousI][currentJ][k + 1];
          } else {
            uno = 0;
          }
          if (j > 0) {
            due = ((double)j) * DP[currentI][previousJ][k];
          } else {
            due = 0;
          }
          if (k > 0) {
            tre = ((double)k) * DP[currentI][currentJ][k - 1];
          } else {
            tre = 0;
          }

          double res = ((double)uno + due + tre) / ((double)i + j + k);

          DP[currentI][currentJ][k] = res;
        }
      }
    }
  }

  // for (int i = 0; i < dim; i++) {
  //   for (int j = 0; j < dim; j++) {
  //     for (int k = 0; k <= V; k++) {
  //       cout << "DP[" << i << "][" << j << "][" << k << "] = " << DP[i][j][k]
  //            << endl;
  //     }
  //   }
  // }

  return DP[1][1][0];
}

int main() {

  // ifstream in("input.txt");
  string id;
  cin >> id;
  ifstream in("dataset/input/input" + id + ".txt");

  int v, f, c;
  in >> v >> f >> c;

  double res = c >= (2 * v + f) ? 0 : iterPotenza(v, f, 0, c);

  ofstream out("output.txt");
  out << scientific << setprecision(10) << res << endl;

  return 0;
}
