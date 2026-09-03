# 07. Character annihilation atlas

## 目的

shift `k ≡ 3 (mod 4)` と hard class `h = p mod 840` を固定したとき、
`C_k = (p+k)/4` の素因子の quadratic character だけで、その shift が
Type I / Type II target を逃すかどうかが決まるかを判定する。

判定は 2 通りで行い、両者を突き合わせる。

- **実素数監査**: `C_k` を実際に素因数分解し、`C_k²` の全約数の `mod k` 剰余を作って
  target を踏むか直接見る。モデルを使わない ground truth。
- **有限閉包**: 状態 `(S, c, neg)` を有限群上で BFS 閉包する。range-free だが
  モデル依存。

## 箱の定義（2026-09-03 訂正）

正しい箱は **`C_k²` の約数**の `mod k` 剰余集合である
（[02. exact reformulation](02_exact-reformulation.md)、
[2026-09-03 箱の訂正](../updates/2026-09-03-box-correction.md) §2）。
`Div(C_k)` は部分箱で、hit を取りこぼす。2026-09-01 の訂正はこの部分箱を「正しい」
としていたため、以下の atlas は 09-03 に再構成した。

## 記号

- Type I target `t₁ = -1/4 (mod k)`、Type II target `t₂ = -C_k (mod k)`。
- character `χ(r) = jacobi(r,k)`。`r | C_k` なら `p ≡ -k (mod r)` と
  `k ≡ 3 (mod 4)` から `χ(r) = (p/r)` が従う（`r=2` も Kronecker 記号で同じ）。
- **pure** = `C_k` の全素因子が p-QR、すなわち `χ = +1`。
- **seed** = `gcd(210, C_k)`。class `h` だけで決まる mandatory factor。

## 定理: QR support は miss に十分

`k ≡ 3 (mod 4)` なので `χ(-1) = -1`、また `jacobi(4,k) = +1` なので
`χ(t₁) = χ(-1) = -1`。pure なら `c = C_k mod k ∈ ker χ` なので
`χ(t₂) = χ(-1)χ(c) = -1`。一方 pure なら `C_k²` の全約数も QR 因子の積なので
`S ⊆ ker χ`。よって `t₁, t₂ ∉ S`、すなわち miss。

~~~
C_k の全素因子が p-QR  ⇒  shift k は miss
~~~

対偶は「shift k が hit するなら `C_k` は p-NR 素因子を持つ」。`p<10^8` の hard prime
179,468 個 × `k ∈ {3,7,11,15,19,31,35,47,59,71}` で「pure かつ hit」は 0。

## 逆向きが成り立つ `(k,h)`: 30 組

逆向き（miss ⇒ pure）は shift と class に強く依存する。`k ≤ 403` の
101 shift × 6 class = 606 組のうち、成立するのは **30 組**。

| `k` | 成立する `h` | seed |
|---:|---|---|
| 3 | 全 6 class | 1 / 7 |
| 7 | 全 6 class | 2 |
| 11 | 169, 289, 529 | 15 |
| 15 | 全 6 class | 2 |
| 19 | 121 | 35 |
| 31 | 169, 289, 529 | 10, 10, 70 |
| 35 | 121, 361 | 3 |
| 47 | 121, 289 | 42 |
| 59 | 361 | 105 |
| ≥ 63 | なし | |

この 30 組では

~~~
shift k が miss  ⇔  C_k の全素因子が p-QR
~~~

が両方向の同値になる。`p < 10^8` の hard prime で mismatch 0、かつ `r²` 遷移の
有限閉包で range-free に `annihilates=YES`、`pureHIT=0`。

`(71,289)` は `p < 2·10^6` では成立して見えるが `p = 3,098,209`
（`C_71 = 2·3·5·25819`）が「miss かつ非 pure」で、閉包でも non-pure miss 5 状態が残る。
小さい上限で成立を判定してはいけない例。

## `k=15` の証明証拠

完全閉包は 19 状態で閉じ、center fiber に到達する miss は class ごとに 1 状態、
その約数剰余集合は `S ⊆ {1,2,4,8} = ker χ`。`non-pure miss = 0` と
`pure かつ hit = 0` が同時に立つ。`p<10^8` の監査値は 179,468 / 98,684 / 98,684 / 0 で、
部分箱でも同じ値になる（`k=15` では箱の違いが出ない）。

## `k=35` は class 121, 361 で成立（09-01 の「反証」を撤回）

reachable 394 状態、class 121 の miss 2 状態、class 361 の miss 3 状態が全て pure。
`p<10^8` では class 121 が 29,900 / 18,080 / 18,080 / 0、class 361 が
29,828 / 18,069 / 18,069 / 0。09-01 addendum §3 の先行報告と一致する。

