# http://118.190.20.162/view.page?gpid=T111
class Node:
    def __init__(self, func, input=[], output=None):
        self.func = func
        self.input = input
        self.output = output

    def cal(self, inputs):
        func = self.func
        if func == 'NOT':
            return 1- inputs[0]
        elif func == 'AND':
            return int(all(inputs))
        elif func == 'OR':
            return int(any(inputs))
        elif func == 'XOR':
            return int(sum(inputs) % 2 == 1)
        elif func == 'NAND':
            return 1 - int(all(inputs))
        elif func == 'NOR':
            return 1 - int(any(inputs))

    def __str__(self):
        return f"{self.func}-{self.input}-{self.output}"


if __name__ == "__main__":
    Q = int(input())
    for i in range(Q):
        # 处理Q个问题
        isLoop = False
        M, N = input().split()  # 输入数量和器件数量
        M = int(M)
        N = int(N)
        inputs = {k: Node(f'I{k}', output=f'I{k}') for k in range(1, M+1)}  # M个输入
        gates = [None] * (N+1)
        for j in range(1, N+1):
            tmp = input().split()
            func = tmp[0]
            nInput = int(tmp[1])
            tmp = tmp[2:]
            gates[j] = Node(func, tmp, f'O{j}')
        S = int(input())
        allInputsValue = [None] * (S+1)
        for j in range(1, S+1):
            runs = input().split()
            allInputsValue[j] = [int(e) for e in runs]
        for j in range(1, S+1):
            tmp = input().split()
            nOutput = int(tmp[0])
            outGates = [int(e) for e in tmp[1:]]
            outs = [-1] * (N+1)
            num = 0
            while num < N:
                new = 0  # 每次遍历过程中能够得到输出的门新增的数量
                for k, g in enumerate(gates[1:], start=1):
                    if outs[k] != -1:
                        continue
                    flag = all([e[0] == 'I' or outs[int(e[1:])] != -1 for e in g.input])
                    if flag:
                        ipts = [allInputsValue[j][int(e[1:])-1] if e[0] == 'I' else outs[int(e[1:])] for e in g.input]
                        o = g.cal(ipts)
                        outs[k] = o
                        new += 1

                if new == 0:  # 如果遍历一圈都没有得到新的门产生输出，则说明存在环
                    isLoop = True
                    break
                num += new

            if isLoop:
                break
            outs = [str(outs[e]) for e in outGates]
            print(" ".join(outs))
        if isLoop:
            print("LOOP")
