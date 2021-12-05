import matplotlib.pyplot as plt
from random import sample
import numpy as np
from sklearn.cluster import KMeans
from sklearn.datasets import load_iris
if __name__ == '__main__':
    #导入数据集
    iris = load_iris()
    X = iris.data[:,0:2] #取特征
    n = 3 #表示n个聚类
    u = sample(X.tolist(),n) #随机选择n个X中的向量作为聚类中心
    max_iter = 0 #记录迭代次数
    u_before = u
    #簇分配过程
    while max_iter < 5: # 迭代次数
        c = []
        for i in range(len(X)):
            min = 1000
            index = 0
            for j in range(n):
                dist = np.sqrt(np.sum(np.square(X[i] - u[j])))
                if dist < min:
                    min = dist
                    index = j
            c.append(index)
        for j in range(n):
            sum = np.zeros(2) 
            cnt = 0 
            for i in range(len(X)):
                if c[i] == j:
                    sum = sum+X[i]
                    cnt = cnt+1
            u[j] = sum / cnt
        max_iter += 1
    label_pred = np.array(c)
    #可视化k-means结果
    col = ["green", "blue", "red"]
    for i in range(3):
        res = X[label_pred == i]
        plt.scatter(res[:, 0], res[:, 1], c = col[i], marker = 'x')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend(loc=2)
    plt.show()