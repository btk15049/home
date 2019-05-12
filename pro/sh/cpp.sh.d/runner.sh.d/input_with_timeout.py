import signal


def waitKey(sec):
    def timeout(sig, frame): raise RuntimeError('timeout')

    signal.signal(signal.SIGALRM, timeout)
    signal.alarm(sec)
    try:
        key = input()
    except(RuntimeError):
        key = -1
    finally:
        signal.alarm(0)
    return key


if __name__ == "__main__":
    key = waitKey(5)
