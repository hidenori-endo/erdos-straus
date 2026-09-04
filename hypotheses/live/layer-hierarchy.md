# 恒等式層の階層 (定理 3)

- status: live / 各固定 `D` の無条件密度上界と character 圧縮は証明済み、`D=D(x)` への一様化は未証
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

## 一様化 route の精密化

[complement normalization / cross-layer audit](../../updates/2026-09-04-complement-normalization-and-cross-layer-audit.md)
により、層の target は補約数を取って常に `-1` に正規化でき、stabilizer が与える部分群の
union は odd character kernel の union に厳密に圧縮できる。割当数は

~~~
C_D = product_{d<=D} (phi(4d)/2)^(2^omega(d)),
log C_D <= L(D) log(2D).
~~~

一方、各層の escape cost を絶対定数で抑える有限群補題は偽である。`C_(2m)` に generator
を `m-1` 個置き、補約数で正規化した target `-1=g^m` を取ると最小 escape は `m-1`。
一方、実データでは `p=3361`, `(d,e)=(17,17)` の旧 target に対する escape 3 は、正規化後
には 1 へ下がる。`p<10^8`, `D<=24` の同時残余では正規化 escape は全て 2 以下だった。
残る具体的標的は、全層を同時に miss する prime について、正の割合の層で escape が定数以下
となること（またはその平均版）を shift 間の差を使って示す cross-layer 補題である。

[inverse escape audit](../../updates/2026-09-04-inverse-escape-and-retro-capture.md) では、
miss 列の非自明 support `A` について、`-1∉⟨A⟩`、`|A|≤4`、または
`2|A|<|⟨A⟩|` のいずれかとなる一般補題を証明した。一方、二つの residue `g,g^-1` だけでも
escape `|G|-2` が可能なので、support 数だけから定数 escape は出ない。現在の最も明確な予想は、
`b_(d,e)(p)≥3` の layer miss は必ず `d'<d` の層ですでに hit しているという
**retro-capture conjecture**。`p<10^8`, `d≤32` では全件成立するが、一般証明は未成立。
