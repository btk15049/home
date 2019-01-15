# 競プロ用ライブラリ
ここにはverifyした問題とかを載せています．  
自由に使って構いませんが動作は保証しませんのでこのライブラリのせいでレートが落ちたとしても一切責任は負いません．

## 文字列系
* KMP.hpp  
最小周期の取得 : ARC77 F  
* RollHash.cpp  
ロリハ : CSA12
* ZAlgorithm.cpp  
Z algorithm : みんプロ2018本選 D

## 数論系
* Modulo.cpp  
p^n modでのnCk : ICL2015Finals(CF) J  

## グラフ
* CentroidDecomposition.cpp  
木の重心分解 : ICL2015Finals(CF) D , CF190 d1C  
重心分解を使ったパスの列挙的なhoge : みんプロ2018本戦 C
* HeavyLightDecomposition.cpp  
HL分解 : yukicoder No529  
* TwoVertex.cpp  
関節点列挙，二重頂点連結成分分解，block cut tree : ECR42 F , AOJ 関節点
* LowestCommonAncestor.cpp  
ダブリング使ったLCA，頂点rを根とする頂点uvのLCAも算出できる

## セグメント木
* SegTree.cpp
* AbstractSegmentTree.cpp  
抽象化セグ木 : RUPC2018 day2 J(遅延),K

## スパーステーブル
* StaticRMQ.cpp  
静的RMQを処理するデータ構造 : ICPC2017模擬地区予選F, CodeChef FRMQ ,CF ECR41 F  
SparseTable : メモリ気にしなくていいならこっち  
RMQ : 空間O(n)，構築O(n)．内部はブロックサイズ16のブロック分割(スパーステーブル+サイズ4の平方分割)

## 永続
* PersittentTrie.cpp  
永続トライ木（配列） : CF457 E

## 平方分割テンプレート
* QuadrasticDivision.cpp

## 自前ヒープ
* IntervalHeap.cpp  
最小値最大値両方使える

## 累積和
* RectangleSum.cpp  
二次元累積和 : ARC089 D

## その他
* Polyomino.cpp
サイズkのポリオミノの列挙 : SRM652 Div1 Med


