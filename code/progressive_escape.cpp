// progressive_escape.cpp -- track subgroup escape costs on successive survivors.
//
// A prime survives budget D when every Type-II layer (d,e), d<=D, misses.
// Complementing a divisor changes the layer target -n to the fixed target -1.
// For each checkpoint this program independently enumerates all subgroups of
// (Z/4dZ)^* and computes the minimum number of prime factors (with
// multiplicity) outside a subgroup that avoids -1 (equivalently, the minimum
// over odd-character kernels).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Factor {
  int prime;
  int exponent;
};

struct Layer {
  int d;
  int e;
};

static vector<int> spf;

static vector<Factor> factor(ll n) {
  vector<Factor> factors;
  while (n > 1) {
    int q = spf[n], exponent = 0;
    do {
      n /= q;
      ++exponent;
    } while (n % q == 0);
    factors.push_back({q, exponent});
  }
  return factors;
}

static bool exact_hit(const vector<Factor> &factors, int modulus, int target) {
  vector<char> seen(modulus, false);
  seen[1] = true;
  for (auto [q, exponent] : factors) {
    vector<char> next(modulus, false);
    int power = 1;
    for (int j = 0; j <= exponent; ++j) {
      for (int a = 1; a < modulus; ++a)
        if (seen[a]) next[(int)(1LL * a * power % modulus)] = true;
      power = (int)(1LL * power * (q % modulus) % modulus);
    }
    seen.swap(next);
  }
  return seen[target];
}

struct UnitGroup {
  int modulus;
  vector<int> units;
  vector<int> index;
  vector<vector<int>> product;
  vector<uint64_t> subgroups;

  explicit UnitGroup(int m) : modulus(m), index(m, -1) {
    for (int a = 1; a < m; ++a)
      if (gcd(a, m) == 1) {
        index[a] = (int)units.size();
        units.push_back(a);
      }
    if (units.size() > 64) {
      fprintf(stderr, "phi(%d)=%zu exceeds the uint64_t implementation\n", m,
              units.size());
      exit(2);
    }
    product.assign(units.size(), vector<int>(units.size()));
    for (size_t i = 0; i < units.size(); ++i)
      for (size_t j = 0; j < units.size(); ++j)
        product[i][j] = index[(int)(1LL * units[i] * units[j] % m)];
    enumerate_subgroups();
  }

  uint64_t extend(uint64_t subgroup, int generator) const {
    uint64_t result = subgroup;
    int power = index[1];
    do {
      uint64_t old = result;
      for (int h = 0; h < (int)units.size(); ++h)
        if (subgroup >> h & 1) result |= 1ULL << product[h][power];
      if (result == old && power == generator) break;
      power = product[power][generator];
    } while (power != index[1]);
    return result;
  }

  void enumerate_subgroups() {
    uint64_t identity = 1ULL << index[1];
    set<uint64_t> known{identity};
    subgroups.push_back(identity);
    for (size_t i = 0; i < subgroups.size(); ++i)
      for (int generator = 0; generator < (int)units.size(); ++generator) {
        uint64_t next = extend(subgroups[i], generator);
        if (known.insert(next).second) subgroups.push_back(next);
      }
  }

  int minimum_escape(const vector<Factor> &factors, int target) const {
    int target_index = index[target];
    int best = numeric_limits<int>::max();
    for (uint64_t subgroup : subgroups) {
      if (subgroup >> target_index & 1) continue;
      int cost = 0;
      for (auto [q, exponent] : factors)
        if (!(subgroup >> index[q % modulus] & 1)) cost += exponent;
      best = min(best, cost);
    }
    return best;
  }
};

static int square_kernel_root(int e) {
  int root = 1;
  for (int q = 2; q * q <= e; ++q) {
    if (e % q) continue;
    int exponent = 0;
    while (e % q == 0) {
      e /= q;
      ++exponent;
    }
    for (int j = 0; j < (exponent + 1) / 2; ++j) root *= q;
  }
  if (e > 1) root *= e;
  return root;
}

