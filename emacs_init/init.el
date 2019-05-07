(set-frame-font "Monospace" 13)

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
    (list "g++" (list "-DBTK" "-std=c++14" "-fsyntax-only" local-file))))
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


;;if�̒���=���x��
(add-hook 'c-mode-common-hook '(lambda ()(font-lock-add-keywords major-mode '(
									      ("[0-9]+" . font-lock-constant-face)
									      ))))



(add-hook 'c-mode-common-hook (lambda () (highlight-phrase ":")))
(add-hook 'c-mode-common-hook (lambda () (highlight-phrase "\\\.")))
