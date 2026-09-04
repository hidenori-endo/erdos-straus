# 2026-09-04: quotient transport route の検証結果と最小 hit shift

[2026-09-04 adaptive external-NR factor forcing](2026-09-04-adaptive-nr-factor-forcing.md) §5 が
挙げた二つの次問題のうち、後者

> whether miss states can be transported between induced shifts in a quotient where
> persistence is impossible

を測定で検証した。**結論は否定的**である。輸送すべき invariant は存在しない。
同じ検証の副産物として、exact box の最小 hit shift という、より扱いやすい量が得られた。

再現コード: `code/survivor_nr.cpp`, `code/transport_test.cpp`, `code/residual_corr.cpp`,
`code/min_hit_k.cpp`。

## 1. 反例条件の言い換え（証明済み部分のみから従う）

atlas 30 組では `miss ⇔ C_k の全素因子が p-QR (pure)` が証明済みの同値である
（[07. character annihilation atlas](../topics/07-character-annihilation-atlas.md)）。
反例は全 shift で miss するので、atlas shift でも miss、したがって pure。
`j := (k-3)/4`、`C_k = N + j`、`N = (p+3)/4` と書くと:

> **補題 1.** hard prime `p ≡ h (mod 840)` が Erdős–Straus の反例なら、`j ∈ J_h` の全てで
> `N + j` は pure（全素因子が p-QR）である。
>
> | `h` | `J_h` | 対応する atlas shift |
> |---:|---|---|
> | 1 | 0, 1, 3 | 3, 7, 15 |
> | 121 | 0, 1, 3, 4, 8, 11 | 3, 7, 15, 19, 35, 47 |
> | 169 | 0, 1, 2, 3, 7 | 3, 7, 11, 15, 31 |
> | 289 | 0, 1, 2, 3, 7, 11 | 3, 7, 11, 15, 31, 47 |
> | 361 | 0, 1, 3, 8, 14 | 3, 7, 15, 35, 59 |
> | 529 | 0, 1, 2, 3, 7 | 3, 7, 11, 15, 31 |

> **系 1.1.** 反例 `p` では、`(r/p) = -1` なる全ての素数 `r` について
> `N mod r ∉ { -j : j ∈ J_h }`。つまり NR 素数は `N+j (j ∈ J_h)` のどれも割らない。

> **系 1.2.** external-NR induced shift は atlas shift と決して一致しない。
> `r | C_{k_r}` かつ `χ_{k_r}(r) = -1` なので `C_{k_r}` は非 pure、一方 atlas shift の
> miss は pure を強制するからである。

系 1.2 は「external-NR route と atlas が本当に別物である」ことの構造的な理由であり、
両者を単純に足し合わせても新しい shift は増えないことを意味する。

補題 1 の条件を `p < 10^8` の hard prime 179,468 個に課すと survivor は
`h=1: 4810 / 121: 316 / 169: 447 / 289: 130 / 361: 1223 / 529: 526`、計 **7,452**。
[09-03 の cross-shift 集計](2026-09-03-global-local-classification-and-next-bottleneck.md)
と完全に一致する（`code/survivor_nr.cpp`、独立実装）。

## 2. exact box での external-NR: first-hit rank 17 → 7

09-04 の known-factor box `Div(s²){1,r,r²}{1,m,m²}` を exact box `Div(C_{k_r}²)` に
置き換えて、survivor 7,452 個の全てで NR rank を昇順に走らせた（`code/survivor_nr.cpp`）。

| first-hit NR rank | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 未 hit |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| survivor 数 | 6700 | 619 | 94 | 20 | 11 | 5 | 2 | 1 | 0 |

known-factor box での最大 rank 17 が **7** に下がる。`C_{k_r}` の素因数分解を要する代わりに
証拠が短くなる、という交換である。

## 3. 輸送 route の検証（本題）: 依存は残らない

survivor 7,452 個 × NR rank 0..31 の miss/hit を記録し、二段階で相関を測った
（`code/residual_corr.cpp`）。

**(a) 生の同時 miss 相関** `joint/(m_i m_j/n)`（1.0 = 独立）は、rank 0-1 の 1.28 を最大に、
それ以外は全て 0.98–1.19。rank が離れると 1.00 に張り付く。

**(b) 残差相関.** 各 `(p, rank)` の miss 確率を `(k, d(C_k²))` の 2 次元ビンで較正し、
残差 `miss - q(k,d)` の相関を取ると、**全ペアで 0.00–0.04**。

```text
# (k,d) 較正後の残差相関 (rank 0..11)
  0  1.00  0.02  0.03  0.02  0.02  0.01  0.01  0.01  0.01  0.02  0.01  0.00
  1  0.02  1.00  0.03  0.03  0.01  0.02 -0.00  0.01 -0.01  0.04 -0.01 -0.00
  ...
 11  0.00 -0.00  0.02  0.00 -0.01  0.02  0.04  0.02  0.02  0.03 -0.00  1.00
```

**(c) 較正モデルの予測精度.** 「最初の 12 rank が全て miss」の件数は独立モデル予測
**0.01 件**、実測 **0 件**。

つまり induced shift 間の miss の同時構造は、`k_r` の大きさと `d(C_{k_r}²)` の
2 変数だけで説明し尽くされ、**shift から shift へ運ばれる状態は残っていない**。

