# python library チートシート

## datetime
from datetime import date time datetime

## shutil ファイル操作用標準ライブラリ
shutil.copy("hoge/aaa.txt", "fuga/aaa.txt")
shutil.move("hoge/aaa.txt", "fuga/aaa.txt")
shutil.copytree("hoge/srcdir, "fuga/srcdir")
shutil.rmtree("hoge/srcdir, "fuga/srcdir")

## json JSONデータ処理用ライブラリ

## zipfile ZIPファイルを扱うための標準ライブラリ
files = zipfile.ZipFile('test.zip') # 解凍
zipfile = zipfile.ZipFile('test.zip', mode="w") # 圧縮
zipfile.write("test1.txt") #ファイルを追加

## re 正規表現を扱うモジュール
```
import re
#事前コンパイル
pattern =r"ho"
match_obj= co.match("hoge")

#都度指定
pattern=r"ho"
res=re.match(pattern, "hoge")
```

## pickle
データをシリアライズ
pickle.dumps()  # データをシリアライズ
pickle.loads()  # 復元


