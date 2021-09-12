# LGV引理

## 基本作用

$$
处理有向无环图上不相交路径的计数问题
$$

## 内容

$$
\\\begin{align}
\\&在一个有向无环图G中,出发点集A = \{a_1, a_2,\dots,a_n\}, B = \{b_1, b_2,\dots,b_n\},同时有向边e的权值为w_e,记a到b的一条路径记作P:a\rightarrow b
\\&设e(a, b) = \sum_{P:a\rightarrow b}{\Big(\prod_{e\in P}{w_e}\Big)},即:	a到b所有路径的边权乘积之和; M为A\rightarrow B所有不相交路径在所有排列上的带符号的和
\\&则:M =  
\left|\begin{array}{}
    e(a_1, b_1) & e(a_1, b_2) & \cdots & e(a_1, b_n)\\ 
    e(a_2, b_1) & e(a_2, b_2) & \cdots & e(a_2, b_n)\\ 
    \vdots & \vdots & \ddots & \vdots\\
    e(a_n, b_1) & e(a_n, b_2) & \cdots & e(a_n, b_n)
\end{array}\right| = \sum_{(P_1, P_2, \dots, P_n):A\rightarrow B}{sign(\sigma(P)) * \prod_{i = 1}^n{\Big(\prod_{e\in P_i}{w_e}}\Big)}
\\&其中排列是指A与B的对应关系(对应路径P_i:A_i\rightarrow B_{\sigma(i)}),符号sign(P)表示(-1)^{P的逆序对个数}
\\\end{align}
$$

## 简单运用

$$
\\\begin{align}
\\&令所有边权w都为1,即w = 1; 且A与B为一一对应关系,则:n条不相交的路径的方案计数 = 上述的行列式 = \det(M),即为这n个起点与终点间走出n条不相交路径的方案数
\\\end{align}
$$

## 证明

$$
\\\begin{align}
\\&先考虑简单的情况,n = 2的时候,a_1\rightarrow b_1, a_2\rightarrow b_2不相交的路径方案数.
\\&那么对于a_1、a_2,b_1、b_2的相对位置只有两种情况.
\\\end{align}
$$

​	![image-20210911213851593](https://raw.githubusercontent.com/WinnieVenice/PicBed/main/image-20210911213851593.png)

$$
\\\begin{align}
\\&当(a_1\rightarrow b_1)与(a_2\rightarrow b_2)平行时,P_{a_1\rightarrow b_1}的路径与P_{a_2\rightarrow b_2}的路径交点数为偶数(\geq 0);
\\&当(a_1\rightarrow b_1)与(a_2\rightarrow b_2)相交时,P_{a_1\rightarrow b_1}的路径与P_{a_2\rightarrow b_2}的路径交点数为奇数(\geq 0);
\\&不难知道,第二种相交的情况可以转换成第一种情况的相交方案数计数,即:
\\&将第一次相交看成a_1与a_2交换位置,则此时(a'_1, b_1),(a'_2, b_2)即是第一种情况,
\\&此时的方案\leftrightarrow第一种情况下的当前交点数-1的方案
\\&故:不相交的路径方案数 = 方案数_{a_1\rightarrow b_1} * 方案数_{a_2\rightarrow b_2} - 方案数_{a_1\rightarrow b_2} * 方案数_{a_2\rightarrow b_1}
\\\end{align}
$$
![image-20210911234055739](https://raw.githubusercontent.com/WinnieVenice/PicBed/main/image-20210911234055739.png)
$$
\\\begin{align}
\\&n = 2的情况其实是一个简单的容斥,那么推广到n的情况,应该也是容斥.
\\&考虑和上面一样的做法,交换某两个起点和终点,那么这两个交点的路径一定会相交,由上面知道,我们应在该项系数上*(-1)
\\&交换两个点产生一个逆序对,枚举所有排列,再乘上*(-1)^{P的逆序对个数},就能算出所有不相交的路径数
\\\end{align}
$$

$$
\\\begin{align}
\\det(M) &= \sum_{\sigma\in S}{sign(\sigma)*\sum_{P}{w(P), P:(a_1, a_2, \dots, a_n)\rightarrow(b_{\sigma(1)}, b_{\sigma(2),\dots,b_{\sigma(n)}})}}
\\&= \sum_{P:A\rightarrow B}{sign(\sigma(P)) * w(P)}
\\&= \Big[\sum_{P^u:A\rightarrow B}{sign(\sigma(P^u)) * w(P^u)}\Big] + \Big[\sum_{P^c:A\rightarrow B}{sign(\sigma(P^c)) * w(P^c)}\Big]
\\&若引理成立,则必有:\sum_{P^c:A\rightarrow B}{sign(\sigma(P^c)) * w(P^c)} = 0
\\&设C = \{P^c\},若能构造一个双射f:C\rightarrow C,满足\forall P^c\in C, w(f(P^c)) = w(P^c), sign(\sigma(f(P^c))) = -sign(\sigma(P^c)).
\\&那么根据重排列定理,则有:\sum_{P^c}{sign(\sigma(P^c)) * w(P^c)} = \sum_{P^c}{sign(\sigma(f(P^c))) * w(f(P^c))}
\\则有:\sum_{P^c}{sign(\sigma(P^c)) * w(P^c)} &= \frac{1}{2} * \Big\{\left[\sum_{P^c}{sign(\sigma(P^c)) * w(P^c)}\right] + \left[\sum_{P^c}{sign(\sigma(f(P^c))) * w(f(P^c))}\right]\Big\}
\\&=\frac{1}{2}*\Big\{\left[\sum_{P^c}{sign(\sigma(P^c)) * w(P^c)}\right] + \left[\sum_{P^c}{-sign(\sigma(P^c)) * w(P^c)}\right]\Big\}
\\&=0
\\&确实可以构造:
\\考虑P^c\in C,&从中找到最小的二元组(i, j)满足P_i和P_j相交,将相交后的路径终点交换一下,交换后的得到P'_i, P'_j,则显然有P'_i,P'_j\in C,且i\not=j
\\\end{align}
$$

![image-20210912165854183](https://raw.githubusercontent.com/WinnieVenice/PicBed/main/image-20210912165854183.png)
$$
\\\begin{align}
\\&简单来说:设P_i:a_i\rightarrow b_{\sigma(i)}, P_j = a_j\rightarrow b_{\sigma(j)}
\\&\begin{cases}\ P_i = e(a_i, v_k) + e(v_k, b_{\sigma(i)}) \\\ P_j = e(a_j, v_k) + e(v_k, b_{\sigma(j)}) \end{cases}
\Rightarrow\begin{cases}\ P'_i = e(a_i, v_k) + e(v_k, b_{\sigma(j)})\\\ P'_j = e(a_j, v_k) + e(v_k, b_{\sigma(i)}) \end{cases}
\\&由于边还是那些边,所以边权w(P)不变;由于交换了终点，所以逆序对数的奇偶改变,故:sign(\sigma(P')) = -sign(\sigma(P))
\\&即:sign(\sigma(f(P))) = -sign(\sigma(P))
\\&事实上,对于P',(i, j)还是最小的二元组,故f(p') = P, 因此f是双射
\\\end{align}
$$

## 做法

$$
\\通用的:利用高斯消元(n^3),可以做到O(求解n对点对之间的路径信息 + n^3)
\\某些题求解n对点对之间的路径信息可以用分治做到O(n*log(n)),则总的O(n*log(n) + n^3)
\\或者通过化简矩阵来减少复杂度
$$

