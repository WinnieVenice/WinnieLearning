#from itertools import permutations
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
#from itertools import combinations, permutations

def dis(x, y, p1, p2):
    p1 = int(p1)
    p2 = int(p2)
    return (x[p1] - x[p2]) ** 2 + (y[p1] - y[p2]) ** 2
def f(pop, num, n, x, y):
    '''适应度函数，计算每个排列的适应度，并保存到pop矩阵第二维的最后一项'''
    for x1 in range(num):
        square_sum = 0
        for x2 in range(n):
            square_sum += dis(x, y, pop[x1][x2], pop[x1][x2 + 1])
        # print(round(1/np.sqrt(square_sum),7))
        pop[x1][-1] = round(1/np.sqrt(square_sum),7)
def choiceFuction(pop):
    '''
    这里的做法：比如A当前种群中的最优解，B为经过交叉、变异后的最差解，把A作为最当前代中的最优解保存下来作为这一代的最优解，同时A也参与交叉
    和变异。经过交叉、变异后的最差解为B，那么我再用A替代B。
    :argument pop矩阵
    :return 本代适应度最低的个体的索引值和本代适应度最高的个体
    '''
    yield np.argmin(pop[:, -1])
    yield pop[np.argmax(pop[:, -1])]
def choice(pop, num, n, x, y, b):
    f(pop,num,n,x,y)
    c,d =choiceFuction(pop)
    # 上一代的最优值替代本代中的最差值
    pop[c] = b
    return pop
def drawPic(maxFitness,x_position,y_position,i):
    index = np.array(maxFitness[:-1],dtype=np.int32)    #去掉向量最后一个元素
    x = np.append(x_position[index],x_position[[index[0]]])
    y = np.append(y_position[index],y_position[[index[0]]])
    fig = plt.figure()
    plt.plot(x,y,'-o')
    plt.xlabel('x',fontsize = 16)
    plt.ylabel('y',fontsize = 16)
    plt.title('{iter}'.format(iter=i))
    plt.show()
def matuingFuction(pop, pc, n, pm, num):
    mating_matrix = np.array(1 - (np.random.rand(num) > pc), dtype=np.bool)  # 交配矩阵，如果为true则进行交配
    a = list(pop[mating_matrix][:, :-1])  # 进行交配的个体
    b = list(pop[np.array(1 - mating_matrix, dtype=bool)][:, :-1])  # 未进行交配的个体,直接放到下一代
    b = [list(i) for i in b]  # 对b进行类型转换，避免下面numpy.array 没有index属性
    #     print(a)
    if len(a) % 2 != 0:
        b.append(a.pop())
    # print('ab的长度：',len(a),len(b))
    for i in range(int(len(a) / 2)):
        # 随机初始化两个交配点,这里写得不好，这边的两个点初始化都是一个在中间位置偏左，一个在中间位置偏右
        p1 = np.random.randint(1, int(n / 2) + 1)
        p2 = np.random.randint(int(n / 2) + 1, n)
        x1 = list(a.pop())
        x2 = list(a.pop())
        matuting(x1, x2, p1, p2)
        # 交配之后产生的个体进行一定概率上的变异
        variationFunction(x1, pm, n)
        variationFunction(x2, pm, n)
        b.append(x1)
        b.append(x2)
    zero = np.zeros((num, 1))
    #     print('b的形状：',len(b))
    temp = np.column_stack((b, zero))
    return temp


def matuting(x1, x2, p1, p2):
    # 以下进行交配
    # 左边交换位置
    temp = x1[:p1]
    x1[:p1] = x2[:p1]
    x2[:p1] = temp
    # 右边交换位置
    temp = x1[p2:]
    x1[p2:] = x2[p2:]
    x2[p2:] = temp
    # 寻找重复的元素
    center1 = x1[p1:p2]
    center2 = x2[p1:p2]
    while True:  # x1左边
        for i in x1[:p1]:
            if i in center1:
                # print(center1.index(i)) # 根据值找到索引
                x1[x1[:p1].index(i)] = center2[center1.index(i)]
                break
        if np.intersect1d(x1[:p1], center1).size == 0:  # 如果不存在交集，则循环结束
            break
    while True:  # x1右边
        for i in x1[p2:]:
            if i in center1:
                # print(center1.index(i)) # 根据值找到索引
                x1[x1[p2:].index(i) + p2] = center2[center1.index(i)]
                # print(x1)
                break
        if np.intersect1d(x1[p2:], center1).size == 0:  # 如果不存在交集，则循环结束
            break
    while True:  # x2左边
        for i in x2[:p1]:
            if i in center2:
                #                     print(center2.index(i)) # 根据值找到索引
                x2[x2[:p1].index(i)] = center1[center2.index(i)]
                break
        if np.intersect1d(x2[:p1], center2).size == 0:  # 如果不存在交集，则循环结束
            break
    while True:  # x2右边
        for i in x2[p2:]:
            if i in center2:
                # print(center2.index(i)) # 根据值找到索引
                x2[x2[p2:].index(i) + p2] = center1[center2.index(i)]
                # print(x2)
                break
        if np.intersect1d(x2[p2:], center2).size == 0:  # 如果不存在交集，则循环结束
            break
        
def variationFunction(list_a, pm, n):
    '''变异函数'''
    if np.random.rand() < pm:
        p1 = np.random.randint(1, int(n / 2) + 1)
        p2 = np.random.randint(int(n / 2) + 1, n)
        #         print(p1,p2)
        temp = list_a[p1:p2]
        temp.reverse()
        list_a[p1:p2] = temp
# print(list_a)
def findDistance(pop):
    sum=0
    for temp in pop:
            sum += 1/temp[-1]
    return sum
def main():
    Gen = []  # 代数
    dist = []  # 每一代的最优距离
    # 初始化
    pop = []  # 存放访问顺序和每个个体适应度
    num = 250  # 初始化群体的数目
    n = 10  # 城市数目
    pc = 0.9  # 每个个体的交配概率
    pm = 0.2  # 每个个体的变异概率
    x_position = np.random.randint(0, 100, size=n)
    y_position = np.random.randint(0, 100, size=n)
    x = np.append(x_position, x_position[0])
    y = np.append(y_position, y_position[0])
    for i in range(num):
        pop.append(np.random.permutation(np.arange(0, n)))  # 假设有10个城市，初始群体的数目为250个
        # 初始化化一个60*1的拼接矩阵，值为0
    zero = np.zeros((num, 1))
    pop = np.column_stack((pop, zero))  # 矩阵的拼接
    f(pop, num, n, x, y)
    for i in range(180):
        a, b = choiceFuction(pop)  # a 为当代适应度最小的个体的索引，b为当代适应度最大的个体,这边要保留的是b
        # pop[a]=b
        # print(x," ",y)
        if (i + 1) % 10 == 0:
            distance = findDistance(pop)
            print("适应度：", b[-1]);
            print("目标函数值：", 1 / b[-1]);
            print("当前实验最优解：",distance)
            print("-----------------------")
            Gen.append(i+1)
            dist.append(distance)
            #drawPic(b, x_position, y_position, i + 1)  # 根据本代中的适应度最大的个体画图
        pop_temp = matuingFuction(pop, pc, n, pm, num)  # 交配变异
        pop = choice(pop_temp, num, n, x, y, b)
    # 绘制进化曲线
    plt.plot(Gen, dist, '-r')
    plt.show()
main()
if __main__ == 
