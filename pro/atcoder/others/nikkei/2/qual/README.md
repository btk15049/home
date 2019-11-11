# [第二回全国統一プログラミング王決定戦予選](https://atcoder.jp/contests/nikkei2019-2-qual)

writer:

## A

`X+Y=N`について，`X<=Y`を仮定すると以下が成り立つ

- `X<=floor(N/2)`
- `Y=N-X`

したがって，`X=1,...,floor(N/2)`が解の候補になる．
N が偶数のときは，`X=N/2`にすると`X=Y`になってしまうためこれを除外する

まとめて楽に書くと， `ceil((N-1)/2)`が答え

## B

深さ k の頂点は深さ k-1 の頂点にくっつけるしかないことを考えると終わり
根は唯一つなのでそれだけ注意

## C

重要な事実として，`N-1`回の操作を行うと任意の置換列ができる．
ここで，`N-1`回操作ができたとしても条件を満たす列が作れない場合は無条件で`No`にしてよい [1]

次に`N-1`回操作が必要な列とはなにかを考えると，辺（操作前の位置，操作後の位置）を使った頂点数 N のグラフが連結成分 1(ただ一つのサイクル)になっている場合のみ`N-1`回操作が必要である．（このときの移動先の位置を並べた順列を`巡回置換列`というらしい）
言い換えると，移動先の位置を並べた順列が巡回置換列でない構築ができたならば，それは`N-2`回以下の操作で実現できる構築ということになる．
や，ここまではわかるよ，わかる．(順列はサイクルの集合（素振り）)

では，巡回置換列でない列をどのように構成するか
A,B をソートした列を A',B'とおきます
ここで，`A'[i] <= B'[i+1]`となるような i が一つでも存在するならば，答えは`Yes`となります [2]
とりあえずバラバラだとめんどいので(Ai,Bi)でソートしておきます（解に影響ない操作）

[1],[2]を経て`Yes`にならない場合，[1]で既に`No`判定されているか，A,B それぞれが distinct であることが保証されます（これが一番本質的な考察（コンテスト中は気づいていない））
この場合は，操作後に生成される列は一意に定まります（[2]の判定がこれを保証してくれます）
よって，この一意に定まる列が巡回置換列であるか判定して，そうなら`Yes`, そうでないなら`No`を返せば AC できます．

[1]: AとBを両方ソートした列が最適なので，それを使って判定しておく
[2]: 書いてあるとおりソートして判定するだけ
[3]: 順列が1つのサイクルになるか判定するだけ

## D

実 家 の よ う な 安 心 感
[](https://atcoder.jp/contests/code-festival-2015-final-open/tasks/codefestival_2015_final_h)

## E

少し考えるとわかるのですが，構成できるとすると，

- `a \in [K, K+N)`
- `b \in [K+N, K+2N)`
- `c \in [K+2N, K+3N)`

として構成できることがわかります
構成した列(ai,bi,ci)が c でソートされているとすると，(ai+bi)が差 1 の等差数列であるときが明らかに最適です．

最適な列を作るのはちょっと難しいので，N が偶数を仮定して
`j \in [0,N)` に対して

- `(ai,bi) = (K+j, K+N+(N/2+j)%N)`
- i は昇順になるように並び替える

としてみます
このときの`(ai+bi)`は，`2K+N+N/2`, `2K+N+N/2`, `2K+N+N/2+2`, `2K+N+N/2+2` ... となります
準最適感はありますね.（これはお気持ちです）

ところで，最適解が構成できたとしたときにギリギリのケースが存在するとすると
`2N*(K+(K+2N-1))/2 <= N* ((K+2N)+(K+3N-1)) /2` が成り立つので，
`2K<=N+1`です

ここでは N が偶数を仮定しているので，`2K<=N`のときに`(K+2N)-(2K+N+N/2)`が 0 以上であってほしい気持ちになります
`(K+2N)-(2K+N+N/2)=N/2-K <= K-K = 0`
0 以上でした（ぱちぱち）
この構築で N が偶数の場合に，解が`Yes`の場合でも正しく構築できることが証明できました

では問題の N が奇数の場合です
同様の構築をします
`j \in [0,N)` に対して

- `(ai,bi) = (K+j, K+N+(N/2+j)%N)`
- i は昇順になるように並び替える

実験するとわかるんですが，差が 1 の等差数列になります（びっくり）
明らかに最適なので，終了です
お疲れさまでした

## F

まだ見ぬ世界

### 新しく学んだこと

- C の一番本質的な証明にたどり着いてないのに解法にたどり着いてるの，奇跡
  - 直感はかなりよかったので，それを証明に変える力をつけていきたい
- E ちゃんと証明できたけど，ほぼ奇跡
  - 証明に無限時間かかったので反省