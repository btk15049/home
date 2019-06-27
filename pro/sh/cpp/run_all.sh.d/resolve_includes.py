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
bh = '/*<head>*/'
eh = '/*</head>*/'
bb = '/*<body>*/'
eb = '/*</body>*/'


def get_contents(path):
    contents = []
    with open(path) as f:
        contents = f.readlines()
    for i in range(len(contents)):
        contents[i] = contents[i].strip()
    return contents


def begin_header(contents, word):
    return contents.index(word)


def end_header(contents, word):
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
    return contents[: begin_header(contents, bh)] + contents[end_header(contents, eh):]


if __name__ == "__main__":
    code_path = sys.argv[1]
    lib_path = sys.argv[2]
    if lib_path[-1] != '/':
        lib_path = lib_path + '/'
    que = LifoQueue()
    que.put(code_path)

    if len(get_includes(code_path)) == 0:
        exit(0)

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
    body = []
    body.append('/* #region header */')
    for path in resolved_includes:
        print('<'+str(i)+'>'+path, file=sys.stderr)
        i = i+1
        body.append('/* #region ' + str(i) + '*/')
        body.extend(get_inner_code(path))
        body.append('/* #endregion */')
    body.append('/* #endregion */')

    main_contents = get_contents(code_path)

    # for i in range(begin_header(main_contents, bh)+1, end_header(main_contents, eh)-1):
    #     main_contents[i] = '// ' + main_contents[i]

    main_contents[begin_header(main_contents, bb) +
                  1: end_header(main_contents, eb)-1] = body

    with open(code_path, 'w') as f:
        f.write('\n'.join(main_contents))
