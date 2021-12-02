# MEX Sequences

https://codeforces.com/contest/1613/problem/D

## 题意

$$

$$

## 做法

$$
\\ 001122+(2/3/4) \leftarrow 非下降状态 \leftarrow 状态0
\\ 00112244+(2) \leftarrow 上下抖,向下 \leftarrow 状态1
\\ 0011224422+(4) \leftarrow 上下抖,向上 \leftarrow 状态2
\\ 因此一个序列有3种状况
\\ 考虑dp[x][0/1/2]表示mex=x时且序列状态为0/1/2时的方案数
\\ 考虑转移:
\\ f[0]\rightarrow f[0],f[0]\rightarrow f[1]
\\ f[1]\rightarrow f[1],f[2]\rightarrow f[1]
\\ f[2]\rightarrow f[2],f[1]\rightarrow f[2]
\\ 即:
$$

