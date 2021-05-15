# Another Coin Weighing Puzzle-莫比乌斯反演

## 题目

$$
\\\begin{align}
\\&每个背包里面分别有k个相同的硬币。
\\&已知只有一个背包里的是假币,其他的都是真币,且假币重量>真币重量。
\\&你有一个天平秤,每次左右两边可以放入相同数量的任意硬币,可以通过中间的读数知道哪边大(小)多少,你可以称量最多m次.
\\&问你最多能从多少个背包里分别出假币包。
\\\end{align}
$$

## 分析

$$
\\定义背包j的安排为A_j=\{a_{j1},a_{j2},\dots,a_{jm}\},其中a_{ji}表示在第i次称量中背包j放入了多少个硬币。
\\考虑所有背包的安排:
\\显然当a_{j1}=a_{j2}=\dots=a_{jn}=0时,背包j为假背包
\\考虑当a_{ji}不全为0时:
\\假设真硬币重量为w,假硬币重量为c*w,则:
\\在第i轮比较中,假设背包p是假硬币,则:第i轮的差值s_i=a_{pi}*c*w-a_{pi}*w=a_{pi}*(c*w-w)
\\我们得到一个差值序列S,其含义是:每轮假硬币和真硬币的差值(即天枰读数)
\\因为s_i=\lambda*a_{pi},即:s_i与假币包p一一对应
\\也就是只有假币包才满足:\forall 1\leq i\leq j\leq m,\frac{a_{pi}}{a_{pj}}=\frac{s_i}{s_j}
\\因此,如果出现有A_i,A_j满足上述对应关系,则无法分辨
\\显然有\frac{s_i}{s_j}=\frac{a_{pi}}{a_{pj}}=\frac{\lambda*a_{pi}}{\lambda*a_{pj}}
\\故我们要保证\lambda=1,即gcd(a_{pi},a_{pj})=1
\\因此答案=|A=\{a_i|a_i\in [1,k],gcd(a_i,a_j)=1\}|
\\经典莫比乌斯反演技巧:i的倍数的个数=最小公倍数是i的个数
\\记:f(n)=|A=\{a_i|a_i\in [1,k],gcd(a_i,a_j)=n\}|,F(n)=|B=\{b_i|b_i\in [1,k],b_i\%n=0\}|=(2*\frac{k}{n}+[b_i=0])^m
\\\sum_{n|d}{f(d)}=F(n)
\\f(n)=\sum_{d|n}{\mu(d)*F(\frac{n}{d})}
\\f(n)=\sum_{d|n}{\mu(d)*(2*\frac{k}{d}+1)^m}
\\答案=f(1)=\sum_{d|1}{\mu(d)*(2*\frac{k}{d}+1)^m}
\\=\sum_{d=1}^k{\mu(d)*(2*\frac{k}{d}+1)^m}
$$

