# 再現コード

`updates/` と `topics/07` の数値のうち、character annihilation atlas に関わるものを
再現するための 13 本。既存の会話由来の数値と違い、ここに書かれた値は本リポジトリで
実行して得たものである。

~~~sh
g++ -O2 -std=c++20 closure.cpp -o closure
g++ -O2 -std=c++20 audit.cpp   -o audit
~~~

## 箱の定義（2026-09-03 に訂正）

shift `k ≡ 3 (mod 4)`、`C_k = (p+k)/4` に対し、`p` で割れない分母 `x = C_k` を固定して
残り 2 項 `1/y + 1/z = k/(pC_k)` を解くと

~~~
Type II (p|y, p|z):  (ky'-C)(kz'-C) = C²,    D = ky'-C     | C²,  D ≡ -C   (mod k)
Type I  (p|y, p∤z):  (ky'-C)(kz-pC) = pC²,   D = (ky'-C)/p | C²,  D ≡ -1/4 (mod k)
~~~

となる。従って正しい箱は **`C_k²` の約数**（素因子ごとに指数 `0..2e`）の `mod k`
剰余集合である。任意の ES 解はどれかの `k` でこの形に落ち、逆に箱の hit から解が復元
できる。`box_check.py` はこれを `p<700` の全素数・全解の総当たりで確認する。

2026-09-01 の訂正はこれを `C_k` の約数（指数 `0..e`）に置き換えていた。これは真の箱の
**部分箱**で、hit を取りこぼす。部分箱の miss は実際には hit であることがあり
（例: `p=21121, k=35`）、それが `k=35` の偽の「反例」を生んだ。詳細は
[2026-09-03 box 訂正](../updates/2026-09-03-box-correction.md)。

## `audit.cpp` — 実素数による ground truth

モデルを一切使わない。hard prime `p`（`p ≡ 1 mod 4` かつ `p mod 840 ∈
{1,121,169,289,361,529}`）ごとに `C_k` を素因数分解し、旧部分箱（`C_k` の約数）と
正しい箱（`C_k²` の約数）の両方で

- Type I target `t₁ = -1/4 (mod k)`
- Type II target `t₂ = -C_k (mod k)`

を踏むかどうかを判定する。同時に「`C_k` の全素因子が p-QR か」(pure) を判定し、
hard class ごとに `subMiss` / `fullMiss` / `pure`、両方向の食い違い、
`subMiss かつ fullHit` の件数、正しい箱で「miss かつ非 pure」な最小 witness を出す。

~~~sh
./audit 100000000 3 7 11 15 35   # 上限 p、続けて shift k を並べる
./audit 2000000                  # k を省略すると k ≤ 403 の全 shift
~~~

## `closure.cpp` — 有限群上の閉包（range-free）

状態 `(S, c, neg)` を BFS で閉じる。`S` は `C_k²` の約数の `mod k` 剰余集合、`c` は
center、`neg` は「p-NR の素因子を使ったか」。素因子 `r` を 1 個消費すると `C_k²` での
指数は 2 増えるので、遷移は

~~~
S -> S ∪ rS ∪ r²S,   c -> c·r,   neg -> neg ∨ [χ(r) = -1]
~~~

で、これを繰り返すことで任意の指数が作れる。したがって実在する全ての約数集合が
到達可能であり、閉包は現実の over-approximation になる。center は
`p ≡ h (mod 840)` が許す exact fiber に限定する。

~~~sh
ALLK=1 NOPRUNE=1 ./closure 15    # k ≤ 15、素数 k も含め、完全閉包
ALLK=1 FAST=1 ./closure 403      # k ≤ 403、最初の non-pure miss で打ち切り
ALLK=1 KMIN=71 ./closure 71      # k=71 だけ
SUBBOX=1 ALLK=1 ./closure 35     # 旧部分箱モデル（比較用）
./closure --selftest             # χ(r) = jacobi(r,k) の補題を実素数で検証
~~~

出力の `annihilates=YES` は「center fiber に到達する miss state が全て pure」、
`pureHIT=0` は逆向き「pure なら必ず miss」を意味する。両方が立つとき、その
`(k,h)` で `miss ⇔ C_k の全素因子が p-QR` が range-free な同値になる。

## `witness.py`

正しい箱で「miss かつ非 pure」な実素数を、閉包モデルを使わずに構成する。

```sh
python3 code/witness.py           # k = 19..403 × 6 class、上限 p < 2e7（数十分）
python3 code/witness.py 19 63 1e6 # 短時間で試す
```

