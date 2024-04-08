# yaml チートシート

YAML はあくまで「仕様」であり、それを処理するライブラリの「実装」が必要。
YAML では、主に次の 3 つの組み合わせでデータを表現する。

* 配列
* ハッシュ
* スカラー（文字列、数値、真偽値など）

## リファレンス
https://magazine.rubyist.net/articles/0009/0009-YAML.html#yaml-について

---
# 配列 (シーケンス）

```
- aaa
- bbb
- ccc
```

Ruby用　YAML.loadはYAMLデータをRubyオブジェクトに変換するメソッド
配列をネストさせるには半角スペースでインデントすればネストする。
```
- aaa
-
  - b1
  - b2
  -
    - b3.1
    - b3.2
- ccc
```


# ハッシュ (マッピング）

* シンタックス

```
A: aaa
B: bbb
C: ccc
```

* 実行結果
```
{"A"=>"aaa", "B"=>"bbb", "C"=>"ccc"}
```


配列とハッシュはネストさせることも可能。

```
- name:  Hanako
  email: flower@mail.com
- name:  Sumire
  email: garnet@mail.net
- name:  Momoko
  email: peach@mail.org
```

### フロースタイル
* 前記シンタックスはブロックスタイルといいこれ以外にも {}や[]で記述する方法をフロースタイルという。

# スカラーとデータ型
配列やハッシュのような他のデータを要素としてもつデータはコレクションという。
それ以外のデータはスカラーといい、YAMLではデータ型を自動的に判別する。

```
decimal1:  123                           # 整数 (10 進数)
decimal2:  1,234,567,890                 # 整数 (10 進数)
octal:     0644                          # 整数 (8 進数)
hexa:      0xFF                          # 整数 (16 進数)
float1:    0.05                          # 浮動小数点
bool1:     true                          # 真
bool2:     yes                           # 真
bool3:     on                            # 真
bool4:     false                         # 偽
bool5:     no                            # 偽
bool6:     off                           # 偽
null1:     ~                             # Null 値
null2:     null                          # Null 値
date:      2005-01-01                    # 日付
stamp:     2005-01-01 00:00:00 +09:00    # タイムスタンプ
str1:      'true'                        # 文字列
str2:      "2005"                        # 文字列
symbol:    :foo                          # シンボル (Syck の独自機能)
```
また、「！」を使うとデータ型を明示できに指定できる。言語依存の型も指定可能。
```
- !str 123            # 文字列
- !pairs              # 組 (要素が 2 つの配列)
  - A: aaa
  - B: bbb
- !ruby/sym  foo      # Ruby の Symbol
- !ruby/regexp /^$/   # Ruby の Regexp
```


# アンカーとエイリアス
データに&nameをつけることでポインタのように*name参照することもできる。
```
- &mark foo
- bar
- *mark
- *mark
```

これは下記Rubyスクリプトと同義

```
mark = foo
{ "A"=>mark, "B"=>"bar", "C"=>mark }
```

