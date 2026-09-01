# 07. Character annihilation atlas

## 目的

shift `k ≡ 3 (mod 4)` と hard class `h = p mod 840` を固定したとき、
`C_k = (p+k)/4` の素因子の quadratic character だけで、その shift が
Type I / Type II target を逃すかどうかが決まるかを判定する。

判定は 2 通りで行い、両者を突き合わせる。

- **実素数監査**: `C_k` を実際に素因数分解し、全約数の `mod k` 剰余を作って
  target を踏むか直接見る。モデルを使わない ground truth。
- **有限閉包**: 状態 `(S, c, neg)` を有限群上で BFS 閉包する。range-free だが
  モデル依存。

## 記号

- Type I target `t₁ = -1/4 (mod k)`、Type II target `t₂ = -C_k (mod k)`。
- character `χ(r) = jacobi(r,k)`。`r | C_k` なら `p ≡ -k (mod r)` と
  `k ≡ 3 (mod 4)` から `χ(r) = (p/r)` が従う（`r=2` も Kronecker 記号で同じ）。
- **pure** = `C_k` の全素因子が p-QR、すなわち `χ = +1`。

## 定理: QR support は miss に十分

`k ≡ 3 (mod 4)` なので `χ(-1) = -1`、また `jacobi(4,k) = +1` なので
`χ(t₁) = χ(-1) = -1`。pure なら `c = C_k mod k ∈ ker χ` なので
`χ(t₂) = χ(-1)χ(c) = -1`。一方 pure なら全約数が QR 因子の積なので
`S ⊆ ker χ`。よって `t₁, t₂ ∉ S`、すなわち miss。

~~~
C_k の全素因子が p-QR  ⇒  shift k は miss
~~~

対偶は「shift k が hit するなら `C_k` は p-NR 素因子を持つ」。`k ≤ 403` の
101 shift × hard prime 4,519 個 = 456,419 件で反例 0。

## 逆向きが成り立つ `(k,h)`

逆向き（miss ⇒ pure）は shift と class に強く依存する。`k ≤ 403` の
101 shift × 6 class = 606 組のうち、成立するのは **21 組だけ**。

| `k` | 成立する `h` | 不成立の `h` |
|---:|---|---|
| 3 | 全 6 class | — |
| 7 | 全 6 class | — |
| 11 | 169, 289, 529 | 1, 121, 361 |
| 15 | 全 6 class | — |
| ≥ 19 | なし | 全部 |

この 21 組では

~~~
shift k が miss  ⇔  C_k の全素因子が p-QR
~~~

が両方向の同値になる。`p < 10^8` の hard prime 179,468 件で mismatch 0、かつ
有限閉包でも range-free に成立（`k=11` の class 分割は closure と実素数で完全一致）。

## `k=15` の証明証拠

完全閉包は 42 状態で閉じる。center fiber に到達する 8 状態のうち miss は 2 個で、
その約数剰余集合は必ず

~~~
S ⊆ {1,2,4,8} = ker χ ⊂ (Z/15Z)^×
~~~

に収まる。`non-pure miss = 0`（miss ⇒ pure）と `pure かつ hit = 0`（pure ⇒ miss）が
同時に立つ。`k=15 | 840` なので center は class ごとに 1 点に固定される。

## `k=35` は不成立（先行報告の訂正）

以前は `h=121,361` で annihilation が起きるとされていたが、これは状態遷移に
`S → S ∪ rS ∪ r²S` を使い、指数 1 の素因子に対して実在しない約数 `r²` を
混ぜていたことによる artifact だった。正しい遷移 `S → S ∪ rS` では全 class で
non-pure miss が残り、実素数にも反例がある。

| `h` | 最小反例 `p` | `C_35` |
|---:|---:|---|
| 1 | 26,041 | 3·41·53 |
| 121 | 21,121 | 3·41·43 |
| 169 | 66,529 | 3²·43² |
| 289 | 12,049 | 3·19·53 |
| 361 | 19,681 | 3·31·53 |
| 529 | 9,769 | 3·19·43 |

`p<10^8`・class 121 では hard prime 29,900 のうち exact miss 20,298、pure miss
18,080、その差 2,218 件が「miss だが p-NR 因子を持つ」。

## `k=11` の class 分割は seed で決まる

`k=11` は `840` を割らないので center fiber は `Z/11Z` 全体であり、class 差は
mandatory seed だけから来る。`h=169,289,529` では `15 | C_11`、
`h=1,121,361` では `3 | C_11` のみ。前者では

~~~
15 | C_11 かつ C_11 が p-NR 素因子を持つ ⇒ shift 11 は hit
~~~

が初等的に証明できる（`t₁ = 8` を外せる NR 剰余は `r ≡ 7` だけに絞られ、それも
`t₂` で潰れる）。後者では `S ⊇ {1,3}` しかないため `r ∈ {2,6,7}` が生き残り、
`C_11 = 3·r`（`r ≡ 2 mod 11`）の実素数反例がある（`h=361` の最小反例は
`p = 1,201`、`C_11 = 3·101`）。詳細は
[k=11 の seed 15 補題](../hypotheses/live/k11-seed15-lemma.md)。

## `k ≥ 19` は構成的に不成立

`k = 19, …, 403` の 97 shift × 6 class = 582 組すべてで、**miss かつ非 pure な
実素数を明示的に構成できる**（探索上限 `p < 2·10^7`、witness の無い組は 0）。
最大の「最小反例」でも `p = 66,529`（`k=35, h=169`）で、582 組すべてが
`p ≤ 66,529` で潰れる。閉包モデル由来の否定ではなく実素数の反例なので、
この不成立はモデルの正しさに依存しない。

`k=39` を「機械的一般化の失敗例」として特別扱いする必要はなく、
`k ≥ 19` 全体が同じ理由で不成立側である。

## 何が annihilation を決めるのか

未解決。少なくとも次は**十分条件ではない**。

- mandatory seed が `ker χ` を生成すること。`k=35` は `⟨3⟩ = ker χ` を満たすが
  不成立。
- center fiber が 1 点（`k | 840`）であること。`k=35 | 840` だが不成立。

- compositeness。成立する `k` の多くは素数である。

`k=11` の解析が示したのは、効いているのが「seed が `ker χ` を飽和するか」では
なく **seed の約数剰余集合が `t₁` を外せる NR 剰余を何本残すか** だという点である。
`{1,3}` は 3 本残すが `{1,3,4,5}` は 1 本しか残さず、それも `t₂` で消える。
`(Z/kZ)^×` が大きくなると外せる NR 剰余の割合が増えるため、`k ≥ 19` が全滅する
ことの説明にもなっている。残るのは、この数え上げを `k` に依存しない形にして
`k ≥ 19` の不成立を証明することである（`k ≤ 403` は上のとおり構成的に確認済み）。

## 状態

有限閉包と実素数監査が完全に一致する枠組みが揃った。再現コードは
[`code/`](../code/README.md)。一般 `k` に対する annihilation 定理は未証明。

関連: [closure の訂正](../updates/2026-09-01-closure-correction.md)、
[追加検証ダイジェスト](../updates/2026-09-01-addendum.md)、
[QR-support 十分性](../hypotheses/live/qr-support-sufficiency.md)、
[Character-annihilation criterion](../hypotheses/live/character-annihilation-criterion.md)
