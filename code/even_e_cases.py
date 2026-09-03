#!/usr/bin/env python3
"""center 固定 shift (k | 840, k ≡ 3 mod 4: k=3,7,15,35) の annihilation を、閉包モデルを
使わずに有限の場合分けで証明する。

hard prime では χ(C_k) = jacobi(p,k) = +1 なので p-NR 素因子の個数 E は偶数。非 pure なら
E ≥ 2 で、NR 剰余 r1, r2 と残りの QR 部分 m (m ≡ c/(seed·r1·r2)) について、真の箱
Div(C_k²) mod k は必ず

    B(r1,r2,m) = Div(seed²)·{1,r1,r1²}·{1,r2,r2²}·{1,m,m²}

を含む (同じ素数の 2 乗、E ≥ 4、m が合成数の場合も単調性で吸収される)。従って
全ての (r1,r2) ∈ NR² で B が t1 = -1/4 または t2 = -c を含めば、その class は
「非 pure ⇒ hit」、すなわち miss ⇔ pure。

  python3 code/even_e_cases.py        # k = 3, 7, 15, 35
  python3 code/even_e_cases.py 35
"""
import sys
from math import gcd
from sympy import jacobi_symbol as J, factorint

HARD = [1, 121, 169, 289, 361, 529]


def prod(k, *sets):
    out = {1}
    for s in sets:
        out = {(a * b) % k for a in out for b in s}
    return out


def main():
    ks = [int(a) for a in sys.argv[1:]] or [3, 7, 15, 35]
    for k in ks:
        assert 840 % k == 0 and k % 4 == 3, "center 固定 shift のみ"
        U = [x for x in range(1, k) if gcd(x, k) == 1]
        NR = [x for x in U if J(x, k) == -1]
        t1 = (-pow(4, -1, k)) % k
        print(f"== k={k}  NR={NR}  t1={t1}")
        for h in HARD:
            c = ((h + k) // 4) % k
            t2 = (-c) % k
            seed = gcd(210, (h + k) // 4)
            D0 = prod(k, *[{1, q % k, q * q % k} for q in factorint(seed)]) if seed > 1 else {1}
            missing = []
            for r1 in NR:
                for r2 in NR:
                    if r2 < r1:
                        continue
                    m = c * pow(seed * r1 * r2, -1, k) % k
                    B = prod(k, D0, {1, r1, r1 * r1 % k}, {1, r2, r2 * r2 % k}, {1, m, m * m % k})
                    if t1 not in B and t2 not in B:
                        missing.append((r1, r2, m))
            verdict = "miss ⇔ pure (PROVED)" if not missing else f"{len(missing)} non-pure miss cases"
            print(f"  h={h:3d} seed={seed:2d} c={c:2d} t2={t2:2d}: {verdict} {missing}")


if __name__ == '__main__':
    main()
