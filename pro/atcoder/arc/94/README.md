# AtCoder Regular Contest 94
writer: Degwer
## C
最終的な値をDとする．エスパーをすると，「D>max(A,B,C)かつ3D-A-B-Cが偶数」なら達成可能なので，それを満たす最小のDをもってくる．
## D
第一の考察として，「k位の人を選んでいるのにk-1位の人を選ばない」というのは無駄なので，高橋君よりもスコアが小さい人がN人いた場合は，各順位が高橋君を除いた順位の高い（小さい）N人であると仮定してよい．  
また，二つの集合をマッチングさせたときに積を最小化させる方法は，片方を昇順に，もう片方を降順に並べてマッチングさせるのが最適である．今回の場合は値の変化が（ほぼ）1ずつなので，真ん中付近が積の最大値であることがわかる．よって，真ん中付近50個ぐらいを調べてやると積の最大値が見つかる．  
したがって，Nを二分探索をして真ん中付近を調べて判定を行うと通る．
## E
先行はA[i]>B[i]となる部分を放置でき，それ以外を全部0にすることが可能である．よって，どこを放置するかを調べてやるだけ．
## F
変化させても総和のmod3の値が変わらない．また，変化後はどこか一部分の連続してるところが同じ値になる．
なんか手元で実験するとほとんどのケースで上を満たす文字列が作れそうな気がしてくるが，サンプル1で爆死する．  
なんかnが大きいときは上の予想が当たるらしいため，30回ぐらい変化させてみてこれ以上変化できなくなったらその値，まだ変化するなら全部作れるのでDPで求める．
### 新しく学んだこと
* 手元で実験して予想を立てたら実験コードを書きましょう

