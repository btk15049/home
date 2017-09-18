# 今更聞けない競技プログラミングのC++  

## はじめに  
これはC言語を大学で学んで競技プログラミングをC++で始める方のためのドキュメントです  

## 初級編  
#### コンパイル方法（gcc）

```shell-session
$ g++ btk.cpp -o btk
```

gcc4.9以降なら以下を使うことを推奨します（そもそも4.9以降を推奨します）


```shell-session
$ g++ btk.cpp -o btk -std=c++11
```
#### 入力

※``include<iostream>``が必要
* 整数  

```
int n;
std::cin >> n;
```

* 文字列  

```
std::string s;
std::cin >> s;
```

* 複数  

```
int n;
std::string s;
std::cin >> n >> s;
```

#### 出力

※``include<iostream>``が必要
* 整数  

```
int n = 1;
std::cout << n;
```

* 文字列  

```
std::string s = "btk";
std::cout << s;
```

* 複数  

```
int n = 10;
std::string s = "cul";
std::cout << n << s;
```

* 空白、改行  

```
std::cout << " "; //空白
std::cout << "\n";//改行
std::cout << std::endl;//改行+flush
```

#### bool  
C++からbool型が提供されている（それまでは0がfalse,0以外がtrue）  
※実はC99からC言語でもboolは使える（stdbool.h）


#### using namespace std  
C++では、名前空間というスコープを管理するための記法を導入している.  
今回説明するC++の標準ライブラリはstd空間に属しているため、``std::``を付与する必要がある.  
しかし、プログラムの先頭に``using namespace std;``と書くと、「std空間を使うよ！」という合図になるので、``std::``を以降書かなくてよくなる.  
競技プログラミングで書かない理由はあまりないので積極的に使っていきましょう.  

## 中級編  
#### std::string  
C言語では、文字列を扱う場合はchar型の配列で扱うことにより文字列を管理していた.  
C++では、内部的には同じだが、もう少し安全かつ便利に文字列を扱うことができるようになる.  

```
string s="a";
cout << s << endl; //a
s += "bc";
cout << s << endl; //abc
s += 'd';
cout << s << endl; //abcd

/* 文字列長を取得 */
cout << s.size() << endl; // 4

/* 0文字目（先頭）を取得 */
cout << s[0] << endl; //a (char型)
cout << s.front() << endl; //a (char型)

/* 最後の文字を取得 */
cout << s[s.size()-1] << endl; //d (char型)
cout << s.back() << endl; //d (char型)
```

#### テンプレートクラス
ここから紹介するクラスはテンプレートクラスといって，様々な型(int,double)とかに対応している．  
宣言方法がちょっと特殊なので紹介．  
コンパイル時にコンパイラが動的に判別してそれ用の型を作ってくれる．

```
/* list<T> */

// int型の要素をもつlistを生成
list<int> a;

// double型の要素をもつlistを生成
list<double> b;

```

#### std::vector< T >
C言語では、動的に配列を確保するときはmallocやcalloc,freeなどポインタを駆使していた.  
もちろんバグも生まれるしメモリの開放を自分でしなければならないので思考の邪魔になってしまう.  
C++では、動的な配列を扱うクラスをstd::vectorという形で提供している.  

* 宣言  

```
vector<int> a; //サイズ0のint型配列
vector<int> b(5); //サイズ5のint型配列
vector<int> c(5,7); //サイズ5で全要素が7のint型配列
vector<int> d={1,3,5}; //サイズ3で要素が1,3,5のint型配列
```

* 要素参照  

```
/* 先頭要素にアクセス */
a.front();

/* 3番目の要素にアクセス */
a.at(3); //配列外参照のチェックあり
a[3]; //配列外参照のチェックなし

/* 末尾要素にアクセス */
a.back();
```

* push_back
末尾に要素を追加できる.  
n要素を追加するときの、追加に要する全体の計算量はO(n)  

```
vector<int> a = {0,1,2,3};
a.push_back(4); // 0,1,2,3,4
```

※pop_backは末尾削除、push_back()の逆  
※push_front,pop_frontもあるがO(n)かかるので非推奨  

* copy

```
vector<int> a;
vector<int> b = {1,2,3};
a=b; //aにbのコピーを代入
```

#### std::stack< T >
いわゆるスタック.vectorみたいに動的に要素を確保してくれる.  
* top  
最後に追加した要素の取得  
* push  
要素追加
* pop  
最後に追加した要素の削除  
* size  

#### std::queue< T >
いわゆるキュー.vectorみたいに動的に要素を確保してくれる.  
* front  
最初に追加した要素の取得,stackと要素名が違うので注意.  
* push  
要素追加
* pop  
要素
* size  

#### std::pair< S , T >
簡単にいえば2つの要素を持つ構造体．  
無理に使う必要はないけど他のライブラリ内で使われてたりするので知識として知っておく必要はある．  
* first  
S型の要素  
* second  
T型の要素  

pairは比較可能なので，ソートとかができて使えると色々嬉しい（first,secondの順に評価する）


#### std::set< T > 
set(集合)クラス  
値の挿入削除検索を対数時間で行える.  
内部実装が平衡二分探索木なので、値は比較できるもの（intやstring）でないとダメ.  
* insert(v)  
値vを挿入する．同じ要素がある場合には何もしない  
* count(v)  
setにvが含まれるなら1,そうでないなら0を返す．  
* erase(v)  
vを消す．vが無いときはちょっと怖いので先にcountで判別をしましょう．  
* lower_bound(v)  
v以上の値でsetに含まれる最小のものを返す．イテレータとか出てきてちょっと複雑なのでここでは紹介だけ．
* size()

