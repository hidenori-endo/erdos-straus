#!/usr/bin/env python3
"""ES 解の総当たりと、shift k / 箱 Div(C_k) vs Div(C_k^2) の判定を突き合わせる。

  python3 code/box_check.py        # p < 700 (数秒)
  python3 code/box_check.py 1500   # 上限を指定

主張 (検証対象):
  4/p = 1/x+1/y+1/z の任意の解で、p∤x なる分母 x をとり k = 4x-p (≡3 mod 4), C_k = x.
    Type II (p|y, p|z):  ∃ D | C_k^2, D ≡ -C_k (mod k)
    Type I  (p|y, p∤z):  ∃ D | C_k^2, D ≡ -1/4  (mod k)
  逆に D が与えられれば解が復元できる。
  Div(C_k) (指数 0..e) だけでは足りない例があるか。
"""
import sys
from math import gcd
from sympy import isprime, factorint

def divisors_from_fact(f, mult):
    ds = [1]
    for q, e in f.items():
        ds = [d * q**i for d in ds for i in range(mult*e + 1)]
    return ds

def box_hit(p, k, mult):
    C = (p + k) // 4
    f = factorint(C)
    inv4 = pow(4, -1, k)
    t1 = (-inv4) % k
    t2 = (-C) % k
    ds = divisors_from_fact(f, mult)
    S = {d % k for d in ds}
    return (t1 in S), (t2 in S), ds, t1, t2

def reconstruct(p, k, D, typ):
    C = (p + k) // 4
    x = C
    if typ == 2:
        # D = k y' - C,  D2 = C^2/D = k z' - C
        D2 = C*C // D
        assert (D + C) % k == 0 and (D2 + C) % k == 0
        y = p * ((D + C) // k); z = p * ((D2 + C) // k)
    else:
        D2 = C*C // D
        assert (p*D + C) % k == 0 and (D2 + p*C) % k == 0
        y = p * ((p*D + C) // k); z = (D2 + p*C) // k
    from fractions import Fraction as F
    assert F(1,x)+F(1,y)+F(1,z) == F(4,p), (p,k,D,typ,x,y,z)
    return x, y, z

def brute_solutions(p):
    """4/p = 1/x+1/y+1/z, x<=y<=z の全解 (整数演算)."""
    sols = []
    x = p // 4 + 1
    while 3 * p >= 4 * x:                # 3/x >= 4/p
        a, b = 4*x - p, p*x              # 4/p - 1/x = a/b
        g = gcd(a, b); a //= g; b //= g
        y = max(x, (b + a - 1)//a)       # 1/y <= a/b
        while 2 * b >= a * y:            # 2/y >= a/b
            num = a*y - b
            if num > 0 and (b*y) % num == 0:
                z = (b*y)//num
                if z >= y: sols.append((x, y, z))
            y += 1
        x += 1
    return sols

def main():
    LIM = int(sys.argv[1]) if len(sys.argv) > 1 else 1500
    n_sol = 0; n_gap = 0; gap_examples = []
    hit_k_by_p = {}
    for p in range(5, LIM):
        if not isprime(p) or p % 4 != 1:
            continue
        sols = brute_solutions(p)
        ks_from_sols = set()
        for (x, y, z) in sols:
            dens = [x, y, z]
            nonp = [d for d in dens if d % p]
            pmul = [d for d in dens if d % p == 0]
            assert 1 <= len(nonp) <= 3
            for xx in nonp:
                k = 4*xx - p
                assert k > 0 and k % 4 == 3
                C = xx
                # 種類: 残り2項のうち p の倍数の個数
                others = [d for d in dens if d != xx] if dens.count(xx) == 1 else dens[:]
                if dens.count(xx) > 1:
                    others = list(dens); others.remove(xx)
                cnt = sum(1 for d in others if d % p == 0)
                if k >= p:      # p | k の可能性がある領域は除外 (k = 3p など)
                    continue
                h1, h2, ds, t1, t2 = box_hit(p, k, 2)
                if cnt == 2:
                    assert h2, ("TypeII sol but D|C^2 target -C missing", p, k, (x,y,z))
                elif cnt == 1:
                    assert h1, ("TypeI sol but D|C^2 target -1/4 missing", p, k, (x,y,z))
                else:
                    # 0 個: p がどの分母も割らない -> 4/p の分母 p が消える: 不可能
                    raise AssertionError(("no p-multiple", p, (x,y,z)))
                ks_from_sols.add(k)
                n_sol += 1
        # 逆向き: 箱が hit する全 k (< p) で解を復元し、総当たり解集合に含まれるか
        for k in range(3, p, 4):
            h1, h2, ds, t1, t2 = box_hit(p, k, 2)
            s1, s2, _, _, _ = box_hit(p, k, 1)
            C = (p + k)//4
            if h2:
                D = next(d for d in ds if d % k == t2)
                sol = tuple(sorted(reconstruct(p, k, D, 2)))
                assert sol in sols, ("reconstructed II not in brute", p, k, sol)
            if h1:
                D = next(d for d in ds if d % k == t1)
                sol = tuple(sorted(reconstruct(p, k, D, 1)))
                assert sol in sols, ("reconstructed I not in brute", p, k, sol)
            if (h1 or h2) and not (s1 or s2):
                n_gap += 1
                if len(gap_examples) < 12:
                    gap_examples.append((p, k, C, factorint(C), 'I' if h1 else '', 'II' if h2 else ''))
            if (s1 or s2):
                assert (h1 or h2)
            if h1 or h2:
                assert k in ks_from_sols, (p, k)
    print(f"primes p<{LIM}, p≡1 mod 4: all brute-force solutions map to Div(C_k^2) targets, "
          f"and all box hits reconstruct to real solutions. checked {n_sol} (solution, x) pairs")
    print(f"(p,k) with Div(C_k^2) hit but Div(C_k) miss: {n_gap}")
    for g in gap_examples:
        print("   ", g)

main()
