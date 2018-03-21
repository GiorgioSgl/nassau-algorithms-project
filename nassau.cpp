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
  return DP[key];
}

double iterPotenza(int v, int f, int mV, int colpi) {
  // DP 3d matrix init
  vector<vector<vector<double>>> DP;
  DP.resize(v + 1);
  for (int i = 0; i <= v; i++) {
    DP[i].resize(f + 1);
    for (int j = 0; j <= f; j++) {
      DP[i][j].resize(v + 1);
    }
  }

  // Casi base: (v==0 and mV==0) e (f==0)
  for (int j = 0; j <= f; j++) {
    DP[0][j][0] = 0;
  }
  for (int i = 0; i <= v; i++) {
    for (int k = 0; k <= v; k++) {
      DP[i][0][k] = 0;
    }
  }

  // Quali sono i casi partenza?
  int vstart = v - colpi > 0 ? v - colpi : 0;
  int fstart = f - colpi > 0 ? f - colpi : 0;

  // Casi partenza
  for (int i = vstart; i <= v; i++) {
    for (int k = 0; k <= v; k++) {
      DP[i][fstart][k] = fstart * (i + k);
    }
  }
  for (int j = fstart; j <= f; j++) {
    for (int k = 0; k <= v; k++) {
      DP[vstart][j][k] = j * (vstart + k);
    }
  }

  for (int i = vstart + 1; i <= v; i++) {
    for (int j = fstart + 1; j <= f; j++) {
      for (int k = 1; k <= v; k++) {
        double tmp = (i * DP[i - 1][j][k + 1] + f * DP[i][j - 1][k] +
                      k * DP[i][j][k - 1]) /
                     ((double)i + j + k);
        DP[i][j][k];
      }
    }
  }

  cout << DP[v][f][mV] << endl;
}

int main() {

  ifstream in("input.txt");
  // string id;
  // cin >> id;
  // ifstream in("dataset/input/input" + id + ".txt");

  int v, f, c;
  in >> v >> f >> c;

  iterPotenza(v, f, 0, c);

  // unordered_map<string, double> DP;
  // double res = c >= (2 * v + f) ? 0 : potenzaPonderata(DP, v, f, 0, c);

  // ofstream out("output.txt");
  // out << scientific << setprecision(10) << res << endl;

  return 0;
}