int main(int argc, char **argv) {
  ll lo = argc > 1 ? atoll(argv[1]) : 1000000;
  ll limit = argc > 2 ? atoll(argv[2]) : 100000000;
  int dmax = argc > 3 ? atoi(argv[3]) : 24;
  bool primes_only = !(argc > 4 && string(argv[4]) == "all");
  if (dmax > 32) {
    fprintf(stderr, "dmax must be at most 32 (so phi(4d)<=64)\n");
    return 2;
  }

  vector<Layer> layers;
  int maximum_e = 0;
  ll coprime_modulus = 1;
  for (int d = 1; d <= dmax; ++d)
    coprime_modulus = lcm(coprime_modulus, (ll)d);
  for (int d = 1; d <= dmax; ++d)
    for (int e = d; e <= d * d; ++e)
      if (d * d % e == 0 && square_kernel_root(e) == d) {
        layers.push_back({d, e});
        maximum_e = max(maximum_e, e);
      }

  spf.assign(limit + 4LL * maximum_e + 1, 0);
  for (ll i = 2; i < (ll)spf.size(); ++i)
    if (!spf[i])
      for (ll j = i; j < (ll)spf.size(); j += i)
        if (!spf[j]) spf[j] = (int)i;

  const vector<int> hard_classes = {1, 121, 169, 289, 361, 529};
  vector<ll> hard_primes;
  vector<int> first_hit_d;
  vector<Layer> first_hit_layer;
  for (ll t = lo / 840;; ++t) {
    bool in_range = false;
    for (int residue : hard_classes) {
      ll p = 840 * t + residue;
      if (p >= limit) continue;
      in_range = true;
      if (p < max<ll>(lo, 11) || (primes_only && spf[p] != p) ||
          (!primes_only && gcd(p, coprime_modulus) != 1))
        continue;
      int hit_d = dmax + 1;
      Layer hit{-1, -1};
      for (auto layer : layers) {
        if (layer.d > hit_d) break;
        ll n = p + 4LL * layer.e;
        int modulus = 4 * layer.d;
        int original_target = (int)((-n % modulus + modulus) % modulus);
        bool original_hit = exact_hit(factor(n), modulus, original_target);
        bool normalized_hit = exact_hit(factor(n), modulus, modulus - 1);
        assert(original_hit == normalized_hit);
        if (normalized_hit) {
          hit_d = layer.d;
          hit = layer;
          break;
        }
      }
      hard_primes.push_back(p);
      first_hit_d.push_back(hit_d);
      first_hit_layer.push_back(hit);
    }
    if (!in_range && 840 * t >= limit) break;
  }

  map<int, unique_ptr<UnitGroup>> groups;
  for (int d = 1; d <= dmax; ++d)
    groups[4 * d] = make_unique<UnitGroup>(4 * d);

  vector<int> checkpoints(dmax);
  iota(checkpoints.begin(), checkpoints.end(), 1);
  printf("range=[%lld,%lld) %s=%zu dmax=%d layers=%zu\n", lo, limit,
         primes_only ? "hard-primes" : "coprime-hard-class-integers", hard_primes.size(),
         dmax, layers.size());
  printf("\n# survivors and exact minimum escape costs\n");
  printf(" D survivors char_misses mult_misses max_escape  max-per-prime distribution\n");
  for (int checkpoint : checkpoints) {
    ll survivors = 0, character_misses = 0, multiplicity_misses = 0;
    int global_max = 0;
    map<int, int> prime_max_distribution;
    for (size_t i = 0; i < hard_primes.size(); ++i) {
      if (first_hit_d[i] <= checkpoint) continue;
      ++survivors;
      ll p = hard_primes[i];
      int prime_max = 0;
      for (auto layer : layers) {
        if (layer.d > checkpoint) break;
        int modulus = 4 * layer.d;
        ll n = p + 4LL * layer.e;
        int target = modulus - 1;
        vector<Factor> factors = factor(n);
        int escape = groups[modulus]->minimum_escape(factors, target);
        if (escape == 0)
          ++character_misses;
        else {
          ++multiplicity_misses;
          prime_max = max(prime_max, escape);
          global_max = max(global_max, escape);
        }
      }
      ++prime_max_distribution[prime_max];
    }
    printf("%2d %9lld %11lld %11lld %10d  ", checkpoint, survivors,
           character_misses, multiplicity_misses, global_max);
    for (auto [maximum, count] : prime_max_distribution)
      printf("%s%d:%d", maximum == prime_max_distribution.begin()->first ? "" : ",",
             maximum, count);
    printf("\n");
  }

  printf("\n# candidates surviving D=16, first later hit, and multiplicity misses through D=24\n");
  printf("p first_d first_e  multiplicity_misses=(d,e,escape)\n");
  int printed = 0;
  for (size_t i = 0; i < hard_primes.size(); ++i) {
    if (first_hit_d[i] <= 16) continue;
    ll p = hard_primes[i];
    printf("%lld %d %d ", p, first_hit_layer[i].d, first_hit_layer[i].e);
    for (auto layer : layers) {
      if (layer.d > min(dmax, 24) || layer.d >= first_hit_d[i]) break;
      int modulus = 4 * layer.d;
      ll n = p + 4LL * layer.e;
      int target = modulus - 1;
      int escape = groups[modulus]->minimum_escape(factor(n), target);
      if (escape > 0) printf("(%d,%d,%d)", layer.d, layer.e, escape);
    }
    printf("\n");
    if (++printed == 30) {
      printf("... additional survivors omitted ...\n");
      break;
    }
  }
}
