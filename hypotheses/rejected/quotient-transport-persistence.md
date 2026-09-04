# Quotient transport / persistence-impossible route

- status: rejected
- source: 2026-09-04 の測定（[transport verdict](../../updates/2026-09-04-transport-verdict-and-min-hit-shift.md) §3）

## 主張

[09-04 adaptive external-NR note](../../updates/2026-09-04-adaptive-nr-factor-forcing.md) §5 の

> whether miss states can be transported between induced shifts in a quotient where
> persistence is impossible

を proof engine にする案。ある induced shift `k_r` での miss state を次の induced shift
`k_{r'}` へ写し、その商群の中では miss が persist できないことを示して矛盾を得る。

## 棄却理由

輸送すべき状態が存在しない。survivor 7,452 個 × NR rank 0..31 の miss/hit を測ると:

- 生の同時 miss 相関 `joint/(m_i m_j/n)` は rank 0-1 の 1.28 が最大、離れた rank では 1.00。
- 各 `(p, rank)` の miss 確率を `(k, d(C_k²))` の 2 変数で較正した残差相関は
  **全ペアで 0.00–0.04**。
- 較正した独立モデルは「最初の 12 rank が全て miss」を 0.01 件と予測し、実測も 0 件。

したがって induced shift 間の miss の同時構造は `k_r` の大きさと `d(C_{k_r}²)` だけで
説明し尽くされ、shift 間に運ばれる情報は残らない。「persistence が不可能な商」を
作ろうとしても、persist すべき invariant が無い。

## 残るもの

否定されたのは「輸送」という論法の形であって、adaptive external-NR 構成そのものではない。
構成は有効なままで、効いている量は `d(C_k²)/k` である
（[min hit shift bound](../live/min-hit-shift-bound.md)）。同じ測定から、
証明が満たすべき形は数え上げ（区間 `[N, N+K]` の約数の剰余分布）であることが確定した。

再現: `code/residual_corr.cpp`, `code/transport_test.cpp`。
