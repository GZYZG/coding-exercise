# http://118.190.20.162/view.page?gpid=T121
class Node:
    def __init__(self, name, size=0, ld=0, lr=0, tp=0):
        self.name = name
        self.kids = {}
        self.ld = ld
        self.lr = lr
        self.size = size  # 表示当前目录下所有普通文件的大小或者当前文件的大小
        self.type = tp  # 0表示目录文件，1表示普通文件
        self.curLr = 0  # 所有普通后代文件的大小
        self.curLd = 0  # 所有普通孩子文件的大小


if __name__ == "__main__":
    n = int(input())
    root = Node("/", tp=0)
    while n > 0:
        cmd = input().split()
        n -= 1
        cmdT = cmd[0]
        fp = cmd[1][1:]
        fp = fp.split('/') if fp else []
        stack = [root]
        flag = True
        if cmdT == "C":
            fz = int(cmd[2])
            fn = fp.pop()
            for name in fp:
                node = stack[-1]

                # 检查是否存在同名的普通文件、检查是否满足配额
                if node.type == 1 or (node.lr != 0 and node.lr < node.curLr + fz):
                    # 操作失败
                    flag = False
                    break

                if node.kids.get(name, None) is None:
                    kid = Node(name, tp=0)
                    node.kids[name] = kid
                    node = kid
                else:
                    node = node.kids[name]
                stack.append(node)

            node = stack[-1]
            if flag:
                if node.type == 1 or (node.ld > 0 and node.curLd <= node.curLd + fz) or \
                        (node.lr > 0 and node.curLr <= node.curLr + fz):  # 判断：是否路径中是否有同名的文件、是否满足后代配额
                    flag = False
                tmp = node.kids.get(fn, None)
                if tmp is not None and tmp.type == 0:  # 当创建的文件与存在且为目录时，创建失败
                    flag = False

            if flag:
                # 可以操作成功
                tmp = node.kids.get(fn, None)
                if tmp is not None:
                    # 存在同名文件，进行替换
                    delta = fz - tmp.size
                else:
                    delta = fz
                nn = Node(fn, tp=1, size=fz)
                node.kids[fn] = nn
                for e in stack:
                    e.curLr += delta
                    e.size += delta
                stack[-1].curLd += delta
            else:
                # 不可以操作成功
                pass
            print('Y' if flag else 'N')
        elif cmdT == "R":
            for name in fp:
                node = stack[-1]
                if node.kids.get(name, None) is None:
                    # 不存在的目录
                    flag = False
                    break
                else:
                    stack.append(node.kids[name])
                    node = node.kids[name]
            if flag:
                fz = stack[-1].size
                for e in stack[::-1]:
                    e.size -= fz
                    if e.type == 0:
                        e.curLr -= fz
                if stack[-1].type == 1:
                    stack[-2].curLd -= fz
                stack[-2].kids.pop(stack[-1].name)
            print('Y')
        else:
            ld = int(cmd[2])
            lr = int(cmd[3])
            for name in fp:
                node = stack[-1]
                if node.kids.get(name, None) is None:
                    # 不存在的目录
                    flag = False
                    break
                else:
                    stack.append(node.kids[name])
                    node = node.kids[name]
            if stack[-1].type == 1:
                flag = False

            if flag:
                node = stack[-1]
                if (0 < ld < node.curLd) or (0 < lr < node.curLr):
                    flag = False
            if flag:
                node.lr = lr
                node.ld = ld
            print('Y' if flag else 'N')