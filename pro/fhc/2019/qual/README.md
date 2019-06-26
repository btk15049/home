# Facebook Hacker Cup 2019 Qualification Round

## Leapfrog: Ch. 1

問題を正しく読んで B を数える

## Leapfrog: Ch. 2

B2 個をうまく使うと無限に前に進めるようになるので、これを使う

## Mr. X

何も考えずに区間 DP をするとちょっと待てば通る。
よく考えると、答えは最大でも 1（最後に使われる演算子をいじると valid になるため）

## Trees as a Service

枝狩り、メモ化全探索を書くと通る。
お気持ちとしては、根の方から valid な分割を繰り返していけばよい。
同じじゃなきゃいけない集合の管理に Union-Find を用いるのがポイント

### 新しく学んだこと

- 枝狩りを信じる心
