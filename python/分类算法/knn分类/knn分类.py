
import pandas as pd
import random
import math
import operator
import matplotlib.pyplot as plt

def change_job(state):
    # 转换职业状态
    job = [ "admin.","blue-collar","entrepreneur","housemaid","management","retired",
            "self-employed","services","student","technician","unemployed","unknown"]
    for i in range(len(job)):
        if state == job[i]:
            return i

def change_marital(state):
    # 转换婚姻状态:未知：0,单身：1,结婚：2,离婚：3
    marital = ["divorced","married","single","unknown"]
    for i in range(len(marital)):
        if state == marital[i]:
            return i

def change_education(state):
    # 转换教育水平
    education = ["basic.4y","basic.6y","basic.9y","high.school","illiterate","professional.course","university.degree","unknown"]
    for i in range(len(education)):
        if state == education[i]:
            return i

def change_binary(state):
    # 二分类转换
    if state == 'yes':
        state = 1
    elif state == 'no':
        state = 0
    return state

def change_contact(state):
    # 转换接触方式: 未知(unknown):0、网络(cellular)：1、电话（telephone）：2
    contact = ['unknown', 'cellular', 'telephone']
    for i in range(len(contact)):
        if state == contact[i]:
            return i

def change_poutcome(state):
    # 转换poutcome（上次成功与否）
    poutcome = ["failure","nonexistent","success"]
    for i in range(len(poutcome)):
        if state == poutcome[i]:
            return i
def change_month(state):
    # 转换month
    month = ['jan','feb','mar','apr','may','jun','jul','aug','sep','oct','nov','dec']
    for i in range(len(month)):
        if state == month[i]:
            return i
def change_week(state):
    # 转换week
    week = ["mon","tue","wed","thu","fri"]
    for i in range(len(week)):
        if state == week[i]:
            return i
def change_default(state):
    # 转换default
    default = ["no","yes","unknown"]
    for i in range(len(default)):
        if state == default[i]:
            return i

def read(filename):
    bank = pd.read_csv(filename, sep=';')
    data = [[] for i in range(len(bank))]
    for i in range(len(data)):
        data[i].append(bank['age'][i])
        data[i].append(change_job(bank['job'][i]))
        data[i].append(change_marital(bank['marital'][i]))
        data[i].append(change_education(bank['education'][i]))
        data[i].append(change_default(bank['default'][i]))
        data[i].append(change_default(bank['housing'][i]))
        data[i].append(change_default(bank['loan'][i]))
        data[i].append(change_contact(bank['contact'][i]))
        data[i].append(change_month(bank['month'][i]))
        data[i].append(change_week(bank['day_of_week'][i]))
        data[i].append(bank['duration'][i])
        data[i].append(bank['campaign'][i])
        data[i].append(bank['pdays'][i])
        data[i].append(bank['previous'][i])
        data[i].append(change_poutcome(bank['poutcome'][i]))
        data[i].append(bank['emp.var.rate'][i])
        data[i].append(bank['cons.price.idx'][i])
        data[i].append(bank['cons.conf.idx'][i])
        data[i].append(bank['euribor3m'][i])
        data[i].append(bank['nr.employed'][i])
        data[i].append(change_binary(bank['y'][i]))
    for x in range(len(data)):
        for y in range(len(data[x])):
            # print(data[x][y])
            data[x][y] = float(data[x][y])
    return data

def euclideanDistance(p1, p2,len):
    #计算欧式距离
    dis=0
    for x in range(len):
        dis += pow((p1[x] -  p2[x]), 2)
    return math.sqrt(dis)
if __name__ == '__main__':
    filename = r"E:\\workworkwork\\GitHub\WinnieLearning\\python\\分类算法\\knn分类\\bank-additional.csv"
    data = read(filename)
    train_data=[]
    test_data=[]
    #拆分数据集
    for id in range(len(data)):
        if random.random() <= 0.7:
            train_data.append(data[id])
        else:
            test_data.append(data[id])    
    print("划分的训练集数:", len(train_data), "划分的测试集数:", len(test_data))
    predict=[]
    k = 7
    for x in range(len(test_data)):
        #选取距离最近的k个实例 test_data(需要分类的测试集点)
        dis=[]
        length = len(test_data[x]) - 1
        for id in range(len(train_data)):
            dis.append((train_data[id], euclideanDistance(train_data[id],test_data[x],length)))
        dis.sort(key = operator.itemgetter(1))
        neighbors=[]
        for id in range(k):
            neighbors.append(dis[x][0])
        #获取距离最近的k个实例中占比例较大的分类
        classvotes = {}
        for x in range(len(neighbors)):
            response=neighbors[x][-1]
            if response in classvotes:
                classvotes[response]+=1
            else:
                classvotes[response]=1
            sortedVotes = sorted(classvotes.items(), key=operator.itemgetter(1), reverse=True)
        res = sortedVotes[0][0]
        predict.append(res)
    # 计算准确率
    accuracy = 0
    for x in range(len(test_data)):
        if test_data[x][-1]==predict[x]:
            accuracy += 1
    accuracy = accuracy / float(len(test_data)) * 100
    print('准确率：', accuracy)
    # 可视化
    X = test_data
    X1 = [n[0] for n in X]
    #X2 = [n[8] for n in X]   # 以month划分
    #X2 = [n[10] for n in X]  # 以duration划分
    X2 = [n[5] for n in X]  # 以housing划分
    X3 = [n[-1] for n in X]
    # 画图
    plt.xlabel("age")
    #plt.ylabel("month")
    #plt.ylabel("duration")
    plt.ylabel("housing") 
    plt.scatter(X1, X2, c = X3, cmap = plt.cm.spring, edgecolor = 'k')
    plt.show()
