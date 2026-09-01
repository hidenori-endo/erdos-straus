# 再現コード

`updates/` と `topics/07` の数値のうち、character annihilation atlas に関わるものを
再現するための 2 本。既存の会話由来の数値と違い、ここに書かれた値は本リポジトリで
実行して得たものである。

~~~sh
g++ -O2 -std=c++20 closure.cpp -o closure
g++ -O2 -std=c++20 audit.cpp   -o audit
~~~

## `audit.cpp` — 実素数による ground truth

モデルを一切使わない。hard prime `p`（`p ≡ 1 mod 4` かつ `p mod 840 ∈
{1,121,169,289,361,529}`）ごとに `C_k=(p+k)/4` を素因数分解し、**全約数の
`mod k` 剰余**を作って

- Type I target `t₁ = -1/4 (mod k)`
- Type II target `t₂ = -C_k (mod k)`

を踏むかどうかを直接判定する。同時に「`C_k` の全素因子が p-QR か」(pure) を判定し、
hard class ごとに `exact miss` / `pure miss` と両方向の食い違いを数える。

~~~sh
./audit 100000000 3 7 11 15      # 上限 p、続けて shift k を並べる
~~~

## `closure.cpp` — 有限群上の閉包（range-free）

状態 `(S, c, neg)` を BFS で閉じる。`S` は約数の `mod k` 剰余集合、`c` は center、
`neg` は「p-NR の素因子を使ったか」。遷移は素因子 1 個の消費に対応する

~~~
S -> S ∪ rS,   c -> c·r,   neg -> neg ∨ [χ(r) = -1]
~~~

で、これを繰り返すことで任意の指数が作れる。したがって実在する全ての約数集合が
到達可能であり、閉包は現実の over-approximation になる。center は
`p ≡ h (mod 840)` が許す exact fiber に限定する。

~~~sh
ALLK=1 NOPRUNE=1 ./closure 15    # k ≤ 15、素数 k も含め、完全閉包
FAST=1 ./closure 300             # k ≤ 300、最初の non-pure miss で打ち切り
./closure --selftest             # χ(r) = jacobi(r,k) の補題を実素数で検証
~~~

出力の `annihilates=YES` は「center fiber に到達する miss state が全て pure」、
`pureHIT=0` は逆向き「pure なら必ず miss」を意味する。両方が立つとき、その
`(k,h)` で `miss ⇔ C_k の全素因子が p-QR` が range-free な同値になる。

## 遷移を間違えないこと

遷移は `S → S ∪ rS` でなければならない。初期の実装は `S → S ∪ rS ∪ r²S` を
使っていたが、これは指数 1 の素因子に対して**実在しない約数 `r²` を混ぜる**。
状態が過大になり、本当は target を外している配置を hit と誤判定するため、
**偽の annihilation** が出る。`k=35` の class 121/361 が annihilate して見えたのは
これが原因だった。詳細は
[2026-09-01 closure 訂正](../updates/2026-09-01-closure-correction.md)。

## `witness.py`

`k ≥ 19` で同値が壊れることを、閉包モデルを使わずに実素数の反例で示す。

```sh
python3 code/witness.py           # k = 19..403 × 6 class、上限 p < 2e7（数十分）
python3 code/witness.py 19 63 1e6 # 短時間で試す
```

sympy が必要。既知の結果は「582 組すべてに witness があり、最大の最小 witness は
`p = 66,529`（`k=35, h=169`）」。
