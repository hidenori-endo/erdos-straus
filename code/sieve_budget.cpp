// sieve_budget.cpp -- size of the fixed-D layer sieve parameters.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static int omega(int n) {
  int count = 0;
  for (int q = 2; 1LL * q * q <= n; ++q) {
    if (n % q) continue;
    ++count;
    while (n % q == 0) n /= q;
  }
  if (n > 1) ++count;
  return count;
}

static int phi(int n) {
  int result = n;
  for (int q = 2; 1LL * q * q <= n; ++q) {
    if (n % q) continue;
    result -= result / q;
    while (n % q == 0) n /= q;
  }
  if (n > 1) result -= result / n;
  return result;
}

int main(int argc, char **argv) {
  vector<int> budgets;
  for (int i = 1; i < argc; ++i) budgets.push_back(atoi(argv[i]));
  if (budgets.empty()) budgets = {1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 24, 32, 48, 64, 96, 128};
  printf(" D      L(D)   dimension        B_D      B_D/L     log C_D   C_D^(1/L)\n");
  for (int D : budgets) {
    ll layers = 0, escape = 0;
    long double log_character_assignments = 0;
    for (int d = 1; d <= D; ++d) {
      ll count = 1LL << omega(d);
      layers += count;
      escape += count * (phi(4 * d) - 1LL);
      log_character_assignments += count * log((long double)phi(4 * d));
    }
    printf("%3d %9lld %11.1f %10lld %10.1f %11.1Lf %13.2Lf\n", D,
           layers, 1.0 + layers / 2.0, escape, (double)escape / layers,
           log_character_assignments,
           exp(log_character_assignments / layers));
  }
}
