#!/usr/bin/env python3
"""「⟨seed⟩ ⊇ ker χ が annihilation の必要条件」の構成的検証。

(k,h) ごとに H = ⟨seed⟩ (seed = gcd(210, (h+k)/4) の素因子の mod k 剰余が生成する群),
Q = ker χ (χ = jacobi(·,k)), fiber F = {x ∈ (Z/k)^× : x ≡ (h+k)/4 (mod gcd(210,k))} を作り、
H ⊉ Q のとき次の構成で「非 pure な miss state」を探す。

  E1 : S = H ∪ rH ∪ r²H,        c = h0·r  (r NR, h0 ∈ H)
       miss ⇔ r ∉ (-H) ∪ (-(1/4)H),   fiber ⇔ r ∈ H·F
  E2i: S = H ∪ r^{±1}H ∪ r^{±2}H, c = h0     (r' = r^{-1}h)
       miss ⇔ r ∉ (-H) ∪ (-(1/4)H) ∪ (-4H), fiber ⇔ F ∩ H ≠ ∅
  E2g: S = H·{1,r,r²}·{1,r',r'²},  c = h0·r·r' ∈ F  (r,r' NR 任意) を総当たり

これらは closure (code/closure.cpp) の到達状態なので、見つかれば (k,h) は
range-free に annihilate しない。出力は各構成での cover 数と、cover できない組。

  python3 code/seed_necessity.py        # k ≤ 403
  python3 code/seed_necessity.py 135
"""
import sys
from math import gcd
from sympy import jacobi_symbol as J, factorint

HARD = [1, 121, 169, 289, 361, 529]


def gen(k, gs):
    S = {1}
    while True:
        T = {(a * g) % k for a in S for g in gs} | S
        if T == S:
            return S
        S = T


def main():
    KMAX = int(sys.argv[1]) if len(sys.argv) > 1 else 403
    cover = {'H⊇Q': 0, 'E1': 0, 'E2i': 0, 'E2g': 0, 'none': 0}
    prop = {'coprime idx>=3': 0, 'coprime idx2 4∈H': 0, 'coprime idx2 4∉H': 0, 'gcd(k,210)>1': 0}
    unc = []
    for k in range(3, KMAX + 1, 4):
        U = [x for x in range(1, k) if gcd(x, k) == 1]
        Q = {x for x in U if J(x, k) == 1}
        NR = [x for x in U if x not in Q]
        inv4 = pow(4, -1, k)
        t1 = (-inv4) % k
        for h in HARD:
            seed = gcd(210, (h + k) // 4)
            sp = [q % k for q in factorint(seed)] if seed > 1 else []
            H = gen(k, sp) if sp else {1}
            if H >= Q:
                cover['H⊇Q'] += 1
                continue
            idx = len(Q) // len(H)
            if gcd(k, 210) == 1:
                key = 'coprime idx>=3' if idx >= 3 else ('coprime idx2 4∈H' if 4 % k in H else 'coprime idx2 4∉H')
            else:
                key = 'gcd(k,210)>1'
            prop[key] += 1
            g = gcd(210, k)
            c0 = ((h + k) // 4) % g
            F = {x for x in U if x % g == c0}
            forb1 = {(-x) % k for x in H} | {(-inv4 * x) % k for x in H}
            HF = {(a * b) % k for a in H for b in F}
            if any(r not in forb1 and r in HF for r in NR):
                cover['E1'] += 1
                continue
            forb2 = forb1 | {(-4 * x) % k for x in H}
            if (F & H) and any(r not in forb2 for r in NR):
                cover['E2i'] += 1
                continue
            found = False
            for r1 in NR:
                for r2 in NR:
                    if r2 < r1:
                        continue
                    S = {(a * b * d) % k for a in H for b in (1, r1, r1 * r1 % k) for d in (1, r2, r2 * r2 % k)}
                    if t1 in S:
                        continue
                    for h0 in H:
                        c = h0 * r1 * r2 % k
                        if c in F and (-c) % k not in S:
                            found = True
                            break
                    if found:
                        break
                if found:
                    break
            if found:
                cover['E2g'] += 1
            else:
                cover['none'] += 1
                unc.append((k, h))
    print(f"k ≤ {KMAX}: coverage of (k,h) pairs:", cover)
    print("pairs with H ⊉ Q, by proposition case:", prop)
    print("uncovered:", unc)


if __name__ == '__main__':
    main()
