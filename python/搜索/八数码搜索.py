import copy
import math
#棋盘的类，实现移动和扩展状态
class grid:
    def __init__(self,stat):
        self.pre=None
        #目标状态
        #self.target = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
        self.target = [[1, 2, 3], [8, 0, 4], [7, 6, 5]]
        #stat是一个二维列表
        self.stat=stat
        self.find0()
        self.update()
    #更新启发函数的相关信息
    def update(self):
        self.fH()
        #self.fG()
        self.fF()
    #H是和目标状态距离之和
    def fH(self):
        self.H=0
        for i in range(3):
            for j in range(3):
                targetX=self.target[i][j]
                nowP=self.findx(targetX)
                #曼哈顿距离之和
                #self.H+=abs(nowP[0]-i)+abs(nowP[1]-j)
                #欧式距离之和
                self.H+=math.sqrt((nowP[0]-i)*(nowP[0]-i)+(nowP[1]-j)*(nowP[1]-j))
                #欧式距离的平方之和
                #self.H += (nowP[0] - i) * (nowP[0] - i) + (nowP[1] - j) * (nowP[1] - j)
    #F是启发函数，F=H
    def fF(self):
        self.F=self.H
        
    #以三行三列的形式输出当前状态
    def see(self):
        for i in range(3):
             print(self.stat[i])
        print("F=",self.F,"H=",self.H)
        print("-"*10)

    #查看找到的解是如何从头移动的
    def seeAns(self):
        ans=[]
        ans.append(self)
        p=self.pre
        while(p):
            ans.append(p)
            p=p.pre
        ans.reverse()
        for i in ans:
            i.see()

    #找到数字x的位置
    def findx(self,x):
        for i in range(3):
            if(x in self.stat[i]):
                j=self.stat[i].index(x)
                return [i,j]

    #找到0，也就是空白格的位置
    def find0(self):
            self.zero=self.findx(0)

    #扩展当前状态，也就是上下左右移动。返回的是一个状态列表，也就是包含stat的列表
    def expand(self):
        i=self.zero[0]
        j=self.zero[1]
        gridList=[]
        if(j==2 or j==1):
            gridList.append(self.left())
        if(i==2 or i==1):
            gridList.append(self.up())
        if(i==0 or i==1):
            gridList.append(self.down())
        if(j==0 or j==1):
            gridList.append(self.right())
        return gridList


    #deepcopy多维列表的复制，防止指针赋值将原列表改变
    #move只能移动行或列，即row和col必有一个为0
    #向某个方向移动
    def move(self,row,col):
        newStat=copy.deepcopy(self.stat)
        tmp=self.stat[self.zero[0]+row][self.zero[1]+col]
        newStat[self.zero[0]][self.zero[1]]=tmp
        newStat[self.zero[0]+row][self.zero[1]+col]=0
        return newStat

    def up(self):
        return self.move(-1,0)

    def down(self):
        return self.move(1,0)

    def left(self):
        return self.move(0,-1)

    def right(self):
        return self.move(0,1)

#判断状态g是否在状态集合中，g是对象，gList是对象列表
#返回的结果是一个列表，第一个值是真假，如果是真则第二个值是g在gList中的位置索引
def isin(g,gList):
    gstat=g.stat
    statList=[]
    for i in gList:
        statList.append(i.stat)
    if(gstat in statList):
        res=[True,statList.index(gstat)]
    else:
        res=[False,0]
    return res

#计算逆序数之和
def N(nums):
    N=0
    for i in range(len(nums)):
        if(nums[i]!=0):
            for j in range(i):
                if(nums[j]>nums[i]):
                    N+=1
    return N

#根据逆序数之和判断所给八数码是否可解
def judge(src,target):
    N1=N(src)
    N2=N(target)
    if(N1%2==N2%2):
        return True
    else:
        return False

#Astar算法的函数
def Astar(startStat):
    #open和closed存的是grid对象
    open=[]
    closed=[]
    #初始化状态
    g=grid(startStat)
    #检查是否有解
    if(judge(startStat,g.target)!=True):
        print("所给八数码无解，请检查输入")
        exit(1)

    open.append(g)
    #time变量用于记录遍历次数
    time=0
    #当open表非空时进行遍历
    while(open):
        #根据启发函数值对open进行排序，默认升序
        open.sort(key=lambda G:G.F)
        #找出启发函数值最小的进行扩展
        minFStat=open[0]
        #检查是否找到解，如果找到则从头输出移动步骤
        if(minFStat.H==0):
            #print("found and times:",time,"moves:",minFStat.G)
            minFStat.seeAns()
            break

        #走到这里证明还没有找到解，对启发函数值最小的进行扩展
        open.pop(0)
        closed.append(minFStat)
        expandStats=minFStat.expand()
        #遍历扩展出来的状态
        for stat in expandStats:
            #将扩展出来的状态（二维列表）实例化为grid对象
            tmpG=grid(stat)
            #指针指向父节点
            tmpG.pre=minFStat
            #初始化时没有pre，所以G初始化时都是0
            #在设置pre之后应该更新G和F
            tmpG.update()
            #查看扩展出的状态是否已经存在与open或closed中
            findstat=isin(tmpG,open)
            findstat2=isin(tmpG,closed)
            #在closed中,判断是否更新
            if(findstat2[0]==True and tmpG.F<closed[findstat2[1]].F):
                closed[findstat2[1]]=tmpG
                open.append(tmpG)
                time+=1
            #在open中，判断是否更新
            if(findstat[0]==True and tmpG.F<open[findstat[1]].F):
                open[findstat[1]]=tmpG
                time+=1
            #tmpG状态不在open中，也不在closed中
            if(findstat[0]==False and findstat2[0]==False):
                open.append(tmpG)
                time+=1

stat = [[2, 8, 3], [1, 0, 4], [7, 6, 5]]
Astar(stat)
