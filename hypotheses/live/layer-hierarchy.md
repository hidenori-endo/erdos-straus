# 恒等式層の階層 (定理 3)

- status: live / 各固定 `D` の無条件密度上界は証明済み、`D=D(x)` への一様化は未証
- source: 2026-09-04 の[層の同定](../../updates/2026-09-04-layer-identification.md)

## 定理 3（証明済み）

`e = ∏ q^{a_q}`、`d = d(e) = ∏ q^{⌈a_q/2⌉}`、`n = p + 4e`（`p ≡ 1 mod 4`）とすると
`n ≡ p (mod 4d)` で、

~~~
∃ k ≡ 3 (mod 4): e | C_k² かつ e ≡ -C_k (mod k)
  ⟺  n が k ≡ -n (mod 4d) なる約数 k を持つ
~~~

hit した `k` から Type II 解 `(C_k, p(e+C_k)/k, p(C_k²/e + C_k)/k)` が復元される。
`d=1` は [D=1 の恒等式](certificate-complexity.md)（`p+4` が `3 mod 4` の約数を持つ）。

`p < 3·10^6` の hard prime 6,628 個で箱の総当たりと突き合わせ、食い違い 4 件は全て
総当たり側の `k ≤ 20003` 打ち切りによるもので、定理側の証拠は厳密に検証済み。

## 層の構造

`d ≤ 8` は 17 層で全て Type II。Type I 層は hard class では `d ≤ 10` で空、最初は
`d = 11`, `e = 11`, `k = 3`（`p ≡ 8 mod 11` ⇒ hit）。

`(Z/4d)^*` の指数が 2 のとき（`4d ∈ {4, 8, 12, 24}`、すなわち `d ∈ {1,2,3,6}`）、
約数の剰余集合は素因子の剰余が生成する部分群に一致し、

~~~
層 (d,e) の失敗  ⟺  -n ∉ ⟨ q mod 4d : q | n ⟩
~~~

が厳密に成り立つ（`p<10^7` の全 hard prime で不一致 0）。`d = 4,5,7,8`（指数 4,4,6,8）では
重複度が効くのでこの形にならない（不一致 1551 / 1301 / 2661 / 3541）。

## 未被覆密度

予算 `D` の未被覆割合は `(log p)^{-δ(D)}` の形で減り、`δ` は層数 `L(D)` にほぼ比例する
（`δ/L` は 0.46 → 0.36、独立なら 0.5）。`D=1` の `δ ≈ 0.46` は Landau–Ramanujan の
理論値 `1/2` と一致。`d ≤ 32`（93 層）では `p < 10^8` の全 hard prime が被覆される。

これは [small-fab sieve dimension](fab-sieve-dimension.md) の `κ(M)` 構想の、
明示的で証明済みの版にあたる。

## 未証の部分

指数 2 の 9 層（`d ∈ {1,2,3,6}`、法 4, 8, 12, 24）については、単一素因子
certificate の Selberg sieve により共通失敗 prime が `O(x/(log x)^3)`、hard prime
内の相対割合が `O((log x)^-2)`。さらに odd character による exact miss の分離で、
exact 共通失敗 prime は `O(x/(log x)^(11/2))`、相対 `O((log x)^(-9/2))` まで証明済み。
詳細は [proof-route audit](../../updates/2026-09-04-route-audit-and-exponent2-sieve.md)。
固定 `D` で未被覆 prime が無限に残るかは未証。`cert(p)` の非有界性は `k,d` の同時有界を
否定するだけで、固定 `D`・非有界 `k` の可能性までは否定しない。upper-bound sieve 単独では
parity barrier のため空集合を導けない。

## 高指数層を含む固定予算（証明済み）

[finite-group sieve lemma](../../updates/2026-09-04-higher-layer-finite-group-sieve.md) により、
任意の固定 `D` で、全 Type-II 層を miss する hard prime の個数は

~~~
O_D(x (log log x)^B_D / (log x)^(1+L(D)/2)),
L(D)=sum_{d<=D} 2^omega(d).
~~~

従って仮想反例の個数は任意の固定 `A` に対し `O_A(x/(log x)^A)`。証明完了に残るのは、
この評価を `D=D(x)` にできる一様な定数管理である。
