# Mandatory seed + exact center による character annihilation

- status: live / classification problem（2026-09-03 箱の訂正で atlas を再構成）
- source: 2026-09-01 会話の追加検証、2026-09-01 closure 訂正（撤回）、2026-09-03 箱の訂正
- confidence: 成立する 30 組は range-free 閉包と `p<10^8` 監査の両方で確定。
  一般 criterion は未確立。

## 問い

shift `k ≡ 3 (mod 4)` と hard class `h` を固定し、class-conditioned mandatory seed を
消費したうえで `p ≡ h (mod 840)` が許す exact center fiber に閉じたとき、
character `-1` の miss state が全て消える条件を特徴づける。

片方向（[QR-support 十分性](qr-support-sufficiency.md)）は初等的に証明済みなので、
残っているのは逆向き「miss ⇒ pure」がいつ成り立つか、である。

## 現在の atlas（正しい箱 `Div(C_k²)`）

`k ≤ 403` の 101 shift × 6 class = 606 組のうち成立は 30 組。

| `k` | 成立する `h` |
|---:|---|
| 3 | 全 6 class |
| 7 | 全 6 class |
| 11 | 169, 289, 529 |
| 15 | 全 6 class |
| 19 | 121 |
| 31 | 169, 289, 529 |
| 35 | 121, 361 |
| 47 | 121, 289 |
| 59 | 361 |
| ≥ 63 | なし |

`k=11` の class 分割は有限閉包と実素数監査で完全に一致し、その原因も
[seed `15 | C_11` の補題](k11-seed15-lemma.md)として証明済みである。
`k=35` の 2 class は [k=35 pure-support 定理](k35-pure-support-theorem.md)。

### 不成立の 576 組は構成的

成立しない組にはすべて `p < 10^8` に「miss かつ非 pure」の実素数がある
（最大の最小 witness は `(71,289)` の `p = 3,098,209`）。閉包モデルによる否定ではなく
実素数の反例なので、この不成立はモデルの正しさに依存しない。

## 条件候補の状態（正しいデータで再点検）

- **seed が QR kernel を生成する**: 成立 30 組すべてが満たす**必要条件**。09-01 に
  「`k=35` が反例」として棄却したのは部分箱の産物で撤回。十分ではない
  （`k ≤ 135` で満たしつつ不成立の組が 112）。
- **center fiber が 1 点（`k | 840`）**: 必要でも十分でもない。ただし
  `⟨seed⟩ ⊇ ker χ` と組むと 24 組中 20 組が成立し、外れるのは `k=35` の 4 class のみ。
- **`t₁ ≠ t₂`**: `h=1` では常に `t₂ = t₁`。center 固定・seed 生成の下でも
  `k=35, h=1` は不成立。
- **composite であること**: 成立する `k` に素数（3, 7, 11, 19, 31, 47, 59）が多く、
  無関係。

## 現在の見立て

`⟨seed⟩ ⊇ ker χ` が必要条件として立ったので、次は

1. 「`⟨seed⟩ ⊉ ker χ` ⇒ 非 pure な miss state が存在する」を `k` に依存しない形で
   証明する。閉包の witness path（例: `k=19, h=169` は seed 1 に NR 1 個）を使う。
2. `⟨seed⟩ ⊇ ker χ` かつ center 固定の 24 組で、`k=35` の 4 class だけが落ちる理由を
   miss state の書き下しで説明する（[k=35 定理](k35-pure-support-theorem.md)の表）。
3. center が動く成立 10 組（`k=11,19,31,47,59`）で、どの fiber が生き残るかを
   [seed 補題](k11-seed15-lemma.md)の形（`t₁` を外せる NR 剰余の本数）で分類する。

関連: [07. atlas](../../topics/07-character-annihilation-atlas.md)、
[箱の訂正](../../updates/2026-09-03-box-correction.md)、
[k=35 pure-support 定理](k35-pure-support-theorem.md)
