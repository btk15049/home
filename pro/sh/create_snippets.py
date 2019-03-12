import sys
import json
from collections import OrderedDict
import pprint

if __name__ == "__main__":
    assert len(sys.argv) == 2

    code=[]
    try:
        while True:
            code.append(input())
    except EOFError:
        pass

    code[0]="$1"+code[0]

    basename = sys.argv[1].lower()

    tree = {"template":{"prefix":"btk_"+basename,"body":code}}

    with open("../.vscode/cp_"+basename+".code-snippets", 'w') as f:
        json.dump(tree,f, ensure_ascii=False, indent=2)