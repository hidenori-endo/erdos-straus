#!/usr/bin/env python3
"""k >= 19 の各 (shift k, hard class h) に対し「miss かつ非 pure」な実素数を構成する。

topics/07-character-annihilation-atlas.md の「k >= 19 で同値が成立するのは 9 組だけ」の
再現用。閉包モデルを一切使わず、実素数 p と C_k = (p+k)/4 の完全分解だけで判定する。
箱は正しい exact box、すなわち C_k^2 の約数（素因子ごとに指数 0..2e）の mod k 剰余。

  python3 code/witness.py            # k = 19..403, 6 hard class, 上限 p < 2e7
  python3 code/witness.py 19 63 1e6  # k の範囲と探索上限を指定

出力: 各 (k,h) の最小 witness。witness の無い組があれば末尾に列挙される。
      既知の結果 (p < 10^8 の C++ 監査): witness が無いのは
      (19,121) (31,169) (31,289) (31,529) (35,121) (35,361) (47,121) (47,289) (59,361)
      の 9 組。(71,289) は p = 3,098,209 に witness があるので 2e6 では見落とす。
      witness を持つ組の最大の最小 witness はその p = 3,098,209。
"""
import sys
from sympy import isprime, factorint
from sympy.functions.combinatorial.numbers import jacobi_symbol as J

HARD = [1, 121, 169, 289, 361, 529]


def witness(k, h, lim):
    """p = h (mod 840) の hard prime で miss かつ非 pure な最小のものを返す。"""
    t1 = (-pow(4, -1, k)) % k          # Type I target
    p = h
    while p < lim:
        if isprime(p) and p % 4 == 1:
            C = (p + k) // 4
            f = factorint(C)
            S = {1}                     # C^2 の約数の mod k 剰余集合 (exact box)
            for q, e in f.items():
                S = {(a * q ** i) % k for a in S for i in range(2 * e + 1)}
            miss = t1 not in S and (-C) % k not in S
            pure = all(J(q, k) == 1 for q in f)   # jacobi(q,k) = (p/q)
            if miss and not pure:
                return p, C, dict(f)
        p += 840
    return None


def main():
    lo = int(sys.argv[1]) if len(sys.argv) > 1 else 19
    hi = int(sys.argv[2]) if len(sys.argv) > 2 else 403
    lim = int(float(sys.argv[3])) if len(sys.argv) > 3 else 2 * 10 ** 7
    missing, worst = [], (0, None)
    for k in range(lo + (3 - lo) % 4, hi + 1, 4):   # k = 3 (mod 4)
        for h in HARD:
            r = witness(k, h, lim)
            if r is None:
                missing.append((k, h))
                print(f"k={k:4d} h={h:3d}  NO WITNESS below {lim}")
                continue
            p, C, f = r
            if p > worst[0]:
                worst = (p, (k, h))
            print(f"k={k:4d} h={h:3d}  p={p:9d}  C={C} = {f}")
    print(f"\nno witness: {len(missing)} {missing}")
    print(f"largest minimal witness: p={worst[0]} at (k,h)={worst[1]}")


if __name__ == "__main__":
    main()
