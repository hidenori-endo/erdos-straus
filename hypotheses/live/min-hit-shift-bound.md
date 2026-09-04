# Exact box の最小 hit shift は小さい

- status: live / conjecture
- source: 2026-09-04 の測定（[transport verdict](../../updates/2026-09-04-transport-verdict-and-min-hit-shift.md) §5）
- confidence: `p < 10^9` の hard prime 全数で成立。証明なし。

## 仮説

hard prime `p` に対し

~~~
minK(p) := min { k ≡ 3 (mod 4) : Div(C_k²) mod k が -1/4 または -C_k を含む }
~~~

とおく（`C_k=(p+k)/4`）。ES(p) ⇔ `minK(p)` が有限。測定は `minK(p)` が
`(log p)^2` よりずっと小さいことを示す。

## 根拠

`p < 10^9` の hard prime を全数走査した（`code/min_hit_k.cpp`、survivor 51,625、未解決 0）。
反例でない hard prime は
[補題 1](../../updates/2026-09-04-transport-verdict-and-min-hit-shift.md#1-反例条件の言い換え証明済み部分のみから従う)
より atlas shift（`k ≤ 59`）で hit するので、最大値は survivor 上で達成される。

- `max minK(p) = 107`、達成するのは `p = 8,803,369` ただ 1 個。
- それ以外は全て `minK ≤ 83`、99.6% が `minK ≤ 23`。
- decade 別最大: `10^3`→23, `10^4`→31, `10^5`→59, `10^6`→107, `10^7`→63, `10^8`→83。
  `10^6` 台以降は増えていない。

`(log 10^9)^2 ≈ 430` なので、
[external shift log-squared conjecture](external-shift-log-squared-conjecture.md)
（external prime shift に限った版、`p<10^8` で最大 251）よりさらに余裕がある。

## なぜ小さいのか（測定された機構）

hit 率は `2 d(C_k²) / k` に従い、`k` が大きいところではこの等分布モデルに
比 1.00 で一致する。小さい `k` では箱が `ker χ` に偏るため比は 0.09 まで落ちるが、
`2d/k` 自体が大きいので hit 率の絶対値は高い。よって最小 `k` に hit が集中する。

## 証明に必要なもの

「`d((N+j)²)` が `j = 0..K` の全てで小さく、かつ `Div((N+j)²) mod (4j+3)` が
2 つの指定剰余を避け続ける」ことの不可能性。算術級数中の約数分布の問題であり、
finite sieve では parity barrier に当たる。`K = 107` は要求される `K` の実測上界。
