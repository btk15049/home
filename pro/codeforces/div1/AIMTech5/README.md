# Codeforces AIMTech Round 5(div1+2)
## A
うん

## B
好き．足して1000000000....を作るようにすれば絶対できる

## C
両端から累積和みたいに最悪をする

## D
buy側の集合，sell側の集合，未確定部分の集合みたいな感じにしてシミュレートをする．
ACCEPTされるのはbuy側の末尾，sell側の先頭，未確定部分のいずれかになって，ACCEPTされた瞬間未確定部分の要素は全てbuy,sellが確定する．  
最後に未確定部分を割り振ることを忘れない．

## E
bが0以外の要素で統一されていたら不可能．  
（証明）aが全て同じ値なら,bの要素は全て0. そうでないなら，`a[i]<a[i+1]`が成り立つiについて`a[i]=b[i]`が成り立つ．全ての要素がcで統一されていたとき，a[i]=b[i]=cとなる要素が存在するはずなので，a[i-1]%a[i]=a[i-1]%c!=cとなることから，不可能．  
逆に，`a[i]<a[i+1]`となるiが存在するときは，a[i+1]=b[i+1]としてあげて，a[i],a[i-1],...,a[i+2]を順番にいい感じに決めてやれば良い


### 新しく学んだこと
* この回は問題文がCSAみたいで最高だった
