// escape_counterexample.cpp -- a family excluding a uniform group-only escape bound.
//
// In C_(2m), take m-1 copies of a generator g.  Their product is c=g^(m-1),
// the layer-shaped target (-1)c is g^(-1), and the subset products miss it.
// Every subgroup avoiding g^(-1) also avoids g, so all m-1 terms escape.
#include <bits/stdc++.h>
using namespace std;

static vector<vector<int>> subgroups_of_cyclic(int order) {
  vector<vector<int>> groups;
  for (int divisor = 1; divisor <= order; ++divisor) {
    if (order % divisor) continue;
    vector<int> subgroup(order, false);
    for (int exponent = 0; exponent < order; exponent += divisor)
      subgroup[exponent] = true;
    groups.push_back(move(subgroup));
  }
  return groups;
}

int main(int argc, char **argv) {
  int maximum_m = argc > 1 ? atoi(argv[1]) : 31;
  printf("m group_order target missed minimum_escape\n");
  for (int m = 2; m <= maximum_m; ++m) {
    int order = 2 * m;
    int terms = m - 1;
    int target = order - 1;  // g^m * g^(m-1) = g^(-1).
    vector<char> subset_products(order, false);
    for (int chosen = 0; chosen <= terms; ++chosen)
      subset_products[chosen] = true;

    int minimum_escape = numeric_limits<int>::max();
    for (const auto &subgroup : subgroups_of_cyclic(order)) {
      if (subgroup[target]) continue;
      int escape = subgroup[1] ? 0 : terms;
      minimum_escape = min(minimum_escape, escape);
    }
    printf("%d %d %d %s %d\n", m, order, target,
           subset_products[target] ? "no" : "yes", minimum_escape);
    assert(!subset_products[target]);
    assert(minimum_escape == m - 1);
  }
}