> **判定.** quotient transport / persistence-impossible route は棄却する。
> ある shift での miss は次の shift の miss について（divisor 数を通じた間接的な相関を
> 除き）何の情報も持たない。輸送すべき invariant が無いので、「persistence が不可能な
> 商を作る」という形の論法は原理的に立たない。
> [rejected/quotient-transport-persistence](../hypotheses/rejected/quotient-transport-persistence.md)。

## 4. 代わりに効いている量: `d(C_k²) / k`

同じ走査で、rank ごとの hit 率を素朴な等分布モデル `2 d(C_k²) / k` と比べた
（`code/transport_test.cpp`、survivor 2,321 個、`p < 2.5·10^7`）。

| rank | mean `k` | mean `d(C²)` | hit 率 | `2d/k` | 比 |
|---:|---:|---:|---:|---:|---:|
| 0 | 34 | 169 | 0.890 | 10.04 | 0.09 |
| 8 | 167 | 153 | 0.570 | 1.84 | 0.31 |
| 24 | 498 | 131 | 0.315 | 0.52 | 0.60 |
| 47 | 1067 | 117 | 0.197 | 0.22 | 0.90 |
| 63 | 1464 | 107 | 0.147 | 0.15 | 1.00 |

`k` が大きくなると hit 率は等分布モデルにぴったり収束する。逆に小さい `k` では比が
0.09 まで落ちる、つまり箱は `ker χ` に強く偏っていて、等分布モデルより **hit しにくい**。
それでも小さい `k` の方が hit 率の絶対値は圧倒的に高い（`2d/k` が大きいため）。

rank 0..63 の hit 率の総和は 21.3 で、rank を倍にするごとに約 5.8 増える。すなわち
「external NR 素数を並べたときの期待 hit 回数」は rank について対数的に発散する。
反例が存在するには `d(C_{k_r}²)` が全ての `r` で同時に小さい必要があり、これは
`[N, N+R)` の区間の乗法的構造に関する主張である。輸送ではなく **数え上げ**の問題に
なった、というのが 3 節の判定の裏返しである。

## 5. 副産物: exact box の最小 hit shift

hit 率が小さい `k` に集中している以上、`k` を昇順に総当たりするのが最も効率が良い。
反例でない hard prime は補題 1 により atlas shift（`k ≤ 59`）で hit するので、
「最小 hit shift」の最大値は survivor 上で達成される。`code/min_hit_k.cpp` で
`p < 10^9` の全 hard prime を走査した（survivor 51,625、未解決 0）。

| 最小 hit `k` | 11 | 19 | 23 | 27 | 31 | 35 | 39 | 43 | 47 | 51 | 55 | 59 | 63 | 67 | 71 | 75 | 79 | 83 | 107 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| survivor 数 | 26886 | 13343 | 7622 | 1464 | 905 | 378 | 538 | 142 | 205 | 34 | 46 | 38 | 10 | 2 | 6 | 2 | 1 | 2 | 1 |

> **`p < 10^9` の全ての hard prime は `k ≤ 107` の shift で hit する。**
> 最大値 107 は `p = 8,803,369`（`h=169`、`C_107 = 3²·11²·43·47`、Type II）ただ 1 個で、
> それ以外は全て `k ≤ 83`、99.6% が `k ≤ 23`。

decade 別の最大値は `10^3`→23, `10^4`→31, `10^5`→59, `10^6`→107, `10^7`→63, `10^8`→83
で、`10^6` 台の 107 を超えていない。

独立検証として `p = 8,803,369`, `k = 107` の hit から解を復元すると

```text
4/8803369 = 1/2200869 + 1/181085300330 + 1/3293760527702370
```

で厳密に一致する（`code/box_check.py` の `reconstruct`）。

この量は
[external shift log-squared conjecture](../hypotheses/live/external-shift-log-squared-conjecture.md)
（`q ≲ (log p)^2`、`p<10^8` の最大 `q*=251`）の、shift を external prime に限らない版で、
`min hit k ≤ 107` は `(log 10^9)^2 ≈ 430` に対してかなり余裕がある。
[live/min-hit-shift-bound](../hypotheses/live/min-hit-shift-bound.md) に conjecture として置く。

## 6. 次の一手

3 節で輸送が消えたので、残る route は 2 つに絞られる。

1. **数え上げ route（推奨）**: 「`d((N+j)²)` が `j = 0..K` の全てで小さい」ことの
   不可能性を、`k ≤ K` の shift に対する `Div(C_k²) mod k` の分布評価として示す。
   必要なのは「与えられた剰余類に約数を持つ」型の主張で、算術級数中の約数分布
   （Erdős–Hooley Δ, divisors in APs）の領域に入る。5 節の `K = 107` は
   その主張が要求する `K` の実測上界を与える。
2. **least-NR 解析 route**: 09-04 note §3 の `p > 4r² - r` を `C ≥ r^E` 型の
   defect 定理へ拡張し、least NR の上界と組み合わせる。外部入力（無条件の
   least-NR bound）に依存する。

いずれも finite sieve では閉じない（parity barrier）点は
[09-03 の bottleneck](2026-09-03-global-local-classification-and-next-bottleneck.md)
と変わらない。変わったのは、**非 sieve な最終論法が満たすべき形が「輸送」ではなく
「区間 `[N, N+K]` の約数の剰余分布」に確定した**ことである。
