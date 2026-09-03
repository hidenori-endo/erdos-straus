# Detector miss から external target position を直接予測する

- status: rejected as a direct bridge
- source: 2026-09-03 会話の追加検証

## 主張

class-specific detector を全て miss した p では、external signed-box target の位置に
強い discrete-log bias や occupancy bias が現れ、それが次の hit を直接予測する。

## 反証

detector survivor と一般 hard prime を比較した探索では、有意な target-position bias は
ほぼ出なかった。external hit の主因は小さい fab certificate と forbidden prime-factor
classes の方に見える。

target placement の研究全体を否定するものではなく、detector miss から直接 target を
予測する shortcut を棄却したもの。
