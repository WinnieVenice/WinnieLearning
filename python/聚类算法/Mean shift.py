from sklearn.cluster import MeanShift
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE
from matplotlib.pyplot import style
import numpy as np
def load_data(path):
    f = open(path)  # 打开文件
    tmp1 = []
    tmp = []
    for line in f.readlines():
        lines = line.strip().split("\t")
        data_tmp = []
        s = line.strip().split(',')
        tmp.append([float(s[0]), float(s[1]), float(s[2]), float(s[3])])
    tmp1.append(tmp)
    data = np.concatenate((tmp1))
    f.close()
    return data
if __name__ == '__main__':  
    data = load_data("E:\workworkwork\GitHub\WinnieLearning\python\聚类算法\iris.data")
    print(data)
    #搭建Mean-Shift聚类器
    clf=MeanShift()
    #对样本数据进行聚类
    predicted=clf.fit_predict(data)
    colors = [['black','green','blue','yellow'][i] for i in predicted]
    #绘制聚类图
    plt.scatter(data[:,0],data[:,1],c=colors,marker='x')
    plt.title('Mean Shift')
    plt.show()