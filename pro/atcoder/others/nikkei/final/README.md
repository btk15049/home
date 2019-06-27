# 全国統一プログラミング王決定戦本戦
writer: maroonrk
## A
累積和

## B
vectorの辞書順比較を使うべき，反省

## C
縦横独立二分探索

## D
最後に更新した時刻しか興味が無いため，いもすっぽくやれば終わり

## E
違反したブロックの個数の偶奇で包除原理

## F
(R,C)の辞書順で頂点をソートしたい気持ちになる．ソートした頂点列をP1,P2,...,Pnとする．  
ここで，(Rs,Cs)>(Rt,Ct)なら，S,Tを入れ替えておく．  
P1,...,Pkのみを使ったSから各頂点への最短路が求まっていて，Pk+1を足して各頂点への最短路情報を更新するという方針をとる.このとき，P1,...,Pkの頂点については，Cの値が同じなら同一視できることに気づける．
また，頂点Pk+1を追加するとき，頂点Pk+1=(r,c)へ行く方法を考える．P1,...,Pkの頂点からこの頂点へ行くには，Ci<=cとなる頂点から移動するしかないため，(SからCi<=cとなる頂点への最短距離)＋(Pk+1へ移動するためのコスト)がPk+1へ行く最短路となる．また，Pk+1を集合へ追加したことによる他の頂点への最短路の更新は，よく考えると最後にPk+1から移動するパターンしか存在しないため，Ci<=cとなる頂点への移動コストを(SからPk+1への最短距離)+(Pk+1から移動するためのコスト)に区間更新すればよいことがわかる．
注意点として，区間更新の際，invalidな座標の更新を行わないような注意が必要となる．


## G
初手で重心分解をすればいいことがわかる．重心分解をしたあとは`傾きが単調でない`CHTができれば良いことがわかる．  
ライブラリがなくて困ったが，[神](http://kazuma8128.hatenablog.com/entry/2018/02/28/102130)がいたのでぺたりした．

### 新しく学んだこと
* 単調性のないCHTはセグ木でやったほうが良さそう（定数も考えるとね）
