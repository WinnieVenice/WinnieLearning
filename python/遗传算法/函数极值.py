import random
import time
def f(x):
    return x * x
def p(x):
    return f(x) / sum
def swap(x, y):
    print([x, y])
    xx = 3 | x
    x -= xx
    yy = 3 | y
    y -= yy
    x += yy
    y += xx
    print([x, y])
    return [x, y]
n = 4
global s
s = [13, 24, 8, 19]
random.seed(time.time())
for times in range(0, 4):
    print(s)
    sum = 0
    for x in s:
        sum += f(x)
    q = [0]
    for i in range(0, 4):
        q.append(p(s[i]) + q[i])
    print(q)
    tmp = [0, 0, 0, 0]
    for i in range(0, 4):
        x = random.random()
        for j in range(1, 5):
            if q[j - 1] <= x and x <= q[j]:
                tmp[i] = s[j - 1]
    s = tmp
    print(s)
    [s[0], s[1]] = swap(s[0], s[1])
    [s[2], s[3]] = swap(s[2], s[3])
    print(s)
ans = s[0]
for x in s:
    ans = max(ans, x)
print(ans)