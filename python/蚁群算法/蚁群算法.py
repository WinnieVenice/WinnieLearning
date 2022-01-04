import random
import math
import matplotlib.pyplot as plt
global n,m,best,Q;
global br;
best = 10000;   #最优距离
n=10;m=30;  #n:样本个数 m:城市个数
road = [[0]*(m) for i in range(n)]  #开辟n*m的数组记录每个只蚂蚁行走的路线
tau = [[0]*(m) for i in range(n)]   #禁忌表
con = [[0]*(m) for i in range(m)]   #信息素浓度
dis =  [[0]*(m) for i in range(m)]  #两点间的距离
game = [0.0]*m; #轮盘赌的概率
value = [0.0]*n;    #每只蚂蚁的路线长度
way = [0]*m;    #最优解路线
class _pot:                  
    def __init__(self,x,y):
        self.x=x;
        self.y=y;
p=[];
def draw(t):             
    x=[0]*(m+1);y=[0]*(m+1);
    for i in range(m):
        x[i] =p[t[i]].x;
        y[i] =p[t[i]].y;
    x[m] =p[t[0]].x;
    y[m] =p[t[0]].y;
    plt.plot(x,y,color='r',marker='*' ); 
    plt.show();
def init_map():                           #城市坐标输入
    for times in range(m):
        p.append(_pot(random.randrange(10, 50), random.randrange(10, 50)))
    
def  get_dis(a,b):       #返回a，b两城市的距离
    return   math.sqrt((p[a].x-p[b].x) *(p[a].x-p[b].x) +(p[a].y-p[b].y) *(p[a].y-p[b].y));
def get_value(t):        #计算蚂蚁t的路线长度
    ans = 0.0;
    for i in range(1,m):     #两点距离公式
        ans += math.sqrt((p[t[i]].x-p[t[i-1]].x) *(p[t[i]].x-p[t[i-1]].x)  +(p[t[i]].y-p[t[i-1]].y) *(p[t[i]].y-p[t[i-1]].y));
    ans +=  math.sqrt((p[t[0]].x-p[t[m-1]].x) * (p[t[0]].x-p[t[m-1]].x)  +(p[t[0]].y-p[t[m-1]].y) *(p[t[0]].y-p[t[m-1]].y));
    return ans;
def init():            #初始化函数
    for i in range(m):
        for j in range(m):
            con[i][j] = 0.1;             #初始化所有信息素为0.03
            dis[i][j]=get_dis(i,j);
def rws():                                      #轮盘赌函数
    num = random.random();
    r = 0.0;
    for i in range(m):
        r += game[i];
        if(r >= num): return i;
    return m-1;
def move(x,loc):              #蚂蚁x从loc位置爬行到下一个点
    tol=0.0
    pk = [0.0]*m;
    for i in range(m):
        if(tau[x][i] != 1and dis[loc][i] !=0):    #概率计算
                pk[i] = con[loc][i]*(1/dis[loc][i])*(1/dis[loc][i]);
        else:
            pk[i]=0;
        tol += pk[i];
    if(tol == 0):           #启发式信息的总和为0，br标记迭代结束
        tol=1;br=0;       
    for i in range(m):    #分配轮盘赌的概率
        game[i] =pk[i]/tol;
    return rws();       #返回轮盘赌的选择
def solve():
    global best,br;
    for i in range(n):
        for j in range(m):
            tau[i][j] = 0;       #初始化禁忌表
    for i in range(n):
        num = random.randint(0,m-1);    #随机选择出发地点
        tau[i][num]=1;   road[i][0] = num;
    for k in range(m-1):
        for i in range(n):
            ob = move(i,road[i][k]);      #向前移动一步
            tau[i][ob]=1;road[i][k+1] = ob;     #更新禁忌表
    if(br == 0):          #br=0说明迭代已经到达终点，函数结束
        return;
    for i in range(n):               #计算每只蚂蚁路径长度
        value[i]=get_value(road[i]);
        if(value[i] < best):       #更新记录最优解
            best = value[i];
            for j in range(m):
                way[j]= road[i][j];     
    for i in range(m):               #挥发过程，每次挥发0.1
        for j in range(m):
            con[i][j]*=0.9;
    for i in range(n):               #信息素更新
        for j in range(m-1):
            a=road[i][j];  b=road[i][j+1];
            con[a][b] += Q/value[i];                #Q为信息素强度
    
    for i in range(n):
            a=road[i][m-1];  
            b=road[i][0];
            con[a][b] += Q/value[i];
        
        
if __name__ == '__main__': 
    init_map();            #数据输入    
    init();                 #数据初始化
    Q=10000;        #信息素强度
    br = 1;
    pre_best = 100000000000000
    best_way = [0] * m
    for i in range(100):    #迭代次数
        if(br == 0):
            break;
        solve();
        print(round(best,3)); 
        if pre_best != best:
            plt.title(str(i) + "th solve")
            draw(way);                     
            print(way);                     
            pre_best = best
            best_way = way
    plt.title('the best path')
    draw(best_way)
    print(best_way)
        