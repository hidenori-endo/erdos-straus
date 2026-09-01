# 07. Character annihilation atlas

## 目的

composite shift `k` に対し、class-conditioned mandatory seed と exact center fiber を
先に固定する。そのうえで signed-box の reachable state を有限群上で閉包し、
Jacobi character が `-1` の miss branch を完全に消せるかを判定する。

ここでいう annihilation は、計算上の state が消えるという意味ではなく、対象の
center fiber に到達した miss state が全て pure Jacobi `+1` support になる、という意味。

## k=15

全 hard class で、combined miss の thin 11-packet は最終 center 条件を入れると空。
したがって会話内の範囲-free整理は

~~~
k=15 が miss ⇔ C_15 の全素因子が p-QR
~~~

である。これは p-NR 因子の完全 detector として扱える候補で、`p<10^8` の
179,468 hard prime 監査では exact miss と pure-H miss がともに 98,684、
non-pure miss と mismatch は 0 と報告された。

## k=35

6 hard class の state closure は次の atlasになった。

| `h=p mod 840` | miss state | pure miss | non-pure miss |
|---:|---:|---:|---:|
| 1 | 12 | 4 | 8 |
| 121 | 2 | 2 | 0 |
| 169 | 6 | 3 | 3 |
| 289 | 3 | 2 | 1 |
| 361 | 3 | 3 | 0 |
| 529 | 6 | 4 | 2 |

従って `h=121,361` では

~~~
k=35 が miss ⇔ C_35 の全素因子が p-QR
~~~

が exact pure-support theorem の候補になる。他の4 classでは non-pure miss が残り、
同じ主張は偽である。

class 121 の closure は `(Z/35Z)^× ≃ C_12 × C_2` 上で行われ、正しい64-bit 実装
では reachable state 394 個。途中で 406 と報告された値は 32-bit mask の実装ミスで、
394 に訂正された。

## k=39

mandatory seed だけでは character branch は消えない。

| seed | miss | `+1` miss | `-1` miss |
|---:|---:|---:|---:|
| 2 | 74 | 52 | 22 |
| 10 | 20 | 17 | 3 |

これは k=15 や k=35 の一部で起きた完全 annihilation が、seed の存在だけから
一般に従うわけではないことを示す control である。

## 暫定 criterion

現時点で必要なのは、個別 k の state 表ではなく、次の条件の群論的特徴づけである。

1. mandatory seed が center fiber のどの character を固定するか。
2. `C_k` の残り因子が生成する sub-box が QR kernel を飽和するか。
3. その saturation と exact center の組合せが `-1` character の miss state を消すか。
4. hard class による強制因子が、次の shift で同じ条件を再現するか。

k=15 全 class、k=35 の class 121/361、k=39 の失敗が、この criterion を抽出する
ための最初の比較対象である。

## 状態

finite-group closure による探索・反例検出の枠組みは有用。一般の composite k に対する
annihilation theorem は未証明。

関連: [追加検証ダイジェスト](../updates/2026-09-01-addendum.md)、
[Character-annihilation criterion](../hypotheses/live/character-annihilation-criterion.md)