#### std::map< S , T >
平衡二分探索木のキーと値を持ったやつ．疑似的な配列みたいな使い方ができる．  
内部実装が平衡二分探索木なので、キーは比較できるもの（intやstring）でないとダメ.
* []
配列みたいに[]で参照できる．が，かなり注意が必要．  
存在しない要素に[]でアクセスした場合はTの初期値で初期化される．  

```
/*stringをキー */
std::map<std::string,double> m;

std::cout<< m.size() << std::endl; // 0
std::cout<< m["btk"] << std::endl; // 0.0(double)
std::cout<< m.size() << std::endl; // 1

m["btk"] = 1.0;
std::cout<< m["btk"] << std::endl; // 1.0(double)
std::cout<< m.size() << std::endl; // 1
```

* count(v)  
mapにキーをvとする要素が含まれるなら1,そうでないなら0を返す．  
* erase(v)  
キーvの要素を消す．無いときはちょっと怖いので先にcountで判別をしましょう．  
* lower_bound(v)  
キーがv以上の値でmapに含まれる最小のものを返す．イテレータとか出てきてちょっと複雑なのでここでは紹介だけ．  
* size()

#### include<algorithm>
意味合い的にはsort以外はutilの方が正しそう．

* std::sort  
普通の配列やvectorをソートできる.内部実装はIntroソートだった気がする（クイックとヒープを組み合わせた安定ソート）  

```
int a[10];
std::vector<int> b(10);

/* 配列の最初と最後を引数に与えるとソートしてくれる */
sort(a,a+10);
sort(b.begin(),b.end());
```

* std::reverse  
配列の中身をひっくり返してくれる．``std::sort``は昇順にソートするので降順にしたいときはsortしたあとこれを使うとよい．  
引数は``std::``sortと一緒  

#### ありがちなミス  
大体のデータ構造のクラスには個数を取得する``size()``が存在するが，戻り値の型は``size_t``でほとんどの環境で``unsigned``であるため注意．

```
std::vector<int> v;
std::cout << v.size()-1 << std::endl; //オーバーフローが発生する
```

## 上級編
#### vectorのテク
* swap  
vector同士のswapはO(1)

* assign  
要素の再割当てみたいなことができる  
使ってる領域を再利用するので少し効率がよい  

```
vector<int> v={1,2,3};

/* 以下の2式は等価 */
v = vector<int>(5,1);
v.assign(5,1);
```
* vectorには比較関数が定義されている  
辞書順比較をしてくれる  

```
vector<int> a={1,2,3};
vector<int> b={1,2,3,4};
a<b //true
vector<int> a={1,2,1};
vector<int> b={1,1,2};
a>b //true

/* ==や!=もあるよ */
```


#### std::tuple  
pairを2要素から複数要素にしたver  
``tuple<int,double,string>``みたいに使う．  
pairと同じく辞書順比較してくれるので便利  
値の取得方法がかなり特殊  

```

std::tuple<int,std::string,double> t = {1,"btk",2.0};

/* get<i> を使う場合 (iは定数でないとダメ) */
std::cout << std::get<0>(t) << endl; //1(int)
std::cout << std::get<1>(t) << endl; //btk(string)
std::cout << std::get<2>(t) << endl; //2.0(double)

/* tieを使う場合 */
int a;
std::string b;
double c;
std::tie(a,b,c) = t; //a,b,cにそれぞれ値が格納される
```

#### auto
C++ではコンパイル時の型推論的なものができる．  
autoを型宣言の部分に書くとコンパイル時に勝手に判別してくれる．


```
std::vectro<int> v = {1,2,3};
auto u = v; //vをコピー
```


#### lower_bound,upper_bound
二分探索をする関数が存在する．配列の場合にはポインタ，vectorの場合にはイテレータが返ってくる．  
std::distanceと組み合わせると配列の何番目かが取得できたりする．  
絶対に忘れてはいけない注意点として，set,mapにはstd::lower_bound,upper_boundではなくメンバ関数のlower_bound,upper_boundを使うこと（計算量がO(N)になってしまう）  
* lower_bound  
v以上の最小の値のアドレスを返す．
* upper_bound
vより大きい最小の値のアドレスを返す．


```
std::vector<int> v = {1,2,3,4};
auto l = std::lower_bound(v.begin(),v.end(),2)//戻り値がクッソ面倒なのでautoで受け取ることを推奨
auto u = std::upper_bound(v.begin(),v.end(),2)//戻り値がクッソ面倒なのでautoで受け取ることを推奨

std::cout << *l << std::endl; //2
std::cout << *u << std::endl; //3

std::cout << std::distance(v.begin(),l) << std::endl; //1
std::cout << std::distance(v.begin(),u) << std::endl; //2
```

#### std::iota
配列と初期値を与えると配列を初期値から始まる連番で初期化してくれる，
```
std::vector<int> v(5);
std::iota(v.begin(),v.end(),1); //{1,2,3,4,5}
std::iota(v.begin(),v.end(),0); //{0,1,2,3,4}


```

#### std::next_permutation  
順列を与えると辞書順で次の順列に進める．戻り値はboolで辞書順で最も大きい順列を与えた場合はfalseが返る．なので，以下のような運用が可能.  

```
/*iotaを用いて順列{1,2,3,4,5}を生成*/
std::vector<int> v(5);
std::iota(v.begin(),v.end(),1);

/* {1,2,3,4,5}からなる順列の全列挙 */
do{
 /*順列に対する処理*/
}while(v.begin(),v.end());

```

順列列挙に対する計算量は``O(N!)``なので安心して使ってよい．

#### ラムダ式
関数内に関数を埋め込める便利な奴．  
説明すると長いので競技に使えそうなのは[ここ](http://snuke.hatenablog.com/entry/2015/12/06/005054)に載ってます
