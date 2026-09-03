# Bounded external-NR rank（aligned-shield seed-only）

- status: rejected
- source: 2026-09-03 会話の追加検証

## 主張

最初の有限個の external NR prime のどれかを、squarefree `M=qs`、`s|210` の forced
seed-only rule で必ず使える。

## 反証

任意の N に対し、`q_i>632`、`(2/q_i)=-1` を持つ q_i を CRT/Dirichlet で選び、各 q_i
の aligned seed-only subset を同時に miss させられる。従ってこの限定 rule には任意の
finite rank の no-go theorem がある。

full `C_q` cofactor を含む external-NR route や ES 本体を反証するものではない。
