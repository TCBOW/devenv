set fileformats=unix,dos,mac
set fileencodings=utf-8,sjis,cp932,utf-16le

syntax enable
filetype plugin indent on

colorscheme slate
set laststatus=2
set ruler
set showmode
set showcmd
set number
set hidden
set wildmenu
set iminsert=0
set hlsearch
set autoindent

set noundofile
set backup
set noswapfile

if (has('win32') || has('win64'))
	set backupdir=$TEMP
else
	set backupdir=/tmp
endif

" ------------ インデント
" デフォルトで4
" ruby, clojure, markdownなら2
" タブはスペースに展開
set shiftwidth=0 softtabstop=0 tabstop=4 expandtab
augroup vimrc_tab
    autocmd!
    autocmd FileType ruby setlocal tabstop=2
    autocmd FileType clojure setlocal tabstop=2
    autocmd FileType markdown setlocal tabstop=2
augroup END
let g:vim_indent_cont=8
set textwidth=0

" ------------ 検索
" デフォルトはmagicモード
set magic

" デフォルトは大文字小文字を無視
set ignorecase

" 賢く大文字小文字を区別
set smartcase

" インクリメンタルサーチ
set incsearch

" すべてのマッチ箇所をハイライト
set hlsearch

" ファイル端に達しても、一周して検索を続行
set wrapscan

" ------------ スペルチェック
" 英語
set spelllang=en,cjk
" デフォルトでOFF
set nospell


" ------------ Vimが自動的に作るファイル
" アンドゥ履歴ファイルを作らない
set noundofile
" バックアップファイルを作る
set backup
" Swapファイル(自動保存ファイル)を作らない
set noswapfile
" バックアップファイルの置き場
if ( has('win32') || has('win64') )
    set backupdir=$TEMP
else
    set backupdir=/tmp
endif

" ------------ その他のオプション
" 未保存のバッファが隠れるのを許す
set hidden

" 挿入モード時のIME制御(0: IME OFF)
set iminsert=0

" 自動インデント
set autoindent

" <C-a>や<C-x>の対応基数
set nrformats-=octal

" 自動改行(0: しない)
set textwidth=0

" ------------ カーソル移動
nnoremap k gk
nnoremap j gj
nnoremap gk k
nnoremap gj j
xnoremap k gk
xnoremap j gj
xnoremap gk k
xnoremap gj j

"------------ スペルチェック
function! s:toggleSyntax()
    if exists("g:syntax_on")
        syntax off
    else
        syntax enable
    endif
endfunction
nnoremap <Leader>s :set invspell<CR>:call <SID>toggleSyntax()<CR>

" ------------ コピペ
set pastetoggle=<F2>
inoremap <C-g><C-v> <F2><C-r>"<F2>

" ------------ コマンドラインモード
cnoremap <expr> %% getcmdtype()==':' ? expand('%:p:h').'/' : '%%'

" ------------ EasyMotion
let g:EasyMotion_do_mapping=0
nmap <C-f> <Plug>(easymotion-overwin-f)

" ------------ BufExplorer
let g:bufExplorerShowDirectories=0
let g:bufExplorerShowUnlisted=0
let g:bufExplorerSortBy='fullpath'
nnoremap <Leader>l :BufExplorerHorizontalSplit<CR>

" ------------ TagBar
nnoremap <Leader>t :TagbarOpenAutoClose<CR>
nnoremap <Leader>T :echo tagbar#currenttag('[%s]', 'No tags')<CR>

" ------------ 無視
nnoremap q: <Nop>



" ------------ 環境独自の設定ファイル ------------
if filereadable(expand("~/.vimrc.local"))
    source ~/.vimrc.local
endif
"nnoremap s <Nop>
"nnoremap sj <C-w>j
"nnoremap sk <C-w>k
"nnoremap sl <C-w>l
"nnoremap sh <C-w>h
"nnoremap sJ <C-w>J
"nnoremap sK <C-w>K
"nnoremap sL <C-w>L
"nnoremap sH <C-w>H
"nnoremap sn gt
"nnoremap sp gT
"nnoremap sr <C-w>r
"nnoremap s= <C-w>=
"nnoremap sw <C-w>w
"nnoremap so <C-w>_<C-w>|
"nnoremap sO <C-w>=
"nnoremap sN :<C-u>bn<CR>
"nnoremap sP :<C-u>bp<CR>
"nnoremap st :<C-u>tabnew<CR>
"nnoremap sT :<C-u>Unite tab<CR>
"nnoremap ss :<C-u>sp<CR>
"nnoremap sv :<C-u>vs<CR>
"nnoremap sq :<C-u>q<CR>
"nnoremap sQ :<C-u>bd<CR>
"nnoremap sb :<C-u>Unite buffer_tab -buffer-name=file<CR>
"nnoremap sB :<C-u>Unite buffer -buffer-name=file<CR>



"" Vundleの設定
"set rtp+=~/.vim/bundle/Vundle.vim
"" 開始
"call vundle#begin()
"Plugin 'gmarik/Vundle.vim'
"call vundle#end()
" 終了

"augroup vimrc
"	autocmd!
"	autocmd FileType vim setlocal
"keywordprg=:help
"augroup END
let mapleader=","
nnoremap \ ,
nnoremap <Leader>git :e ${HOME}/git/devenv/dotfiles/cs/gitcs.md
nnoremap <Leader>python :e ${HOME}/git/devenv/dotfiles/cs/python.md
nnoremap <Leader>vim :e ${HOME}/git/devenv/dotfiles/cs/vimcs.md
nnoremap <Leader>etc :e ${HOME}/git/devenv/dotfiles/cs/etccs.md
nnoremap <Leader>asm :e ${HOME}/git/devenv/dotfiles/cs/asm.md
nnoremap <Leader>yocto :e ${HOME}/git/devenv/dotfiles/cs/yocto.md
nnoremap <Leader>yaml :e ${HOME}/git/devenv/dotfiles/cs/yaml.md
nnoremap <Leader>sh :e ${HOME}/git/devenv/dotfiles/cs/shell.md
nnoremap <Leader>sec :e ${HOME}/git/devenv/dotfiles/cs/security.md
nnoremap <Leader>ros :e ${HOME}/git/devenv/dotfiles/cs/ros.md
nnoremap <Leader>gcc :e ${HOME}/git/devenv/dotfiles/cs/gcc.md
nnoremap <Leader>make :e ${HOME}/git/devenv/dotfiles/cs/make.md
nnoremap <Leader>gdb :e ${HOME}/git/devenv/dotfiles/cs/gdb.cs
nnoremap <Leader>net :e ${HOME}/git/devenv/dotfiles/cs/net.cs
nnoremap <Leader>c :e ${HOME}/git/devenv/dotfiles/cs/c.md
nnoremap <Leader>hack :e ${HOME}/git/devenv/dotfiles/cs/hack.md
nnoremap <Leader>kvm :e ${HOME}/git/devenv/dotfiles/cs/kvm.md
 
" ------------ 検索
nnoremap <Leader>gg :vim //j <C-r>=expand('%:h').'/**'<CR> <CR>:copen 8<CR><C-w>J
nnoremap <Leader>gG :vim //j <C-r>=expand('%:h').'/../**'<CR> <CR>:copen 8<CR><C-w>J
nnoremap <Leader>q :copen 8<CR>
nnoremap <C-l> :nohlsearch<CR><C-l>

" ------------ 折り畳み
nnoremap <Space> zA

let g:copilot_enablled=v:false
" プラグイン追加
" "Plugin 'joonty/vdebug.git'
