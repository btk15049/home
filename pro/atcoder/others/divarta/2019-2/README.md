# diverta 2019 Programming Contest 2

writer: satashun, yuma000, E869120, square1001

## A

N=1 に気をつけよう

## B

結構めんどくさくて面倒実装をしてしまった

## C

最初正負が半分半分になると勘違いして WA を重ねてしまった．
サンプルが優しくないので，サンプルを読んで疑う心を強めていきたい．

## D

実家のような DP．
更新微妙にミスったのはダメ．

## E

一番大きい値が一つだけ飛び抜けてる状態を考えて，i 本一番大きいやつと同じにして最後尾のやつを上に飛び抜けさせるみたいな思考をすると AC

## F

任意の頂点 v について，ハミルトン路に現れる v の隣接辺は 1 本または 2 本になる．
そこで，頂点 v から出る辺のコストを[1, 2, 4, 7, 12, 20, 29, 38, 52]とすると，1 または 2 本選ぶときのコストが distinct になる．この数列は魔術をして生み出す．
これを使って n 進数テクみたいなノリでやると，1.6\*10^11 ぐらいになる（ダメ）
だけど，数列をちょっといじるとコストが小さくなって何故かうまくいく（魔術）．
まあ高々 2 本って言っても，合計が 9 本しかないあたりでかなり効いてそう

### 新しく学んだこと

- E に行くべきだった気もする
