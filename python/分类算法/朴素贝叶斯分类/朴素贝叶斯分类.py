import math
Iris_setosa_data = []
Iris_versicolor_data = []
Iris_virginica_data = []
test_data = []
def split(data, l, r):
    s = []
    for line in data[l : r - 10]:
        line = line.strip().split(',')
        s.append(line[0 : 4])
    for line in data[r - 10 : r]:
        line = line.strip().split(',')
        test_data.append(line[0 : 4])
    return s
def read(filename):
    # 读取训练数据集前40条数据，剩下的10条数据作为测试数据集
    f = open(filename, 'r')
    all_lines = f.readlines()
    Iris_setosa_data = split(all_lines, 0, 50)
    Iris_versicolor_data = split(all_lines, 50, 100)
    Iris_virginica_data = split(all_lines, 100, 150)
    return Iris_setosa_data, Iris_versicolor_data, Iris_virginica_data
def calc(train_data):
    # 计算均值和方差    
    sum_x = [0.0, 0.0, 0.0, 0.0]
    for x in train_data:
        for id in range(0, 4):
            sum_x[id] += float(x[id])
    ux = []
    for id in range(0, 4):
        ux.append(sum_x[id] / 45)
    k = [0.0, 0.0, 0.0, 0.0]
    for x in train_data:
        for id in range(0, 4):
            k[id] += (float(x[id]) - ux[id]) ** 2
    vx = []
    for id in range(0, 4):
        vx.append(k[id] / 45)
    return ux, vx

def calc_P(ux, vx, data):
    # 计算每个属性估计条件概率
    px = []
    C = 1 / math.sqrt(2 * math.pi)
    for id in range(0, 4):
        px.append(C * math.exp(-(float(data[id]) - ux[id]) ** 2 / (2 * vx[id])))
    return px 
if __name__ == '__main__':
    print('读取数据集')
    filename = 'E:\workworkwork\GitHub\WinnieLearning\python\分类算法\朴素贝叶斯分类\iris.data'
    Iris_setosa_data, Iris_versicolor_data, Iris_virginica_data = read(filename)
    # 求均值和方差
    Iris_setosa_ux, Iris_setosa_vx = calc(Iris_setosa_data)
    Iris_versicolor_ux, Iris_versicolor_vx = calc(Iris_versicolor_data)
    Iris_virginica_ux, Iris_virginica_vx = calc(Iris_virginica_data)
    print ('测试数据')
    for x in test_data:
        print(x)
    print('开始测试')
    # 估计类先验概率
    sum_data = len(Iris_versicolor_data) + len(Iris_virginica_data) + len(Iris_setosa_data)
    p = []
    for data in [len(Iris_setosa_data), len(Iris_versicolor_data), len(Iris_virginica_data)]:
        p.append(data / sum_data)
    for data in test_data:
        Iris_setosa_Px = calc_P(Iris_setosa_ux, Iris_setosa_vx, data)
        Iris_versicolor_Px = calc_P(Iris_versicolor_ux, Iris_versicolor_vx, data)
        Iris_virginica_Px = calc_P(Iris_virginica_ux, Iris_virginica_vx, data)
        P = [p[0], p[1], p[2]] # Iris_setosa_P, Iris_versicolor_P, Iris_virginica_P
        for id in range(0, 4):
            P[0], P[1], P[2] = P[0] * Iris_setosa_Px[id], P[1] * Iris_versicolor_Px[id], P[2] * Iris_virginica_Px[id]
        if P[0] == max(P):
            print(data, ":这行数据属于Iris_setosa类")
        elif P[1] == max(P):
            print(data, ":这行数据属于Iris_versicolor类")
        else:
            print(data, ":这行数据属于Iris_virginica类")
        