sympy が必要。`k ≥ 19` で witness が無いのは 9 組
（`(19,121) (31,169) (31,289) (31,529) (35,121) (35,361) (47,121) (47,289) (59,361)`）。
`(71,289)` は `p = 3,098,209` に witness があり、上限 `2·10^6` では見落とすので注意。

## `box_check.py`

`p<700`（引数で変更可）の全素数 `p ≡ 1 (mod 4)` について 4/p の全解を総当たりし、

- 全ての解が、`p` で割れない分母 `x` に対する `k = 4x-p` で `Div(C_k²)` の target を踏む
- 逆に `Div(C_k²)` の hit から復元した `(x,y,z)` が総当たり解集合に含まれる
- `Div(C_k)` 部分箱では miss だが `Div(C_k²)` では hit の `(p,k)` が存在する（266 組）

を assert で確認する。

## `even_e_cases.py`

center 固定 shift `k ∈ {3,7,15,35}` で、E=2 帰着の有限検査により「非 pure ⇒ hit」を
閉包モデル非依存に証明する。失敗 class では miss 組 `(r₁,r₂,m)` を列挙する。

```sh
python3 code/even_e_cases.py        # k = 3, 7, 15, 35
python3 code/even_e_cases.py 35
```

## `seed_necessity.py`

`⟨seed⟩ ⊉ ker χ` の各 `(k,h)` に対し、E1 / E2 の subgroup 構成で閉包の非 pure miss state を
作れるかを検査する。`k ≤ 403` では 217 組すべてが cover される（1.5 秒）。

```sh
python3 code/seed_necessity.py 403
```

## 2026-09-03/04 添付コード

添付された完全な検証コードは次の通り。出力は再現用の有限計算であり、証明そのものではない。

- `seed_necessity_fast.cpp`: E1/E2i/E2g による seed 必要性の高速検証
- `cross_shift_scan.cpp`: 30 組の pure 条件を同一 prime に課す cross-shift 集計
- `adaptive_cover.cpp`: base shift 後の greedy adaptive cover
- `nr_adaptive.cpp`: external-NR prime 一個ずつの induced shift 検査
- `nr_group_adaptive.cpp`: 同一 induced shift の NR factor を束ねる検査
- `nr_adaptive_sample.cpp`: 全 hard class の大きい p の乱択 stress test
- `combined_cycle_scan.cpp`: exact two-target box を入れた external cycle の反証確認

例:

```sh
g++ -O2 -std=c++20 code/seed_necessity_fast.cpp -o /tmp/seed_necessity_fast
/tmp/seed_necessity_fast 403
g++ -O2 -std=c++20 code/nr_adaptive.cpp -o /tmp/nr_adaptive
/tmp/nr_adaptive 100000000 1000
```

`intermediate_fiber_global.cpp` と `quotient_necessity_proof.py` は指定会話の添付が途中で
終わっており、完全なプログラムではないため runnable code としては追加していない。結果の
論理は `updates/2026-09-03-intermediate-fiber-global.md` と
`updates/2026-09-03-seed-kernel-global-proof.md` に整理した。

## 2026-09-04 輸送 route 検証コード

[transport verdict](../updates/2026-09-04-transport-verdict-and-min-hit-shift.md) の
数値を再現する 4 本。いずれも exact box `Div(C_k²)` を使い、`(p+3)/4` までの
smallest-prime-factor 篩で `C_k` を分解する。

- `survivor_nr.cpp`: atlas の pure 条件（補題 1）で survivor を絞り、external-NR
  induced shift を全 rank 走らせて first-hit rank と miss 構造を出す。
- `transport_test.cpp`: rank ごとの hit 率を等分布モデル `2 d(C_k²)/k` と比較し、
  生の miss 相関行列を出す。
- `residual_corr.cpp`: `(k, d(C_k²))` の 2 次元ビンで miss 確率を較正し、残差相関と
  独立モデルの予測精度を出す。**輸送 route の棄却根拠**。
- `min_hit_k.cpp`: survivor の最小 hit shift `minK(p)` を全数で求める。

~~~sh
g++ -O2 -std=c++20 code/survivor_nr.cpp   -o /tmp/survivor_nr   && /tmp/survivor_nr   100000000 5000 60
g++ -O2 -std=c++20 code/transport_test.cpp -o /tmp/transport_test && /tmp/transport_test 25000000 20000 64
g++ -O2 -std=c++20 code/residual_corr.cpp  -o /tmp/residual_corr  && /tmp/residual_corr  100000000 20000 32
g++ -O2 -std=c++20 code/min_hit_k.cpp      -o /tmp/min_hit_k      && /tmp/min_hit_k      1000000000 4003
~~~

