# Erdős–Straus research context

- source: https://chatgpt.com/c/6a8993cb-a988-83e8-b6b4-020ccbc56969
- captured: 2026-08-28
- additional source: https://chatgpt.com/c/6a914e1d-c37c-83ee-b5fb-e5560a6203a8
- additional captured: 2026-09-01（会話は追加検証依頼で終了）
- format: topic-first Markdown
- note: ChatGPTの思考時間、ツール呼び出し表示、回答操作ボタンなどのUI装飾は除去済み

## Directory tree

```
Erdos–Straus/
├── README.md
├── 00_toc.md
├── manifest.json
├── topics/
│   ├── 01_problem-and-prior-work.md
│   ├── 02_exact-reformulation.md
│   ├── 03_hard-prime-obstructions.md
│   ├── 04_divisor-roster.md
│   ├── 05_search-vs-proof.md
│   ├── 06_cross-shift-and-consecutive-integers.md
│   ├── 07-character-annihilation-atlas.md
│   └── 08-external-nr-and-fab-sieve.md
├── hypotheses/
│   ├── index.md
│   ├── live/          （qr-support-sufficiency.md, k11-seed15-lemma.md, ...）
│   └── rejected/      （k35-pure-support-theorem.md, ...）
├── updates/
│   ├── 2026-09-01-addendum.md
│   ├── 2026-09-01-closure-correction.md
│   ├── 2026-09-03-addendum.md
│   └── 2026-09-03-box-correction.md
└── code/
    ├── README.md
    ├── closure.cpp
    ├── audit.cpp
    ├── witness.py
    └── box_check.py
```

## Reading order

1. `00_toc.md` で論点の地図を確認する。
2. `topics/` で定義・既知結果・証明の流れを読む。
3. `hypotheses/` で数学的仮説の状態（live / rejected）を確認する。
4. `updates/` で追加検証の差分を確認する。`2026-09-01-closure-correction.md` は
   `2026-09-01-addendum.md` §3 の `k=35` を「反証」したが、その訂正自体が箱の誤りで、
   `2026-09-03-box-correction.md` で撤回された（`k=35` 定理は正しい）。atlas の
   現行版は `topics/07` と `2026-09-03-box-correction.md`。
5. `code/` の 4 本（有限閉包 / 実素数監査 / 反例構成 / 箱の総当たり検証）で atlas を
   再現できる。
