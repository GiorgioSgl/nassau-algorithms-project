using namespace std;

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>

double potenzaPonderata(unordered_map<string, double> &DP, int v, int f, int mV,
                        int colpi, double prob);
double potenzaMemo(unordered_map<string, double> &DP, int v, int f, int mV,
                   int colpi, double prob);

string intToKey(int a, int b, int c) {
  return to_string(a) + " " + to_string(b) + " " + to_string(c);
}

double potenzaVecchia(int v, int f, int mV, int colpi, double prob) {

  if (colpi == 0) {
    return prob * (f * (mV + v));
  } else {
    double uno = 0, due = 0, tre = 0;
    if (v != 0)
      uno = potenzaVecchia(v - 1, f, mV + 1, colpi - 1,
                           prob * ((double)v / (v + f + mV)));
    if (f != 0)
      due = potenzaVecchia(v, f - 1, mV, colpi - 1,
                           prob * ((double)f / (v + f + mV)));
    if (mV != 0)
      tre = potenzaVecchia(v, f, mV - 1, colpi - 1,
                           prob * ((double)mV / (v + f + mV)));

    return uno + due + tre;
  }
}

double potenzaPonderata(unordered_map<string, double> &DP, int v, int f, int mV,
                        int colpi, double prob) {

  if (colpi == 0) {
    return prob * (f * (mV + v));
  } else {
    double uno = 0, due = 0, tre = 0;
    if (v != 0)
      uno = potenzaMemo(DP, v - 1, f, mV + 1, colpi - 1,
                        prob * ((double)v / (v + f + mV)));
    if (f != 0)
      due = potenzaMemo(DP, v, f - 1, mV, colpi - 1,
                        prob * ((double)f / (v + f + mV)));
    if (mV != 0)
      tre = potenzaMemo(DP, v, f, mV - 1, colpi - 1,
                        prob * ((double)mV / (v + f + mV)));

    return uno + due + tre;
  }
}

double potenzaMemo(unordered_map<string, double> &DP, int v, int f, int mV,
                   int colpi, double prob) {
  string key = intToKey(v, f, mV);
  if (DP.count(key) == 0) {
    DP[key] = potenzaPonderata(DP, v, f, mV, colpi, prob);
  }
  return DP[key];
}

int main() {

  ifstream in("input.txt");

  int v, f, c;
  in >> v >> f >> c;
  // cout << ((double)v/(f+v));
  unordered_map<string, double> DP;
  double res = potenzaPonderata(DP, v, f, 0, c, 1);

  for (pair<string, double> element : DP) {
    cout << element.first << " => " << element.second << endl;
  }

  ofstream out("output.txt");
  out << scientific << setprecision(10) << res << endl;

  return 0;
}