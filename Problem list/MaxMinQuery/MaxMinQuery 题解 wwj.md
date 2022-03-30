# MaxMinQuery 题解

$$
\\ F(r)=\sum_{i=1}^r\sum_{j=i}^rf(i,j)
\\ F(r+1)=F(r)+\sum_{i=1}^{r+1}f(i,r+1)
\\ T(r)=\sum_{i=1}^rf(i,r),则：F(r+1)=F(r)+T(r+1)
\\ T(r+1)=\sum_{i=1}^rf(i,r)*g(r,r+1)+f(r+1,r+1),即：f(i,r+1)=f(i,r)*g(r,r+1)
\\ 调整函数g(r,r+1)=\begin{cases}1,a_{r+1}对f(i,r)没贡献\\ \frac{a_{r+1}}{a_{pre}},a_{r+1}是新的极值 \end{cases}
\\ 由于极值的贡献范围是一段一段的，所以可以知道：a_{r+1}的影响至多只有(p,r+1),p为r\rightarrow 1中第一个a_p<>a_{r+1}
\\ 故:T(r+1)=(\sum_{i=1}^pf(i,r))*1+(\sum_{i=p+1}^rf(i,r))*\frac{a_{r+1}}{a_{pre}}+f(r+1,r+1)
\\ T(r+1)=1*\sum_{1}^pf_j*len_j+\sum_{p+1}^{r+1}f_j\frac{a_{r+1}}{a_j}*len_j+f(r+1,r+1)
\\ 我们事实上只关心贡献更改的那一部分(事实上我们更新的时候也只更新这一部分)
\\ 所以我们忽略掉不变的那一部分，则：T(r+1)=\sum_{p+1}^{r+1}f_j\frac{a_{r+1}}{a_j}*len_j
\\ 这里下标j表示考虑成一段一段后的第j段
\\ 这样子还是不好维护，因为每段的len_j都不一样，考虑如何处理len_j
\\ 依旧是前缀和思想len_j=id(r_j)-id(l_j),不难知道id(r_j)=r+1,这里指的是有贡献的那部分的
\\ 那么T(r+1)就分为两段，即：
\\ T(r+1)=-\Big[\sum_{p+1}^{r+1}f_j\frac{a_{r+1}}{a_j}*id(l_j)\Big]+\Big[\sum_{p+1}^{r+1}f_j\frac{a_{r+1}}{a_j}*(r+1)\Big]
\\ L(r+1)=-\Big[\sum_{p+1}^{r+1}f_j\frac{a_{r+1}}{a_j}*id(l_j)\Big]
\\ (r+1)R(r+1)=(r+1)\Big[\sum_{p+1}^{r+1}f_j\frac{a_{r+1}}{a_j}\Big]\Rightarrow R(r+1)=\Big[\sum_{p+1}^{r+1}f_j\frac{a_{r+1}}{a_j}\Big]
\\ T(r+1)=L(r+1)+R(r+1)*(r+1)
\\ F(r+1)=F(r-1)+L(r+1)+R(r+1)*(r+1)
\\ 用线段树维护F,L,R，即：F(x)=F(x-1)+f(x,x)+L(x)+R(x)*x
\\ 事实上我们可以将F并入L中一起维护，那么答案就是ans = L+R*len
$$

