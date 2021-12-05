import numpy as np
import matplotlib
import matplotlib.pyplot as plt
def dis(x, y, p1, p2):
    p1 = int(p1)
    p2 = int(p2)
    return (x[p1] - x[p2]) ** 2 + (y[p1] - y[p2]) ** 2
def f(F, N, n, x, y):
    # 适应度函数
    for x1 in range(N):
        square_sum = 0
        for x2 in range(n):
            square_sum += dis(x, y, F[x1][x2], F[x1][x2 + 1])
        F[x1][-1] = round(1 / np.sqrt(square_sum), 7)
def matching(mat, pc, n, pm, num): 
    match_matrix = np.array(1 - (np.random.rand(num) > pc), dtype = np.bool_)
    a = list(mat[match_matrix][:, :-1])  # 进行交配的个体
    b = list(mat[np.array(1 - match_matrix, dtype=bool)][:, :-1])  # 未进行交配的个体,直接放到下一代
    b = [list(i) for i in b]
    if len(a) % 2 != 0:
        b.append(a.pop())
    for i in range(int(len(a) / 2)):
        p1 = np.random.randint(1, int(n / 2) + 1)
        p2 = np.random.randint(int(n / 2) + 1, n)
        x1 = list(a.pop())
        x2 = list(a.pop())
        x1[:p1], x2[:p1] = x2[:p1], x1[:p1]
        x1[:p2], x2[:p2] = x2[:p2], x1[:p2]
        c1 = x1[p1:p2]
        c2 = x2[p1:p2]
        while True: 
            for i in x1[:p1]:
                if i in c1:
                    x1[x1[:p1].index(i)] = c2[c1.index(i)]
                    break
            if np.intersect1d(x1[:p1], c1).size == 0:
                break
        while True: 
            for i in x1[p2:]:
                if i in c1:
                    x1[x1[p2:].index(i) + p2] = c2[c1.index(i)]
                    break
            if np.intersect1d(x1[p2:], c1).size == 0:
                break
        while True: 
            for i in x2[:p1]:
                if i in c2:
                    x2[x2[:p1].index(i)] = c1[c2.index(i)]
                    break
            if np.intersect1d(x2[:p1], c2).size == 0:
                break
        while True:  
            for i in x2[p2:]:
                if i in c2:
                    x2[x2[p2:].index(i) + p2] = c1[c2.index(i)]
                    break
            if np.intersect1d(x2[p2:], c2).size == 0:  # 如果不存在交集，则循环结束
                break
        # 交配之后产生的个体进行一定概率上的变异
        variation(x1, pm, n)
        variation(x2, pm, n)
        b.append(x1)
        b.append(x2)
    return np.column_stack((b, np.zeros((num, 1))))
def variation(list_a, pm, n):
    '''变异函数'''
    if np.random.rand() < pm:
        p1 = np.random.randint(1, int(n / 2) + 1)
        p2 = np.random.randint(int(n / 2) + 1, n)
        #         print(p1,p2)
        temp = list_a[p1:p2]
        temp.reverse()
        list_a[p1:p2] = temp
if __name__ == '__main__':
    gen = []  # 代数
    dist = []  # 每一代的最优距离
    # 初始化
    F = []  #存放访问顺序和每个个体适应度
    N = 500  #初始化群体的数目
    n = 10  #城市数
    pc = 0.9  #交配概率
    pm = 0.2  #变异概率
    pos_x = np.random.randint(0, 100, size = n)
    pos_y = np.random.randint(0, 100, size = n)
    x = np.append(pos_x, pos_x[0])
    y = np.append(pos_y, pos_y[0])
    for i in range(N):
        F.append(np.random.permutation(np.arange(0, n))) 
    zero = np.zeros((N, 1))
    F = np.column_stack((F, zero))  # 矩阵的拼接
    f(F, N, n, x, y)
    for i in range(200):
        a, b = np.argmin(F[:, -1]), F[np.argmax(F[:, -1])] 
        if (i + 1) % 10 == 0:
            cur_dis = 0
            for v in F:
                cur_dis += 1 / v[-1]
            print("当前实验最优解：", cur_dis)
            gen.append(i+1)
            dist.append(cur_dis)
            index = np.array(b[:-1], dtype=np.int32)
            x = np.append(pos_x[index],pos_x[[index[0]]])
            y = np.append(pos_y[index],pos_y[[index[0]]])
            fig = plt.figure()
            plt.plot(x,y,'-o')
            plt.xlabel('x',fontsize = 16)
            plt.ylabel('y',fontsize = 16)
            plt.title('{iter}'.format(iter=i+1) + 'th gen')
            plt.show()
        mat_temp = matching(F, pc, n, pm, N)  # 交配变异
        f(F, N, n, x, y)
        c, d = np.argmin(F[:, -1]), F[np.argmax(F[:, -1])]
        F[c] = b
    # 绘制进化曲线
    plt.plot(gen, dist, '-r')
    plt.show()
