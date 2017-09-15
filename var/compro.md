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

#### std::vector  
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

#### stack
いわゆるスタック.vectorみたいに動的に要素を確保してくれる.
* top()
最後に追加した要素の取得
* push  
要素追加
* pop  
最後に追加した要素の削除
* size()  

#### queue
いわゆるキュー.vectorみたいに動的に要素を確保してくれる.
* front()
最初に追加した要素の取得,stackと要素名が違うので注意.
* push  
要素追加
* pop  
要素
* size()  

#### pair

#### set 
set(集合)クラス  
値の挿入削除検索を対数時間で行える.  
内部実装が平衡二分探索木なので、値は比較できるもの（int,string）でないとダメ.


#### map





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


#### tuple  

#### auto

#### lower_bound,upper_bound

#### iota

#### next_permutation

#### ラムダ式
