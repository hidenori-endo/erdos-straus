# Top-strip quantization (p-k = O(sqrt p))

- status: rejected as a proof route (identities are correct; coverage is density zero)
- source: [Turn 034](../../会話ログ/034-assistant.md) + 本セッションの数値検証

## 検証できたこと

Turn 034 の式はすべて正しい。found リスト 10 件で以下を確認した:

- `4dab = 3p+1`, `3k = 4da^2+1`, `H = d(b-a)^2`, `p = 3dh^2 - u`, `u = ceil(s^2/k)`
- `H = (s+u)^2 / (uk - s^2)`
- `uH(p+u) = (H+1)n^2`  (n = s+u)
- 各組から `x = pabd`, `y = bd(a+b)/3`, `z = ad(a+b)/3` が実際に `4/p` を与える

## 棄却理由 1: e=3 の Type I は 1 行の条件に潰れる

一般 e の Type I は `4abd = ep+1`, `gcd(a,b)=1`, `e | d(a+b)` と同値。
e=3 では `M = (3p+1)/4` が `M ≡ 1 (mod 3)` なので `3 ∤ d`、よって `3 | a+b`。
`a = 1` を取れば条件は「`M` が `2 mod 3` の約数を持つ」に落ちる。すなわち

    Type I(e=3) が可解  <=>  (3p+1)/4 が 2 mod 3 の素因子を持つ

p < 4000 の全該当素数 269 個で総当たりと完全一致（不一致 0）。
`(s,u,H,n)` 座標は a ≈ b の隅を記述しているだけで、可解性そのものは a=1 で決まる。

## 棄却理由 2: bounded H の素数は密度 0

`H = d v^2 <= H0` かつ `3p+1 = 4 d a(a+v)` なので、(d,v) の組は `O(H0 log H0)` 個、
各組で a は `O(sqrt X)` 通り。よって `p <= X` で bounded H を持つ素数は `O_{H0}(sqrt X)` 個。

実測（全列挙）:

| X | H0=22 | H0=100 | pi(X) |
|---|---|---|---|
| 1e4 | 45 (3.66%) | 103 (8.38%) | 1229 |
| 1e5 | 123 (1.28%) | 329 (3.43%) | 9592 |
| 1e6 | 328 (0.42%) | 891 (1.14%) | 78498 |

sqrt X 則どおりに割合が落ちる。固定割合 reduction が偽である
（[Fixed-fraction H reduction](fixed-fraction-H-reduction.md)）のに加え、
残った top strip も全素数を覆えない。量子化された sqrt p バンドは
**特殊な素数族の生成器**であって、証明の被覆にはならない。
