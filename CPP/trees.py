if __name__ == "__main__":
    n = int(input())
    pos = input().split()
    pos = list(map(lambda x: int(x), pos))

    ret = 0

    a, b = pos[:2]

    l = b-a
    if l == 1:
        ret += 1
    else:
        for i in range(1, l//2+1):
            if l % i == 0:
                ret += 1

    print(ret)
