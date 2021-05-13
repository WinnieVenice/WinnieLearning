# Min_25筛

## 定义

$$
比杜教筛更牛逼的特殊的求积性函数的前缀和\sum_{i=1}^n{f(i)},其中f(p^c)要能快速求值
$$

## 思路

$$
类似于杜教筛的思路,只是进一步的，在递推时分成合数部分F和质数部分G。
\\根据定义质数部分我们能快速处理出来,然后弄出F(\frac{n}{d})和G\rightarrow F(n)
$$

## 结论

$$
记mfp(n)=min\{p:p|n\}*[n>1]+[n=1];F(k,n)=\sum_{i=2}^n{f(i)*[p_k\leq mfp(i)]};G(k,n)=\sum_1^n{f(i)*[p_k<mfp(i)\cup i\in P]}
\\答案=F(1,n)+f(1) 
\\递推式:
\\\begin{align}
\\F(k,n)&=\sum_{i=2}^n(f(i)*[p_k\leq mfp(i)])
\\&=\Big[G(1,n)-G(1,p_{k-1})\Big]+\left[\sum_{k\leq i,p_i^2\leq n}\sum_{c\geq1,p_i^{i+1}\leq n}{[f(p_i^c)*F(i+1,\frac{n}{p_i^c})+f(p_i^{i+1})]}\right]
\\\end{align}
\\G(k,n)=G(k-1,n)-[p_k^2\leq n]*g(p_k)*[G(k-1,\frac{n}{p_k})-G(k-1,p_{k-1})]
$$

## 实现

$$
线性筛预处理筛出\sqrt n内的p,f值,此时还能根据筛出的f把对应g也晒出来,合并并记忆化g后得到G，根据F递推式递归求F(1,n)
$$

