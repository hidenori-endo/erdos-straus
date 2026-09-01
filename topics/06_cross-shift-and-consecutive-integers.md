# 06. Consecutive integers と cross-shift

## 座標変換

admissible shift を `q_j=4j+3` とし、

~~~
N=(p+3)/4,
C_{q_j}=(p+q_j)/4=N+j
~~~

と置く。この座標では、shift roster は連続整数 `N,N+1,N+2,...` の因数分解を
順に調べる操作になる。

signed-box の target は

~~~
Type I:  D ≡ -(j+1) (mod q_j)
Type II: D ≡ -C_{q_j} (mod q_j)
~~~

である。Type I target から p が消えることは、shift ごとの個別観察を一つの
連続列の問題へ移す重要な整理である。

## 最初の p-NR と exact hit

会話内の全数スキャンでは、`p<10^8` の Mordell-hard prime 179,468 個について、
最初の p-quadratic-nonresidue 因子を持つ shift `q_NR` と最初の exact hit `q_hit` を
比較した。

- `q_NR=q_hit`: 175,761/179,468 = 97.93%
- `max q_NR=59`
- `max q_hit=107`
- 最大遅延の例: `p=8,803,369` で `q_NR=43`, `q_hit=107`

従って典型的な hard prime では NR 因子の出現がそのまま target 捕捉になる。
残る本当の障害は、NR 因子が既にあるのに signed-box の到達集合が target を外す
exceptional defect である。

## q=7 の saturation

最初の NR-bearing shift で失敗する例のうち、q=7 では QR sub-box が
`Q_7` を埋めると、NR 因子一つを加えた時点で `Q_7 ∪ rQ_7` が全単元群になる。
会話内の実験では、最初の NR-bearing shift 172,146 件のうち 159,836 件
(92.85%) が NR 因子を加える前に QR sub-box を飽和させていた。

これは「NR supply → QR saturation → target capture」という局所機構の具体例で
あり、全 shift の定理ではない。q=7 については、hard prime で `2|C_7`、mod 7 の
box `{2^-1,1,2}={4,1,2}=Q_7` となるため、NR 因子があれば hit するという形で
整理されている。

## 既知の到達点と限界

- q=11 → q=19 は、zero-slack 条件、hard class、強制因子 5,7、`Q_19` saturation
  が接続した最初の clean な cross-shift chain。
- q=23 → q=27/31 の固定 route は `p<10^9` の探索で反証された。
- したがって、次の証明対象は「すべての hard prime が有限個の shift のどれかで解ける」
  という roster 表ではなく、`N+j` に沿って defect がいつか target を捕捉する
  adaptive な補題である。

## 状態

cross-shift の個別補題と数値統計は有用。全 hard prime を覆う一般定理は未確立。

関連: [追加検証ダイジェスト](../updates/2026-09-01-addendum.md)、
[Global branch-covering problem](../hypotheses/live/global-branch-covering.md)
