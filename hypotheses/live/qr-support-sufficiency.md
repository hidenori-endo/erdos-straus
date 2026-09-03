# QR-support 十分性

- status: **proved**（初等・完全証明・大規模監査済み）
- source: 2026-09-01 closure 訂正
- 関連: [character-annihilation-criterion](character-annihilation-criterion.md)、
  [k35-pure-support-theorem](k35-pure-support-theorem.md)
- 箱: 判定は正しい箱 `Div(C_k²)`（[2026-09-03 箱の訂正](../../updates/2026-09-03-box-correction.md)）。
  証明は `S` を `C_k²` の約数剰余集合と読んでそのまま通る。

## 主張

`k ≡ 3 (mod 4)`、hard prime `p`、`C_k = (p+k)/4` とする。

~~~
C_k の全ての素因子 r が p-QR （(p/r) = +1）ならば、shift k は miss する。
~~~

対偶: **shift k が hit するならば、`C_k` は p-NR の素因子を持つ。**

## 証明

target は `t₁ = -1/4 (mod k)`、`t₂ = -C_k (mod k)`。character を
`χ(r) = jacobi(r,k)` とおく。

1. `r | C_k` なら `4C_k = p+k` より `p ≡ -k (mod r)`。`k ≡ 3 (mod 4)` なので
   相互法則の符号が `(-1/r)` と相殺して
   `(p/r) = (-k/r) = (-1/r)(k/r) = (-1/r)²(r/k) = χ(r)`。
   `r = 2` のときは `2|C_k` から `p ≡ -k (mod 8)` が従い、Kronecker 記号として
   同じ等式になる。よって「全素因子が p-QR」= 「全素因子が `ker χ` に入る」。
2. 全素因子が `ker χ` に入るなら、その積である `C_k²` の全約数も `ker χ` に入る。
   約数剰余集合を `S` として `S ⊆ ker χ`。
3. `k ≡ 3 (mod 4)` より `χ(-1) = (-1)^{(k-1)/2} = -1`。また `4` は平方なので
   `jacobi(4,k) = +1`。よって `χ(t₁) = χ(-1/4) = χ(-1) = -1`、つまり
   `t₁ ∉ ker χ ⊇ S`。
4. 仮定より `jacobi(C_k,k) = +1`、すなわち `c = C_k mod k ∈ ker χ`。
   よって `χ(t₂) = χ(-c) = χ(-1)χ(c) = -1`、つまり `t₂ ∉ ker χ ⊇ S`。

`t₁, t₂ ∉ S` なので miss。∎

## 監査

正しい箱で `k = 3,7,11,...,403` の 101 shift × hard prime 4,519 個 = 456,419 件で
「pure かつ hit」は 0 件。`k = 3,7,11,15,19,31,35,47,59,71` は `p < 10^8` の
179,468 件でも 0 件。再現コードは [`code/audit.cpp`](../../code/README.md)。

## 使いどころと限界

これは **shift を捨てる側**の判定である。ある `p` で target を捕まえたいときは
「`C_k` に p-NR 因子がある」ことが必要条件なので、hard prime が全 shift を逃れる
という仮想状況は「全ての admissible `k` で `C_k` に p-NR 因子があるのに、それが
一度も target を踏まない」という形に絞られる。

逆向き（miss ⇒ pure）は一般には偽で、`k ≤ 403` で成立するのは 30 組のみ
（[07. atlas](../../topics/07-character-annihilation-atlas.md)）。
