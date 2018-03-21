using namespace std;

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>

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

int main() {

  ifstream in("input.txt");
  // string id;
  // cin >> id;
  // ifstream in("dataset/input/input" + id + ".txt");

  int v, f, c;
  in >> v >> f >> c;

  unordered_map<string, double> DP;
  double res = c >= (2 * v + f) ? 0 : potenzaPonderata(DP, v, f, 0, c);

  ofstream out("output.txt");
  out << scientific << setprecision(10) << res << endl;

  return 0;
}
