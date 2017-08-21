
;;�����F�Ƃ��e�[�}�̐ݒ���ۂ�
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

;;�s�ԍ���\������ݒ�Ƃ��̕��̒���
(global-linum-mode t)
(setq linum-format "%3d ")

;;�����o�b�N�A�b�v�t�@�C�������Ȃ�����ݒ�
(setq make-backup-files nil)

;;����flymake�̐ݒ�
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

;;�����X�^�[�g���̃��b�Z�[�W�������ݒ�
(setq inhibit-startup-message t)

;;�����X�y�[�X�̃I�t�Z�b�g��4�ɂ���ݒ�
(setq c-basic-offset 4)

;;�����C���f���g���^�u�ł͂Ȃ��X�y�[�X�ɂ���ݒ�
(setq-default indent-tabs-mode nil)

;;����������Ȃ��Ȃ�ݒ�
(setq ring-bell-function 'ignore)

;;�����w�i�̐ݒ�
(if window-system (progn
    (set-background-color "Black")
    (set-foreground-color "LightGray")
    (set-cursor-color "Gray")
    (set-frame-size (selected-frame) 80 30 nil)
    (set-frame-parameter nil 'alpha 80) ;�����x
    ))


;;if�̒���=���x��
(add-hook 'c-mode-common-hook '(lambda ()(font-lock-add-keywords major-mode '(
  ("[0-9]+" . font-lock-constant-face)
  ))))



(add-hook 'c-mode-common-hook (lambda () (highlight-phrase ":")))
(add-hook 'c-mode-common-hook (lambda () (highlight-phrase "\\\.")))
