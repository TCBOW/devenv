#! /usr/bin/perl
use warnings;
use strict;

# コマンドラインオプションからキーワードの読み込み
# @ARGV が空だったら｡（カレントディレクトリ）を返して終了
my $keyword = shift @ARGV or (print "." and exit);

# キーワードとディレクトリのハッシュ
my %alist = (
    "raspi" => "tochibow9\@192.168.1.200",
    "18" => "tochibow9\@192.168.122.227",
    "20" => "tochibow9\@192.168.122.71",
    "22" => "tochibow9\@192.168.1.14 -p 22222",
    "kali" => "tochibow9\@192.168.122.41",
);

# キーワードごとの処理
if (exists $alist{"$keyword"} ) {
        # %alist にキーワードとマッチするペア発見
        print $alist{"$keyword"};
}
elsif ($keyword eq "all") {
    # キーワードが "all" だったら %alist の中身を表示
    while (my ($key, $dir) = each %alist) {
        print "$key => $dir\n";
    }
}
else{
    # キーワードにマッチするものが無い場合
    #.(カレントディレクトリ）を返す
    print ".";
}

