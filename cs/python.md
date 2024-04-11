# python 文法チートシート

# ライブラリのインポート
import calendar
print(calendar.month(2017.7)) #標準出力はprint()

# ライブラリのインポートその2
from math import pi
print(pi) # from句を使うとモジュール名を省略可

# 変数宣言
a = 1
b = "hoge" #文字列はダブル/シングルクオートどちらでも可
c = 'fuga'
d = True # 真偽値はTrue /False
e = None #いわゆる”null"

# 関数宣言
def my_fnc(val1, val2):
    return val1 + val2

# 関数の呼び出し
ret = my_fnc(a, 999)

# 算術演算子
a = a + 1 # a+=1の表記も可
a = a - 1
a = a * 1
a = a / 1
a = 7 % 3
a = 2 ** 10 #累乗
a = 3 // 2
# a++, a--これらの表記は不可

# 比較演算子(以下の評価はすべてTrueになる)
100 == 100
"hoge" != "fuga"
100 > 99
100 >= 100
99 < 100
100 <= 100
"a" in "abcd"
"z" not in "abcd"
None is None ＃isはオブジェクト比較用の演算子
"hoge" is not None #"not in"と"is not"なので要注意

#論理演算子（以下の評価はすべてTrueになる）
2 > 1 and 2 >= 2
2 > 3 or 2 >= 2
not 2 > 3

# 三項演算子
"hoge" if 2 > 1 else "fuga" #(条件が真の時の値) if (条件) else (条件が偽の時の値）


# 最低限の文字列操作
str = "hoge" + "fuga" #連結
"ab,cd,ef".split(",") #指定した値での分割(List変換）
len("abcd") #文字列長の取得
"a" * 3 #指定した数だけ連結　"aaa"
"abcdef"[2:4] #cd インデックス2から4の前（4-1）までの値を取得
"abcdef"[2:] #cdef インデックス2以降の値を取得
"abcdef"[:5] #abcde インデックス5より前(5-1)までの値を取得

#ヒアドキュメント
"""
シングルクォートでもOK
"""

#raw文字列(見たままの値で扱う文字列)
r"\d+\s\n"
r'\d+\s\n'

#条件分岐
val1 = 1
val2 = 2
if val1 == val2:
    print("hoge")
elif val1 > val2:
    print("fuga")
else:
    print("boo") # boo

if 1 < val2 < 3:
    print("foo")

val3 = 3
if val3 == 1:
    print("hoge")
elif val3 in (2,3):
    print("fuga") #fuga
elif val3 in (3,4)
    print("boo")
else:
    print("piyo")

#繰り返し
val1 = 1
while val1 < 3:
    print(val1) #1,2と順に表示
    val1 += 1

for i in range(2):
    print(i) #0,1と順に表示

#リスト
lst＝「”hoge", 10, True]
print(lst[1] #10
lst[1] = 999
print(lst[1]) #999

#辞書
dict = {"key1": "value1", "key2": "value2", "key3": 3}
print(dict["key"]) #value1

dict["key1"] = "value4"
print(dict["key1"]) #value4

#タプル
tuple1 =("hoge", 999, False)
print(tuple1[1]) #999
#tuple[0] = "boo" #これはNG(タプルは値の変更不可)

#集合
sets1 = {"hoge", 999, True}
print(set1) #{True, "hoge", 999}
#print(set1[0]) #順番を持たないためこれはNG

#クラス
class Member:
    #クラス変数
    LANG="JP"

    #コンストラクタ
    def __init__(self):
    return self.name

    #セッタ
    def setName(self, name):
        self.name = name

taro = Member()
taro.setName("太郎")
print(taro.getName()) #太郎
print(Member.LANG) #JP

#エラーハンドリング
try:
    x = 10 / 0
except Exception as e:
    print(e) #division by zero
else:
#例外が発生しなかった場合に行う処理
    print("hoge")
finally:
    #例外発生有無に関係なく必ず走る処理
    print("fuga") #fuga

try:
    raise Exception("hoge")
except Exception as e:
    print(e) #hoge

# pass
def hogehoge():
    pass   #”pass"は「何もしない」ことを明示する

#クロージャ
def counter():
    count = 0

    def inner_counter():
    nonlocal count
    count += 1
    return count

    return inner_counter
cnt = counter()
print(cnt()) #1
print(cnt()) #2
print(cnt()) #3



