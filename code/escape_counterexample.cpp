// escape_counterexample.cpp -- a family excluding a uniform group-only escape bound.
//
// In C_(2m), take m-1 copies of a generator g.  After complementing divisors,
// the layer target is -1=g^m, and the subset products miss it.  Every subgroup
// avoiding g^m also avoids g, so all m-1 terms escape.  Taking m-1 copies each
// of g and g^(-1) still misses g^m and raises the escape to 2m-2=|G|-2.
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
  printf("m group_order target one_class_escape two_class_escape\n");
  for (int m = 2; m <= maximum_m; ++m) {
    int order = 2 * m;
    int target = m;  // The normalized layer target -1 = g^m.
    vector<char> one_class_sums(order, false), two_class_sums(order, false);
    for (int positive = 0; positive <= m - 1; ++positive) {
      one_class_sums[positive] = true;
      for (int negative = 0; negative <= m - 1; ++negative)
        two_class_sums[(positive - negative + order) % order] = true;
    }

    int one_class_escape = numeric_limits<int>::max();
    int two_class_escape = numeric_limits<int>::max();
    for (const auto &subgroup : subgroups_of_cyclic(order)) {
      if (subgroup[target]) continue;
      one_class_escape = min(one_class_escape, subgroup[1] ? 0 : m - 1);
      int cost = (subgroup[1] ? 0 : m - 1) +
                 (subgroup[order - 1] ? 0 : m - 1);
      two_class_escape = min(two_class_escape, cost);
    }
    printf("%d %d %d %d %d\n", m, order, target, one_class_escape,
           two_class_escape);
    assert(!one_class_sums[target]);
    assert(!two_class_sums[target]);
    assert(one_class_escape == m - 1);
    assert(two_class_escape == 2 * m - 2);
  }
}
