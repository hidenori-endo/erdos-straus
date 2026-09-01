# q=23 thin miss は q=27/31 へ必ず進む

- status: rejected
- source: 2026-09-01 会話の追加検証

## 主張

q=19 の pure-QR survivor が q=23 の thin miss に入った場合、`p mod 11` により
`11|C_27` または `11|C_31` が強制され、次の shift で必ず解ける。

## 反証

q=19 survivor 710 件の小さい探索では、q=23 は 459 hit、247 pure-QR miss、
4 thin miss。4 件は確かに q=27/31 へ route した。

しかし `p<10^9` まで探索すると q=23 thin survivor は 61 件となり、
`p mod 11=1:5, 2:31, 6:25` に分布した。従って `p mod 11=1` の survivor が存在し、
固定 route は成立しない。

## 残る教訓

少数例で見えた factor routing を universal lemma とみなしてはいけない。route を
使うなら、thin state の support alphabet と hard class の合同条件を同時に含む
意味論的な条件が必要である。
