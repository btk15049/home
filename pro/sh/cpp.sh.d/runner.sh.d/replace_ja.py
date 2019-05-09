import sys
import unicodedata

if __name__ == "__main__":
    assert len(sys.argv) == 2

    with open(sys.argv[1]) as target:
        old_code = target.read()
        new_code = ''.join(list(map(lambda c: '#'if unicodedata.east_asian_width(c) in 'FWA' else c, old_code)))
        print(new_code)
