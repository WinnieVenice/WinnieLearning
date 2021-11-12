# dp优化-矩阵快速幂

$$
\\ 假设转移方程:f_i=\sum_{j=1}^n{w_jf_{i-j}},则:
\\ f_{(0,i)}=\sum_{j=1}^n{w_{(0,j)}f_{(j,i)}},即矩阵乘法形式
\\ 不难构造出以下两种矩阵相乘的形式:
\\ B = B * A形式
\\ 
\left|\begin{array}{}
& f_{i-1} & f_{i-2} & f_{i-3}) & \dots & f_{i-n}
\\& 0 & 0 & 0 & \dots & 0
\\& \vdots & \vdots & \vdots & \ddots
\\& 0 & 0 & 0 & \dots & 0
\end{array}\right|*\left|\begin{array}{}
& w_1 & 1 & 0 & 0 & \dots & 0
\\& w_2 & 0 & 1 & 0 & \dots & 0
\\& w_3 & 0 & 0 & 1 & \dots & 0
\\& \vdots & \vdots & \vdots & \vdots & \ddots
\\ & w_n &0 & 0 & 0 &\dots & 1
\end{array}\right|
=\left|\begin{array}{}
& f_{i} & f_{i-1} & f_{i-2} & \dots & f_{i-n+1}
\\& 0 & 0 & 0 & \dots & 0
\\& \vdots & \vdots & \vdots & \ddots
\\& 0 & 0 & 0 & \dots & 0
\end{array}\right|
\\
\\B=A*B形式
\\
\left|\begin{array}{}
& w_1 & w_2 & \dots & w_n
\\& 1 & 0 & \dots & 0
\\& 0 & 1 & \dots & 0
\\& \vdots & \vdots & \ddots
\\& 0 & 0 & \dots & 1
\end{array}\right| * \left|\begin{array}{}
& f_{i-1} & 0 & \dots & 0
\\& f_{i-2} & 0 & \dots & 0
\\& \vdots & \vdots & \ddots
\\& f_{i-n} & 0 & \dots & 0
\end{array}\right|
=\left|\begin{array}{}
& f_{i} & 0 & \dots & 0
\\& f_{i-1} & 0 & \dots & 0
\\& \vdots & \vdots & \ddots
\\& f_{i-n+1} & 0 & \dots & 0
\end{array}\right|
$$



