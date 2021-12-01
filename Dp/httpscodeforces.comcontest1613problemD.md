# https://codeforces.com/contest/1613/problem/D

## 题意

$$

$$

## 做法

$$
\\ 001122 + 3 \rightarrow mex+1上升,mex+1 \rightarrow f[mex+1][(mex)]+=f[mex][(mex)]
\\ 001122 + 2 \rightarrow mex-1,mex不变 \rightarrow f[mex][(mex-1)]+=f[mex][(mex-1)]
\\ 001122 + 1 \rightarrow 不合法 
\\ 001122 + 0 \rightarrow 不合法
\\ 001122 + 4 \rightarrow mex+1,mex不变 \rightarrow f[mex][(mex+1)]+=f[mex][(mex+1)]
\\ 00112244 + 2 \rightarrow mex-1,mex不变 \rightarrow f[mex][(mex-1)]+=f[mex][(mex-1)]
\\ 00112244 + 4 \rightarrow mex+1,mex不变 \rightarrow f[mex][(mex+1)]+=f[mex][(mex+1)]
\\ 00112244 + 3 \rightarrow mex + 2上升 \rightarrow f[mex+2][(mex)]+=f[mex][(mex)]
$$

