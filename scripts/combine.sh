#!/bin/bash

# テキストファイルの出力先を指定します
output_file="output.txt"

# 検索するワードを指定します
search_word=ch

# 検索するディレクトリを指定します
search_directory="."

# 指定したディレクトリ内のファイルを検索し、指定したワードを含むファイル名を抽出します
files=$(find "$search_directory" -type f -name "*$search_word*")

# 抽出したファイル名に含まれる数字をソートして小さい順に処理します
for file in $(echo "$files" | sort -V); do
    # 各ファイルをoutput_fileに追記します
    echo "ファイル: $file" >> "$output_file"
    echo "-----------------------------" >> "$output_file"
    cat "$file" >> "$output_file"
    echo "-----------------------------" >> "$output_file"
    echo "" >> "$output_file"
done

echo "処理が完了しました。結果は$output_fileに保存されました。"