09-01 が反例とした `p=21121`（`C_35 = 3·41·43`）は、部分箱 `Div(C_35)` では
`{1,3,4,6,8,13,18,24}` が `26,31` を避けるが、真の箱には
`3²·41·43² ≡ 26 = t₁` があり Type I の hit。詳細は
[k=35 pure-support 定理](../hypotheses/live/k35-pure-support-theorem.md)。

他の 4 class は真の箱でも不成立で、最小 witness は `h=1`: 26,041（`3·41·53`）、
`169`: 66,529（`3²·43²`）、`289`: 12,049（`3·19·53`）、`529`: 18,169（`3·37·41`）。

## `k=11` の class 分割は seed で決まる

`k=11` は `840` を割らないので center fiber は `Z/11Z` 全体であり、class 差は
mandatory seed だけから来る。`h=169,289,529` では `15 | C_11`、
`h=1,121,361` では `3 | C_11` のみ。前者では

~~~
15 | C_11 かつ C_11 が p-NR 素因子を持つ ⇒ shift 11 は hit
~~~

が初等的に証明できる。後者では `C_11 = 3·r`（`r ≡ 2 mod 11`）の実素数反例があり、
真の箱でも miss（`h=361` の最小反例は `p = 1,201`、`C_11 = 3·101`）。詳細は
[k=11 の seed 15 補題](../hypotheses/live/k11-seed15-lemma.md)。

## `k ≥ 19` で成立する 9 組と不成立の 573 組

`k = 19, …, 403` の 582 組のうち、9 組（表の `k=19,31,35,47,59`）を除く 573 組には
`p < 10^8` に「miss かつ非 pure」の実素数がある（`code/witness.py`、`code/audit.cpp`）。
最大の最小 witness は `(71,289)` の `p = 3,098,209`、それ以外は全て `p < 10^6`。

`k=19, h=121` は 09-01 addendum §2 の「class 121 での q=19 saturation」そのもので、
seed `5·7` が `Q_19` を生成することから初等的に従う。

## center 固定 shift（`k=3,7,15,35`）は有限検査で証明済み

hard prime では `χ(C_k) = jacobi(p,k) = +1` なので p-NR 因子の個数は偶数。非 pure なら
NR 剰余 `r₁,r₂` と残り `m` について箱は `Div(seed²){1,r₁,r₁²}{1,r₂,r₂²}{1,m,m²}` を
含むので、全 `(r₁,r₂)` の有限検査で「非 pure ⇒ hit」が示せる。`k=3,7,15` の全 class と
`k=35` の `h=121,361` は missing 0（`code/even_e_cases.py`）。閉包モデル非依存の証明である
（[seed 必要条件](../updates/2026-09-03-seed-necessity-and-even-e.md) §2）。

## 何が annihilation を決めるのか

`k ≤ 135` の 204 組を 3 条件で分類した結果
（[箱の訂正](../updates/2026-09-03-box-correction.md) §6）:

- **`⟨seed⟩ ⊇ ker χ` は必要条件**。`k ≤ 403` で構成的に証明済み、`gcd(k,210)=1` かつ
  index ≥ 3 なら一般 `k` でも成立（[seed-kernel-necessity](../hypotheses/live/seed-kernel-necessity.md)）。
  09-01 で「`k=35` が反例」として棄却されたが、それは部分箱の産物だった。
- 十分ではない。満たしても `k=23, 39, 55` などは全 class で不成立。
- center 固定（`k | 840`、すなわち `k ∈ {3,7,15,35}`）かつ `⟨seed⟩ ⊇ ker χ` の
  24 組では 20 組が成立。外れる 4 組は全て `k=35`。
- `h=1` は常に `c ≡ 1/4`、`t₂ = t₁` で target が 1 本に潰れ、不利。

`k=11` の解析が示したのは、効いているのが **seed の約数剰余集合が `t₁` を外せる
NR 剰余を何本残すか**、そしてそれが `t₂` で潰れるかだという点である。残るのは

1. center が動く成立 10 組（`k=11,19,31,47,59`）の証明。
2. `⟨seed⟩ ⊇ ker χ` を満たして不成立の組を分ける第二の条件（`k=35` の 4 class が最小例）。
3. `gcd(k,210) > 1`、`k ∤ 840` での fiber を含む一般命題。

## 状態

正しい箱で有限閉包と実素数監査が完全に一致する枠組みが揃った。再現コードは
[`code/`](../code/README.md)。一般 `k` に対する annihilation 定理は未証明。

関連: [箱の訂正](../updates/2026-09-03-box-correction.md)、
[closure の訂正（撤回済み）](../updates/2026-09-01-closure-correction.md)、
[追加検証ダイジェスト](../updates/2026-09-01-addendum.md)、
[QR-support 十分性](../hypotheses/live/qr-support-sufficiency.md)、
[Character-annihilation criterion](../hypotheses/live/character-annihilation-criterion.md)
