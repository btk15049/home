(set-frame-font "Monospace" 13)

;;行番号を表示する設定とその幅の調整
(global-linum-mode t)
(setq linum-format "%3d ")

;;多分バックアップファイルを作らなくする設定
(setq make-backup-files nil)

;;多分flymakeの設定
(require 'flymake)
(defun flymake-cc-init ()
  (let* ((temp-file   (flymake-init-create-temp-buffer-copy
                       'flymake-create-temp-inplace))
         (local-file  (file-relative-name
                       temp-file
                       (file-name-directory buffer-file-name))))
    (list "g++" (list "-DBTK" "-std=c++14" "-fsyntax-only" local-file))))
(push '("\\.cpp$" flymake-cc-init) flymake-allowed-file-name-masks)
(add-hook 'c++-mode-hook
          '(lambda ()
             (flymake-mode t)))

;;多分スタート時のメッセージを消す設定
(setq inhibit-startup-message t)

;;多分スペースのオフセットを4個にする設定
(setq c-basic-offset 4)

;;多分インデントをタブではなくスペースにする設定
(setq-default indent-tabs-mode nil)

;;多分音が鳴らなくなる設定
(setq ring-bell-function 'ignore)


;;ifの中の=を警告
(add-hook 'c-mode-common-hook '(lambda ()(font-lock-add-keywords major-mode '(
									      ("[0-9]+" . font-lock-constant-face)
									      ))))



(add-hook 'c-mode-common-hook (lambda () (highlight-phrase ":")))
(add-hook 'c-mode-common-hook (lambda () (highlight-phrase "\\\.")))
