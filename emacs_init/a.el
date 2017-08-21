
;;文字色とかテーマの設定っぽい
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(ansi-color-faces-vector
   [default default default italic underline success warning error])
 '(custom-enabled-themes (quote (tango-dark))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:family "Verdana" :foundry "outline" :slant normal :weight normal :height 140 :width normal))))
 '(hi-yellow ((t (:background "gray20" :foreground "snow"))))
 '(highlight ((t (:background "SteelBlue4" :foreground "snow")))))

(set-frame-font "Monospace" 14)

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
    (list "g++" (list  "-std=c++11" "-fsyntax-only" local-file))))
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

;;多分背景の設定
(if window-system (progn
    (set-background-color "Black")
    (set-foreground-color "LightGray")
    (set-cursor-color "Gray")
    (set-frame-size (selected-frame) 80 30 nil)
    (set-frame-parameter nil 'alpha 80) ;透明度
    ))


;;ifの中の=を警告
(add-hook 'c-mode-common-hook '(lambda ()(font-lock-add-keywords major-mode '(
  ("[0-9]+" . font-lock-constant-face)
  ))))



(add-hook 'c-mode-common-hook (lambda () (highlight-phrase ":")))
(add-hook 'c-mode-common-hook (lambda () (highlight-phrase "\\\.")))
