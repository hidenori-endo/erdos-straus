# External-NR cycle の単調降下

- status: rejected
- source: 2026-09-03 会話の追加検証

## 主張

external NR factor cycle に沿って defect や box failure に単調な ranking function を
定義すれば、最終的に signed-box hit へ降下できる。

## 反証

`p=3361` の `53→31→1103→1051→281→11→53` という 6-cycle が存在し、各頂点で
aligned-shield が失敗する。従って cycle の存在から解への単調降下は導けない。

full cofactor を使う route を否定した結果ではなく、cycle-only の proof engine を
棄却したもの。
