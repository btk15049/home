(global-linum-mode t)
(setq linum-format "%3d ")
(setq make-backup-files nil)
(setq inhibit-startup-message t)
(setq c-basic-offset 4)
(setq-default indent-tabs-mode nil)
(setq ring-bell-function 'ignore)
(add-hook 'c-mode-common-hook (lambda () (highlight-phrase ":")))
(add-hook 'c-mode-common-hook (lambda () (highlight-phrase "\\\.")))
(set-frame-font "Monospace" 13)
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

(if window-system (progn (set-frame-parameter nil 'alpha 60)))