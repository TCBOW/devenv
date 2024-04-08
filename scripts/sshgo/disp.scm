#! /opt/local/bin/gosh
 
;; Scheme(Gauche)では main という名前の関数が
;; このスクリプトの呼び出し時に実行される
;; ちなみにコマンドラインオプション（キーワード）は
;; リスト args の cdr 部に格納されている
(define (main args)
 (cond  [(null? (cdr args)) (format #t "~a" ".")] ;; キーワードが空だったらカレントディレクトリを返す
        [(equal? (cadr args) "all") (disp-all *alist*)] ;; キーワードが "all" だったら *alist* をそのまま表示
                 [else (disp (cdr args))])) ;; キーワードにひも付けされていディレクトリを返す
;;                   
;; *alist* からキーワードと紐付いているディレクトリを探し出す関数
    (define (disp args)
        (cond    [(null? args) (format #t "~a" ".")]
            [(pair? args) (cond  [(assoc (car args) *alist*) 
            (format #t "~a" (cdr (assoc (car args) *alist*)))]
            [else (disp (cdr args))])]))

;; *alist* をそのまま表示する関数
    (define (disp-all alst)
    (cond  [(null? alst) #f]
        [else (and (print (car alst)) (disp-all (cdr alst)))]))

;; これが *alist* 本体
;; (key . dir) のペアを必要なだけ登録しておく
;; 後から追加したければこの *alist* に追加すればいい
;; ※以下は単なる例です。
(define *alist* 
    '(("dropbox" . "/Users/user_name/Dropbox") 
    ("works" . "/Users/user_name/dir/works")
    ("blog" . "/Users/user_name/Documents/blog")
    ("dl" . "/Users/user_name/Downloads")
    )
)
