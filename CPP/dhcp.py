# http://118.190.20.162/view.page?gpid=T126
class IP:
    def __init__(self, addr):
        self.addr = addr
        self.status = "wfp"
        self.user = ''
        self.expired = 0

    def __str__(self):
        return f"[{self.addr}-{self.status}-{self.user}-{self.expired}]"


if __name__ == "__main__":
    tmp = input().split()
    N = int(tmp[0])
    tdef = int(tmp[1])
    tmax = int(tmp[2])
    tmin = int(tmp[3])
    H = tmp[-1]
    num = int(input())
    n = 0

    packs = []
    for i in range(num):
        packs.append(input())

    ipPools = {k: IP(k) for k in range(1, N+1)}
    usedIPs = {}

    for pack in packs:
        pack = pack.split()
        t = int(pack[0])
        pack = pack[1:]
        sender = pack[0]
        receiver = pack[1]
        ptype = pack[2]
        ip = int(pack[3])
        expired = int(pack[4])

        # 清除过期的ip
        ks = list(usedIPs.keys())
        for k in ks:
            if usedIPs[k].expired <= t:
                usedIPs[k].status = 'gq'
                usedIPs[k].user = ''
                usedIPs[k].expired = 0
                usedIPs.pop(k)



        if receiver not in [H, '*'] and ptype != "REQ":
            continue

        if (receiver == "*" and ptype != "DIS") or (receiver == H and ptype == "DIS"):
            continue

        rep = ""
        if ptype == "DIS":
            if usedIPs.get(sender, None) is not None:
                used = usedIPs[sender]
            else:
                flag = False
                for i in range(1, N):
                    if ipPools[i].status == "wfp":
                        used = ipPools[i]
                        usedIPs[sender] = used
                        flag = True
                        break
                if not flag:
                    for i in range(1, N):
                        if ipPools[i].status == "gq":
                            used = ipPools[i]
                            usedIPs[sender] = used
                            flag = True
                            break
                if not flag:
                    continue

            used.status = "dfp"
            used.user = sender
            if expired == 0:
                used.expired = t + tdef
            else:
                if expired <= t + tmin:
                    used.expired = t + tmin
                elif expired >= t + tmax:
                    used.expired = t + tmax
                else:
                    used.expired = expired

            rep = f"{H} {sender} OFR {used.addr} {used.expired}"

        elif ptype == "REQ":
            if receiver == H:
                if sender in usedIPs and usedIPs[sender].addr == ip:
                    used = usedIPs[sender]
                    used.status = "zy"
                    if expired == 0:
                        used.expired = t + tdef
                    else:
                        if expired <= t + tmin:
                            used.expired = t + tmin
                        elif expired >= t + tmax:
                            used.expired = t + tmax
                        else:
                            used.expired = expired

                    rep = f"{H} {sender} ACK {ip} {used.expired}"
                else:
                    # NAK
                    rep = f"{H} {sender} NAK {ip} 0"
            else:
                if usedIPs.get(sender, None) is not None:
                    used = usedIPs[sender]
                    if used.status == "dfp":
                        usedIPs.pop(used.user)
                        used.status = "wfp"
                        used.expired = 0
                        used.user = ""

                rep = ""
        # 将过期变为未分配
        # for k in ipPools.keys():
        #     if ipPools[k].status == 'gq':
        #         ipPools[k].status = 'wfp'
        if rep:
            print(rep)
