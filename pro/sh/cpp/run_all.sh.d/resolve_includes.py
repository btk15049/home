#!/usr/local/bin/python3
# -*- coding: utf-8 -*-

import sys
from queue import LifoQueue
import re

# "#"+<空白0文字以上>+"include"+<空白1文字以上>+"<"+<file名>+">"
# 空白はタブも含む
pattern = r'[\s]*#[\s]*include[\s]*\"([^\"]+)\"'

# 事前に正規表現のパターンをコンパイル
matcher = re.compile(pattern)

lib_path = ''
bs = '/*<stl>*/'
es = '/*</stl>*/'
bh = '/*<head>*/'
eh = '/*</head>*/'
bb = '/*<body>*/'
eb = '/*</body>*/'


# pathから改行を区切りにしてsplitした文字列の配列を取得
def get_contents(path):
    contents = []
    with open(path) as f:
        contents = f.readlines()
    for i in range(len(contents)):
        contents[i] = contents[i].strip()
    return contents


def begin_header(contents, word):
    if word not in contents:
        return 0
    else:
        return contents.index(word)


def end_header(contents, word):
    if word not in contents:
        return 0
    else:
        return contents.index(word)+1


def get_library(include_line):
    inner = matcher.search(include_line).group(1)
    inner = lib_path + inner
    return inner


def is_include_line(line):
    if matcher.search(line):
        return True
    else:
        return False


def get_includes(path):
    contents = get_contents(path)
    raw_lines = contents[begin_header(
        contents, bh)+1:end_header(contents, eh)-1]
    includes = [get_library(s) for s in raw_lines if is_include_line(s)]
    print(path+':', file=sys.stderr)
    for s in includes:
        print(' - '+s, file=sys.stderr)
    return includes


graph = dict()
visited = dict()
resolved_includes = []


def dfs(v):
    if visited[v] == False:
        visited[v] = True
        for u in graph[v]:
            dfs(u)
        resolved_includes.append(v)


def get_inner_code(path):
    contents = get_contents(path)
    return contents[:begin_header(contents, bs)] + contents[end_header(contents, es): begin_header(contents, bh)] + contents[end_header(contents, eh):]


def get_stl(path):
    contents = get_contents(path)
    return contents[begin_header(contents, bs):end_header(contents, es)]


if __name__ == "__main__":
    code_path = sys.argv[1]
    lib_path = sys.argv[2]
    if lib_path[-1] != '/':
        lib_path = lib_path + '/'
    que = LifoQueue()
    que.put(code_path)

    # build include graph
    while que.empty() == False:
        path = que.get()
        graph[path] = get_includes(path)
        for parent in graph[path]:
            if parent not in visited:
                visited[parent] = False
                que.put(parent)

    # topological sort
    for key in visited.keys():
        dfs(key)

    i = 0
    stl = []
    body = []
    for path in resolved_includes:
        file_id = path[path.find('src/') + 4:]
        stl.extend(get_stl(path))
        print('<' + str(i) + '> ' + file_id, file=sys.stderr)
        i = i+1
        body.append('/* #region ' + file_id + '*/')
        body.extend(get_inner_code(path))
        body.append('/* #endregion */')
    stl = ["/* #region stl */"] + stl + ['/* #endregion */']
    main_contents = get_contents(code_path)

    main_contents[begin_header(main_contents, bb) +
                  1: end_header(main_contents, eb)-1] = ['/* #region auto includes */'] + stl + body + ['/* #endregion */']

    with open(code_path, 'w') as f:
        f.write('\n'.join(main_contents))
