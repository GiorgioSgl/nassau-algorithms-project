using namespace std;

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

double potenzaPonderata(unordered_map<string, double> &DP, int v, int f, int mV,
                        int colpi);
double potenzaMemo(unordered_map<string, double> &DP, int v, int f, int mV,
                   int colpi);

string intToKey(int a, int b, int c) {
  return to_string(a) + " " + to_string(b) + " " + to_string(c);
}

double potenzaPonderata(unordered_map<string, double> &DP, int v, int f, int mV,
                        int colpi) {
  if ((v == 0 && mV == 0) || f == 0) {
    return 0;
  } else if (colpi == 0) {
    return f * (mV + v);
  } else {
    double uno = 0, due = 0, tre = 0;
    if (v != 0)
      uno = ((double)v) * potenzaMemo(DP, v - 1, f, mV + 1, colpi - 1);
    if (f != 0)
      due = ((double)f) * potenzaMemo(DP, v, f - 1, mV, colpi - 1);
    if (mV != 0)
      tre = ((double)mV) * potenzaMemo(DP, v, f, mV - 1, colpi - 1);

    return (uno + due + tre) / (v + f + mV);
  }
}

double potenzaMemo(unordered_map<string, double> &DP, int v, int f, int mV,
                   int colpi) {
  string key = intToKey(v, f, mV);
  if (DP.count(key) == 0) {
    DP[key] = potenzaPonderata(DP, v, f, mV, colpi);
  }
  cout << "DP(" << v << ", " << f << ", " << mV << ") = " << DP[key] << endl;
  return DP[key];
}

double iterPotenza(int V, int F, int mV, int colpi) {
  // DP 3d matrix init
  // vector<vector<vector<double>>> DP;
  // DP.resize(V + 1);
  // for (int i = 0; i <= V; i++) {
  //   DP[i].resize(F + 1);
  //   for (int j = 0; j <= F; j++) {
  //     DP[i][j].resize(V + 1);
  //   }
  // }
  double DP[V + 1][F + 1][V + 1];

  // Casi base: (V==0 and mV==0) e (F==0)
  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 1; j++) {
      for (int k = 0; k <= 1; k++) {
        DP[i][j][k] = (i + k) * j;
      }
    }
  }

  for (int i = 0; i <= V; i++) {
    for (int j = 0; j <= F; j++) {
      for (int k = 0; k <= V; k++) {
        // Se colpi andati, restituisci potenza!
        int colpiSparati = 2 * (V - i) - k + F - j;
        if (colpiSparati > colpi) {
          DP[i][j][k] = 0;
        } else if (colpiSparati == colpi) {
          double tmp = (i + k) * j;
          DP[i][j][k] = tmp;
        } else {
          double uno, due, tre;
          if (i > 0 && k < V) {
            uno = ((double)i) * DP[i - 1][j][k + 1];
          } else {
            uno = 0;
          }
          if (j > 0) {
            due = ((double)j) * DP[i][j - 1][k];
          } else {
            due = 0;
          }
          if (k > 0) {
            tre = ((double)k) * DP[i][j][k - 1];
          } else {
            tre = 0;
          }

          double res = ((double)uno + due + tre) / ((double)i + j + k);

          DP[i][j][k] = res;
        }
      }
    }
  }

  // for (int i = 0; i <= V; i++) {
  //   for (int j = 0; j <= F; j++) {
  //     for (int k = 0; k <= V; k++) {
  //       cout << "DP[" << i << "][" << j << "][" << k << "] = " << DP[i][j][k]
  //            << endl;
  //     }
  //   }
  // }

  return DP[V][F][mV];
}

int main() {

  ifstream in("input.txt");
  // string id;
  // cin >> id;
  // ifstream in("dataset/input/input" + id + ".txt");

  int v, f, c;
  in >> v >> f >> c;

  // unordered_map<string, double> DP;
  double res = c >= (2 * v + f) ? 0 : iterPotenza(v, f, 0, c);

  ofstream out("output.txt");
  out << scientific << setprecision(10) << res << endl;

  return 0;
}
