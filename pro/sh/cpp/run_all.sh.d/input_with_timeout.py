import sys
import termios
import signal


def wait_type():
    # 標準入力のファイルディスクリプタを取得
    fd = sys.stdin.fileno()
    # fdの端末属性をゲットする
    # oldとnewには同じものが入る。
    # newに変更を加えて、適応する
    # oldは、後で元に戻すため
    old = termios.tcgetattr(fd)
    new = termios.tcgetattr(fd)
    # new[3]はlflags
    # ICANON(カノニカルモードのフラグ)を外す
    new[3] &= ~termios.ICANON
    # ECHO(入力された文字を表示するか否かのフラグ)を外す
    new[3] &= ~termios.ECHO

    ch = 'n'
    try:
        # 書き換えたnewをfdに適応する
        termios.tcsetattr(fd, termios.TCSANOW, new)
        # キーボードから入力を受ける。
        # lfalgsが書き換えられているので、エンターを押さなくても次に進む。echoもしない
        ch = sys.stdin.read(1)

    finally:
        # fdの属性を元に戻す
        # 具体的にはICANONとECHOが元に戻る
        termios.tcsetattr(fd, termios.TCSANOW, old)
        return ch


def wait_input(sec):
    def timeout(sig, frame): raise RuntimeError('timeout')

    signal.signal(signal.SIGALRM, timeout)
    signal.alarm(sec)
    try:
        key = wait_type()
    except(RuntimeError):
        key = 'n'
    finally:
        signal.alarm(0)
    return key


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: input_with_timeput.py <sec>")
        exit(1)
    key = wait_input(int(sys.argv[1]))
    print(key)
