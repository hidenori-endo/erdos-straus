# Mandatory seed + exact center による character annihilation

- status: live / classification problem（2026-09-01 closure 訂正で atlas を再構成）
- source: 2026-09-01 会話の追加検証、2026-09-01 closure 訂正
- confidence: 成立する 21 組は range-free 閉包と `p<10^8` 監査の両方で確定。
  一般 criterion は未確立。

## 問い

shift `k ≡ 3 (mod 4)` と hard class `h` を固定し、class-conditioned mandatory seed を
消費したうえで `p ≡ h (mod 840)` が許す exact center fiber に閉じたとき、
character `-1` の miss state が全て消える条件を特徴づける。

片方向（[QR-support 十分性](qr-support-sufficiency.md)）は初等的に証明済みなので、
残っているのは逆向き「miss ⇒ pure」がいつ成り立つか、である。

## 現在の atlas

`k ≤ 403` の 101 shift × 6 class = 606 組のうち成立は 21 組。

| `k` | 成立する `h` |
|---:|---|
| 3 | 全 6 class |
| 7 | 全 6 class |
| 11 | 169, 289, 529 |
| 15 | 全 6 class |
| ≥ 19 | なし |

`k=11` の class 分割は有限閉包と実素数監査で完全に一致し、その原因も
[seed `15 | C_11` の補題](k11-seed15-lemma.md)として証明済みである。

### `k ≥ 19` は構成的に不成立

`k = 19, …, 403` の 97 shift × 6 class = 582 組すべてについて、
**miss かつ非 pure な実素数を明示的に構成できる**（探索上限 `p < 2·10^7`、
見つからなかった組は 0）。最大の「最小反例」でも `p = 66,529`（`k=35, h=169`）で、
582 組すべてが `p ≤ 66,529` の範囲で潰れる。閉包モデルによる否定ではなく実素数の
反例なので、この不成立はモデルの正しさに依存しない。

## 棄却された必要条件候補

- **seed が QR kernel を飽和する**: `k=35` は `⟨3⟩ = ker χ`（位数 12）を飽和するが
  不成立。`k ≤ 300` の composite で飽和するのに不成立な組が 140 ある。
- **center fiber が 1 点（`k | 840`）**: `k=35 | 840` だが不成立。
- **composite であること**: 成立する `k` の多数（3, 7, 11）は素数。composite に
  限定していた旧 atlas の枠組み自体が狭かった。

## 現在の見立て

成立する 21 組は `k < 19` に集中している。`(Z/kZ)^×` が小さいと `ker χ` の
補集合が target を覆いやすく、非 pure な状態が必ず target を踏む、という
サイズ効果が主因である可能性が高い。次に必要なのは

1. `k ≥ 19` で必ず non-pure miss が現れることを、`k` に依存しない形で**証明**
   すること。`k ≤ 403` は上のとおり構成的に確認済みだが、一般 `k` の構成は
   `C_k = seed · q`（`q` は p-NR 素数）の形を狙うと `p = 4·seed·q - k` と `q` が
   同時に素数であることを要求し、Dickson 型の素数タプル予想に落ちる。
   無条件の証明には別の構成が要る。
2. 成立する 21 組が `k ≤ 15` に限られることの群論的な説明。`k=11` については
   [seed 補題](k11-seed15-lemma.md)が完全な答えを与えたので、同じ形の議論
   （seed の約数集合が `t₁` を外せる NR 剰余を何本残すか）を `k=3,7,15` と
   `k ≥ 19` の境界に一般化するのが次の一手。

の 2 点である。

関連: [07. atlas](../../topics/07-character-annihilation-atlas.md)、
[closure の訂正](../../updates/2026-09-01-closure-correction.md)、
[k=35 定理候補（棄却）](../rejected/k35-pure-support-theorem.md)
