from collections import deque

MOVES1 = [(0, 1), (0, -1), (1, 0), (-1, 0)]
P=["R","L","D","U"]
H,W=list(map(int,input().split()))
S=[input() for _ in [0]*H]

sx=sy=gx=gy=-1

for i in range(H):
    for k in range(W):
        if S[i][k]=="S":
            sx,sy=i,k
        elif S[i][k]=="G":
            gx,gy=i,k

INF=1<<30
prv=[[[(-1,-1,-1) for _ in [0]*4] for _ in [0]*W] for _ in [0]*H]
used=[[[INF for _ in [0]*4] for _ in [0]*W] for _ in [0]*H]

Q=deque()

for i in range(4):
    used[sx][sy][i]=0
    Q.append((sx,sy,i))

while Q:
    x,y,p=Q.popleft()

    for i in range(4):
        mx,my=MOVES1[i]
        nx,ny=x+mx,y+my

        if not (0<=nx<H and 0<=ny<W):
            continue

        if (S[x][y]=="o" and i!=p) or (S[x][y]=="x" and i==p) or (S[nx][ny]=="#"):
            continue
        if used[nx][ny][i]==INF:
            used[nx][ny][i]=used[x][y][p]+1
            prv[nx][ny][i]=(x,y,p)
            Q.append((nx,ny,i))


for p in range(4):
    if used[gx][gy][p]!=INF:
        print("Yes")
        ans=[]

        x,y=gx,gy

        while prv[x][y][p]!=(-1,-1,-1):
            ans.append(P[p])
            x,y,p=prv[x][y][p]

        print("".join(ans[::-1]))
        break
else:
    print("No")

