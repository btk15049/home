# KEYENCE Programming Contest 2019 
writer:IH19980412, satashun
## A
こういうやつはソートしたほうが早いってじっちゃんが言ってた

## B
超安全に3乗を回した  
indexどうなるか考えて1割バグるぐらいなら4行追加して100%通るコードを書くという安全策をとれたのはよかった

## C
ソートして貪欲したい気持ちになると貪欲できることがわかる

## D
明らかに考察難易度がEより難しいけど，10分で詰めきった自分を褒めたい  
後ろから順に埋めてくことを考えるとなんかわかる

## E
見た瞬間プリム＋盆栽とわかったのはいいがお前実装遅すぎる

## F
解説を見たら方針と全然違ってびっくりした  
K回の操作のパターン数は,(R+C)!/(R+C-K)! で表される（まずこれがきつい  
また，左下が(i,j)となるような長方形が何回現れるかの期待値を考える．  
すると，K回の操作の内，
* y=jがt回目に現れる確率は1/(R+C)
* y=jがt回目に現れるという条件のもと，xが1,...,t-1回目のいずれかに現れる確率は，(t-1)/(R+C-1)
* 上記条件のもと，左下が(i,j)となる長方形はt,...,K回目に現れる  
  
よって，tを固定した時左下が(i,j)となる長方形が現れる回数は(1/(R+C))*((t-1)/(R+C-1))*(K-t+1)*((R+C)!/(R+C-K)!)で求められ，これはi>0,j>0であれば(i,j)の値によらない

### 新しく学んだこと
* 期待値の線形性を数え上げで使う発想，前にもあったような気がするのでちゃんと道具として取り入れたい