`min_hit_k 1000000000` は SPF 篩に約 1GB、実行 1 分。survivor 51,625 / 未解決 0 /
`max minK = 107` (`p = 8,803,369`) を出す。`survivor_nr 100000000` の class 別
survivor 数は 09-03 の cross-shift 集計 (4810/316/447/130/1223/526) と一致する。

## 2026-09-04 証拠複雑度コード

[certificate complexity](../updates/2026-09-04-certificate-complexity.md) の 3 本。
`d(e) = ∏ q^⌈a_q/2⌉` は `e | C_k²` が target を踏むときに必要な `C_k` の最小約数で、
`(k, d, e)` を固定すると条件が `p` の合同式（＝古典的恒等式）になる。

- `cert_size.cpp`: `k ≤ KMAX` 固定での最小証拠約数 `dmin(p)` の分布。
- `cert_complexity.cpp`: `cert(p) = min_k max(k, d(e))`。`k` 昇順で `k ≥ best` 打ち切り。
- `tradeoff.cpp`: 約数予算 `D` に対する必要 shift `k_D(p)` のトレードオフ表。

~~~sh
g++ -O2 -std=c++20 code/cert_size.cpp       -o /tmp/cert_size       && /tmp/cert_size       100000000 107
g++ -O2 -std=c++20 code/cert_complexity.cpp -o /tmp/cert_complexity && /tmp/cert_complexity 1000000000
g++ -O2 -std=c++20 code/tradeoff.cpp        -o /tmp/tradeoff        && /tmp/tradeoff        100000000 4003
~~~

`cert_complexity 1000000000` は約 75 秒で hard 1,587,581 / 最大 cert 395 / 幾何平均 17.2。
`tradeoff` の `D=1` 行は「`p+4` が `3 (mod 4)` の素因子を持つか」と一致する（補題 2）。

## 2026-09-04 層の同定コード

[層の同定](../updates/2026-09-04-layer-identification.md) の 3 本。定理 3
「層 `(d,e)` は `n=p+4e` が `k ≡ -n (mod 4d)` なる約数を持つことと同値」を扱う。

- `layers.cpp`: 定理 3 の判定と `Div(C_k^2)` 総当たりの突き合わせ（`d ≤ DMAX`）。
- `fast_layers.cpp`: 定理 3 だけを使った予算 `D` の未被覆密度。区間指定可。
- `failchar.cpp`: 「失敗 ⟺ `-n ∉ ⟨素因子 mod 4d⟩`」が成り立つ `d` の判定。
- `exponent2_layers.cpp`: 指数 2 の法に属する **9 層**をまとめて検査し、exact な
  共通失敗率、prime-atom sieve の上界集合、局所 sieve 次元 `2`（素数条件込みで `3`）
  を再現する。さらに odd character による exact miss の分離を全列挙し、4096 character
  assignment、exact 層の次元 `9/2`（素数条件込みで `11/2`）を確認する。

~~~sh
g++ -O2 -std=c++20 code/layers.cpp      -o /tmp/layers      && /tmp/layers      3000000 8 20003
g++ -O2 -std=c++20 code/fast_layers.cpp -o /tmp/fast_layers && /tmp/fast_layers 10000000 100000000 32
g++ -O2 -std=c++20 code/failchar.cpp    -o /tmp/failchar    && /tmp/failchar    10000000
g++ -O2 -std=c++20 code/exponent2_layers.cpp -o /tmp/exponent2_layers && /tmp/exponent2_layers 10000000 100000000
~~~

`layers 3000000 8 20003` の mismatch 4 件は総当たり側の `k` 打ち切りによるもので、
定理側が正しい（`k` = 20751, 54311, 30999, 34647）。`failchar` は `d ∈ {1,2,3,6}` で
不一致 0、`d ∈ {4,5,7,8}` で不一致あり ―― `(Z/4d)^*` の指数が 2 かどうかで分かれる。

## 教訓（2026-09-01 の訂正が逆だった）

09-01 の訂正は「`r²` は指数 1 の素因子に対して実在しない約数」として `r²` 遷移を
外したが、箱が `C_k²` の約数である以上、指数 1 の素因子 `r` に対しても `r²` は実在する
約数である。モデルの「訂正」は、モデルが近似している対象の定義（ここでは ES 解との
対応）まで遡って確認しなければならない。閉包モデルと実素数監査が一致しても、両方が
同じ誤った箱を使っていれば mismatch 0 は自動的に出る。
